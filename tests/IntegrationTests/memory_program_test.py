import os
import sys
import subprocess

PROJECT_ROOT = r"../.."

if (sys.platform == 'win32'):
    EXECUTABLE_NAME = "ARM-ISA-SIMULATOR.exe"
else:
    EXECUTABLE_NAME = "ARM-ISA-SIMULATOR"

TEST_PROGRAM_NAME = "MemoryProgram.s"
CONSTANTS_FILE_NAME = "MemoryConstants.s"
OUTPUT_FILE_NAME = "memory_program_output.txt"

def find(name, path):
    for root, dirs, files in os.walk(path):
        if name in files:
            return os.path.join(root, name)

if __name__ == '__main__':
    print("Memory Program Integration Test START")

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
    INCLUDE MemoryConstants.s

    __main PROC

        LDR r3, =array
        LDR r0, [r3]
        
        LDR r1, [R3, #4]

        LDR R2, [R3, #8]!

        LDR r4, =myArray
        LDR r5, =size
        LDRB r5, [r5]
        MOV r6, #0

    top
        LDRB r7, [r4], #1
        ADD r6, r7
        CMP r5, #0
        BEQ end
        SUB r5, #1
        B top
    end

        ;MOV R4, R6

        LDR r7, =myInt
        LDRSB r7, [r7]

        ENDP

    array DCD 25, 26, 27
    myArray DCB 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20

        ALIGN

    size DCB 11
        ALIGN
    myInt DCB -5
    
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
    expected_values = ['19', '1a', '1b', '20000008', '20000018', '0', '6e', 'FFFFFFFB']
    lines = output.readlines()

    for i in range(0, len(expected_values)):
        assert(expected_values[i] in lines[i]), lines[i] + " does not contain " + expected_values[i]

    output.close()

    # Cleanup
    os.remove(TEST_PROGRAM_NAME)
    os.remove(CONSTANTS_FILE_NAME)
    os.remove(OUTPUT_FILE_NAME)

    print("Memory Program Integration Test COMPLETE")