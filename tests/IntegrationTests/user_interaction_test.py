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

        # Step out of every function we enter
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

if __name__ == '__main__':
    raise Exception("Run using pytest")
