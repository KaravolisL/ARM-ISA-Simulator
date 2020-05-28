import os
import sys
import subprocess

PROJECT_ROOT = r"../.."

if (sys.platform == 'win32'):
    EXECUTABLE_NAME = "ARM-ISA-SIMULATOR.exe"
else:
    EXECUTABLE_NAME = "ARM-ISA-SIMULATOR"

TEST_PROGRAM_NAME = "FunctionProgram.s"
CONSTANTS_FILE_NAME = "FunctionConstants.s"
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
    MY_CONSTANT EQU 0xCAFE
    
    ''')

    constants_file.close()

    # Create the test program
    file = open(TEST_PROGRAM_NAME, "w")

    file.write('''
    INCLUDE FunctionConstants.s

    __main PROC

        ; Multiply 5 by 7
        MOV R0, #5
        MOV R1, #7
        MOV r3, #9
        MOV R5, #5
        MOV R4, #0xBEEF
        MOV R6, #6
        MOV R7, #0xC0DE
        MOV R8, #8
        BL multiply

        BL func1

        ENDP

    multiply PROC

        PUSH {R3, R4, R6-R8}
        MOV R4, #0xCODE
        MOV R7, #0xBEEF

        MOV R2, #0

    Top ADD R2, R0
        SUBS R1, #1
        BNE Top
        MOV R0, R2

        POP {R3, R4, R6-R8}
        BX LR

        ENDP

    func1 PROC

        PUSH {LR}

        BL func2
        POP {LR}
        BX LR

        ENDP

    func2 PROC

        MOV R10, #0xCAFE
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
    expected_values = ['23', '0', '23', '9', 'beef', '5', '6', 'c0de', '8']
    lines = output.readlines()

    for i in range(0, len(expected_values)):
        assert(expected_values[i] in lines[i]), lines[i] + " does not contain " + expected_values[i]

    output.close()

    # Cleanup
    os.remove(TEST_PROGRAM_NAME)
    os.remove(CONSTANTS_FILE_NAME)
    os.remove(OUTPUT_FILE_NAME)

    print("Function Program Integration Test COMPLETE")