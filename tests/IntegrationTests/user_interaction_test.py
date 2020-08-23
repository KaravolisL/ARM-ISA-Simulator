# Standard Libraries
import os
import sys
import pytest
from time import sleep

if (sys.platform == 'win32'):
    import wexpect as xexpect
else:
    import pexpect as xexpect

def test_step_through(find_executable, artifacts):
    """Test user's ability to step through a program instruction by instruction

    :param fixture find_executable: Finds and returns the simulator executable
    :param fixture artifacts: Sets up the artifacts folder, organizes artifact at teardown
    
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
    :param fixture artifacts: Sets up the artifacts folder, organizes artifact at teardown
    
    """
    TEST_PROGRAM = r"SourcePrograms/FunctionProgram.s"

    # Execute simulator
    program = xexpect.spawn("./" + find_executable, ["-f" + TEST_PROGRAM, "-d"])

    while (True):

        # Step out of every function we enter
        if (program.before != None and program.before.find(b"BL") >= 0):
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

    # Step out of while in __main
    for debug_option in ('', '', '2'):
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


if __name__ == '__main__':
    raise Exception("Run using pytest")
    