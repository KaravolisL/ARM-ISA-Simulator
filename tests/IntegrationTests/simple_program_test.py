# Standard Libraries
import os
import pytest
import subprocess

TEST_PROGRAM = r"SourcePrograms/SimpleProgram.s"
OUTPUT_FILE_NAME = "simple_program_output.txt"

def test_simple_program(find_executable, artifacts):
    """Test using simple program

    :param fixture find_executable: Finds and returns the simulator executable
    :param fixture artifacts: Sets up the artifacts folder, organizes artifact at teardown
    
    """
    # Create a file to hold the program output
    output = open(os.path.join(artifacts, OUTPUT_FILE_NAME), 'w')

    # Execute simulator
    program = subprocess.call(["./" + find_executable, "-f", TEST_PROGRAM], stdout=output)
    assert(program == 0), "Program did not execute successfully"

    # Close and reopen the output file
    output.close()
    output = open(os.path.join(artifacts, OUTPUT_FILE_NAME), 'r')

    # Check for correct values in registers
    expected_values = ['ff', 'aa', 'b4', '22', 'a0', 'fa', 'eb', '7']
    lines = output.readlines()

    for i in range(0, 7):
        assert(expected_values[i] in lines[i]), lines[i] + " does not contain " + expected_values[i]

    output.close()
