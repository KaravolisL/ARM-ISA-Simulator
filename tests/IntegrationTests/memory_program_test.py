# Standard Libraries
import os
import pytest
import subprocess

TEST_PROGRAM = r"SourcePrograms/MemoryProgram.s"
OUTPUT_FILE_NAME = "memory_program_output.txt"

def test_memory_program(find_executable, artifacts):
    """Test using program with memory operations (LDR, STR, PUSH, POP)

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
    expected_values = ['19', '1a', '1b', '20000008', '20000018', '0', '6e', 'fffffffb']
    lines = output.readlines()

    for i in range(0, len(expected_values)):
        assert(expected_values[i] in lines[i]), lines[i] + " does not contain " + expected_values[i]

    output.close()
    