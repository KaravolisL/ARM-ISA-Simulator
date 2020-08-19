# Standard Libraries
import os
import pytest
import subprocess

TEST_PROGRAM_NAME = r"SourcePrograms/ConditionalProgram.s"
OUTPUT_FILE_NAME = "conditional_program_output.txt"

def test_conditional_program(find_executable, artifacts):
    """Test using program with conditionals

    :param fixture find_executable: Finds and returns the simulator executable
    :param fixture artifacts: Sets up the artifacts folder, organizes artifact at teardown
    
    """
    # Create a file to hold the program output
    output = open(os.path.join(artifacts, OUTPUT_FILE_NAME), 'w')

    # Execute simulator
    program = subprocess.call(["./" + find_executable, TEST_PROGRAM_NAME], stdout=output)
    assert(program == 0), "Program did not execute successfully"

    # Close and reopen the output file
    output.close()
    output = open(os.path.join(artifacts, OUTPUT_FILE_NAME), 'r')

    # Check for correct values in registers
    expected_values = ['0', 'a', '14', 'ff', '8', 'fffffffe', 'aa']
    lines = output.readlines()

    for i in range(0, len(expected_values)):
        assert(expected_values[i] in lines[i]), lines[i] + " does not contain " + expected_values[i]

    output.close()
