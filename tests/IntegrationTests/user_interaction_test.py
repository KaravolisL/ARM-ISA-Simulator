# Standard Libraries
import os
import sys
import polling
import pytest

if (sys.platform == 'win32'):
    import wexpect as xexpect
else:
    import pexpect as xexpect

def test_step_through(find_executable, artifacts):
    """Test user's ability to step through a program instruction by instruction

    :param fixture find_executable: Finds and returns the simulator executable
    :param fixture artifacts: Sets up the artifacts folder, organizes artifacts at teardown

    """
    TEST_PROGRAM = r"SourcePrograms/SimpleProgram.s"

    # Execute simulator
    program = xexpect.spawn("./" + find_executable, ["-f" + TEST_PROGRAM, "-d"])

    while (True):
        try:
            program.expect("Debug Option: ", timeout=0.2)
        except (xexpect.TIMEOUT, xexpect.EOF) as e:
            print(e)
            assert(program.isalive() == False), "Program is hung"
            break
        program.sendline('')

    returncode = program.wait()
    assert(returncode == 0), "Program did not execute successfully"

def test_step_out_of(find_executable, artifacts):
    """Test user's ability to step out of the currently executing function

    :param fixture find_executable: Finds and returns the simulator executable
    :param fixture artifacts: Sets up the artifacts folder, organizes artifacts at teardown

    Requirements:
        - Step out of shall execute a single instruction if the program is in __main
        - Step out of shall execute instructions until the current function returns if inside a function

    """
    TEST_PROGRAM = r"SourcePrograms/FunctionProgram.s"

    # Execute simulator
    program = xexpect.spawn("./" + find_executable, ["-f" + TEST_PROGRAM, "-d"])

    # TEST 1: Step out of function once entered
    pattern = "PUSH" if sys.platform == 'win32' else b"PUSH"
    while (True):

        # Step out of function we entered
        if (program.before != None and program.before.find(pattern) >= 0):
            debug_option = '2'
        else:
            debug_option = ''

        try:
            print(program.before)
            program.expect("Debug Option: ", timeout=0.2)
        except (xexpect.TIMEOUT, xexpect.EOF) as e:
            print(e)
            assert(program.isalive() == False), "Program is hung"
            break
        program.sendline(debug_option)

    returncode = program.wait()
    assert(returncode == 0), "Program did not execute successfully"

    # Execute simulator
    program = xexpect.spawn("./" + find_executable, ["-f" + TEST_PROGRAM, "-d"])

    # TEST 2: Step out of while in __main (expected behavior is to just step)
    for debug_option in ('2', '2', '2', '2', '2', '2'):
        try:
            print(program.before)
            program.expect("Debug Option: ", timeout=0.2)
        except (xexpect.TIMEOUT, xexpect.EOF) as e:
            print(e)
            assert(program.isalive() == False), "Program is hung"
            break
        program.sendline(debug_option)

    while (True):
        try:
            print(program.before)
            program.expect("Debug Option: ", timeout=0.2)
        except (xexpect.TIMEOUT, xexpect.EOF) as e:
            print(e)
            assert(program.isalive() == False), "Program is hung"
            break
        program.sendline('')

    returncode = program.wait()
    assert(returncode == 0), "Program did not execute successfully"

def test_step_over(find_executable, artifacts):
    """Test user's ability to step over a function

    :param fixture find_executable: Finds and returns the simulator executable
    :param fixture artifacts: Sets up the artifacts folder, organizes artifacts at teardown

    Requirements:
        - Step over shall execute a single instruction if the next instruction is not BL or BLX
        - Step over shall execute until the next function returns if the next instruction is either BL or BLX

    """
    TEST_PROGRAM = r"SourcePrograms/FunctionProgram.s"

    # Execute simulator
    program = xexpect.spawn("./" + find_executable, ["-f" + TEST_PROGRAM, "-d"])

    pattern = "BL" if sys.platform == 'win32' else b"BL"
    while (True):

        # Step over functions
        if (program.before != None and program.before.find(pattern) >= 0):
            debug_option = '3'
        else:
            debug_option = ''

        try:
            print(program.before)
            program.expect("Debug Option: ", timeout=0.2)
        except (xexpect.TIMEOUT, xexpect.EOF) as e:
            print(e)
            assert(program.isalive() == False), "Program is hung"
            break
        program.sendline(debug_option)

    returncode = program.wait()
    assert(returncode == 0), "Program did not execute successfully"

def test_abort(find_executable, artifacts):
    """Test user's ability to abort their program using the q input

    :param fixture find_executable: Finds and returns the simulator executable
    :param fixture artifacts: Sets up the artifacts folder, organizes artifacts at teardown

    """
    TEST_PROGRAM = r"SourcePrograms/SimpleProgram.s"

    # Execute simulator
    program = xexpect.spawn("./" + find_executable, ["-f" + TEST_PROGRAM, "-d"])

    for debug_option in ('', '', '', 'q'):
        try:
            program.expect("Debug Option: ", timeout=0.2)
        except (xexpect.TIMEOUT, xexpect.EOF) as e:
            print(e)
            assert(program.isalive() == False), "Program is hung"
            break
        program.sendline(debug_option)

    try:
        program.expect("Aborting program...", timeout=0.2)
    except:
        assert(False), "Program did not abort"

    try:
        polling.poll(lambda: program.isalive() == False, step=0.1, timeout=1)
    except polling.TimeoutException as te:
        assert(False), "Program is hung"

    returncode = program.wait()
    assert(returncode == 0), "Program did not execute successfully"

def test_inspect(find_executable, artifacts):
    """Test user's ability to inspect both registers and memory locations

    :param fixture find_executable: Finds and returns the simulator executable
    :param fixture artifacts: Sets up the artifacts folder, organizes artifacts at teardown

    """
    TEST_PROGRAM = r"SourcePrograms/MemoryProgram.s"

    # Execute simulator
    program = xexpect.spawn("./" + find_executable, ["-f" + TEST_PROGRAM, "-d"])

    pattern = "NOP" if sys.platform == 'win32' else b"NOP"
    while (True):

        try:
            print(program.before)
            program.expect("Debug Option: ", timeout=0.2)

        except (xexpect.TIMEOUT, xexpect.EOF) as e:
            print(e)
            program.kill()
            assert(False), "Program didn't respond as expected"

        # Stop once we see the nop at the end of the program
        if (program.before != None and program.before.find(pattern) >= 0):
            break

        program.sendline('')

    # Expected register and memory values
    expected_values = {
        'R0' : '0x19',
        'R1' : '0x1a',
        'R2' : '0x1b',
        'R3' : '0x20000008',
        'R4' : '0x20000018',
        'R5' : '0x0',
        'R6' : '0x6e',
        'R7' : '0xfffffffb',
        '0x20000000' : '0x19',
        '0x20000004' : '0x1a',
        '0x20000010' : '0xe0c0a08'
    }

    for key in expected_values:
        program.sendline('i')
        try:
            print(program.before)
            program.expect("Register or Memory Address to Inspect: ", timeout=0.3)
        except (xexpect.TIMEOUT, xexpect.EOF) as e:
            print(e)
            program.kill()
            assert(False), "Program responded unexpectedly"

        # Enter the register/memory address
        program.sendline(key)
        try:
            print(program.before)
            program.expect("Value of " + key + " = " + expected_values[key], timeout=0.5)
        except (xexpect.TIMEOUT, xexpect.EOF) as e:
            print(program.after)
            program.kill()
            assert(False), "Program responded unexpectedly"

    # Finish executing the program
    program.sendline('')
    returncode = program.wait()
    assert(returncode == 0), "Program did not execute successfully"

if __name__ == '__main__':
    raise Exception("Run using pytest")
