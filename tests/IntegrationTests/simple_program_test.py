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

        MOV R1, #0
        MOV R2, #0
        ADD R2, =MY_CONSTANT

        B MyLabel

        MOV R3, #0xBEEF

    MyLabel

        ADD R3, R1, R2

        ENDP
    
    ''')

    file.close()

    # Execute simulator
    if (sys.platform == 'win32'):
        program = subprocess.run(["./" + EXECUTABLE_NAME, TEST_PROGRAM_NAME])
    else:
        program = subprocess.call(["./" + EXECUTABLE_NAME, TEST_PROGRAM_NAME])

    assert(program.returncode == 0), "Program did not execute successfully"

    # Cleanup
    os.remove(TEST_PROGRAM_NAME)
    os.remove(CONSTANTS_FILE_NAME)

    print("Simple Program Integration Test COMPLETE")