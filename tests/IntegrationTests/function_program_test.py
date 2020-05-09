import os
import sys
import subprocess

PROJECT_ROOT = r"../.."

if (sys.platform == 'win32'):
    EXECUTABLE_NAME = "ARM-ISA-SIMULATOR.exe"
else:
    EXECUTABLE_NAME = "ARM-ISA-SIMULATOR"

TEST_PROGRAM_NAME = "FunctionProgram.s"
CONSTANTS_FILE_NAME = "Constants.s"
OUTPUT_FILE_NAME = "function_program_output.txt"

def find(name, path):
    for root, dirs, files in os.walk(path):
        if name in files:
            return os.path.join(root, name)

if __name__ == '__main__':
    print("Function Program Integration Test START")

    # Find the executable and go to that directory
    path = find(EXECUTABLE_NAME, PROJECT_ROOT)
    assert(path != None), "Executable was not found"
    os.chdir(os.path.dirname(path))

    # Create constants file
    constants_file = open(CONSTANTS_FILE_NAME, "w")

    constants_file.write('''
    MY_CONSTANT EQU 0xFF
    
    ''')

    constants_file.close()

    # Create the test program
    file = open(TEST_PROGRAM_NAME, "w")

    file.write('''
    INCLUDE Constants.s

    __main PROC

        ; Multiply 5 by 7
        MOV R0, #5
        MOV R1, #7
        BL multiply


        ENDP

    multiply PROC

        MOV R2, #0

    Top
        ADD R2, R0
        ADDS R1, #-1
        ; SUBS R1, #1
        BNE Top

        MOV R0, R2

        BX LR

        ENDP
    
    ''')

    file.close()

    # Create a file to hold the program output
    output = open(OUTPUT_FILE_NAME, 'w')

    # Execute simulator
    program = subprocess.call(["./" + EXECUTABLE_NAME, TEST_PROGRAM_NAME], stdout=output)
    assert(program == 0), "Program did not execute successfully"

    # Close and reopen the output file
    output.close()
    output = open(OUTPUT_FILE_NAME, 'r')

    # Check for correct values in registers
    expected_values = ['23', '0']
    lines = output.readlines()

    for i in range(0, len(expected_values)):
        assert(expected_values[i] in lines[i]), lines[i] + " does not contain " + expected_values[i]

    output.close()

    # Cleanup
    os.remove(TEST_PROGRAM_NAME)
    os.remove(CONSTANTS_FILE_NAME)
    os.remove(OUTPUT_FILE_NAME)

    print("Function Program Integration Test COMPLETE")