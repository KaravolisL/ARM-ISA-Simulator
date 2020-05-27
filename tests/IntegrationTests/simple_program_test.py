import os
import sys
import subprocess

PROJECT_ROOT = r"../.."

if (sys.platform == 'win32'):
    EXECUTABLE_NAME = "ARM-ISA-SIMULATOR.exe"
else:
    EXECUTABLE_NAME = "ARM-ISA-SIMULATOR"

TEST_PROGRAM_NAME = "SampleProgram.s"
CONSTANTS_FILE_NAME = "Constants.s"
OUTPUT_FILE_NAME = "simple_program_output.txt"

def find(name, path):
    for root, dirs, files in os.walk(path):
        if name in files:
            return os.path.join(root, name)

if __name__ == '__main__':
    print("Simple Program Integration Test START")

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

        MOV R1, #0xAA
        
        ADD R2, R1, #0xA ; R2 = 0xB4

        MOV R3, #0x66
        AND R3, R1 ; R3 = 0x22

        BIC R4, R1, #0x0F ; R4 = 0xA0

        MOV R0, #0x50
        EOR R5, R1, R0 ; R5 = 0xFA

        MOV R0, #65
        ORR R6, R1, R0 ; R6 = 0xEB

        NOP

        B MyLabel

        MOV R7, #0xBEEF

    MyLabel MOV R0, #0xFF
        MOV R7, #7 ; R7 = 7

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
    expected_values = ['ff', 'aa', 'b4', '22', 'a0', 'fa', 'eb', '7']
    lines = output.readlines()

    for i in range(0, 7):
        assert(expected_values[i] in lines[i]), lines[i] + " does not contain " + expected_values[i]

    output.close()

    # Cleanup
    os.remove(TEST_PROGRAM_NAME)
    os.remove(CONSTANTS_FILE_NAME)
    os.remove(OUTPUT_FILE_NAME)

    print("Simple Program Integration Test COMPLETE")