import pytest
import os
import sys

@pytest.fixture(scope='function')
def find_executable():
    """Finds simulator executable inside of root directory

        Returns:
            path (str): Path to executable
    """
    PROJECT_ROOT = r"../.."

    if (sys.platform == 'win32'):
        EXECUTABLE_NAME = "ARM-ISA-SIMULATOR.exe"
    else:
        EXECUTABLE_NAME = "ARM-ISA-SIMULATOR"

    path = None
    for root, dirs, files in os.walk(PROJECT_ROOT):
        if EXECUTABLE_NAME in files:
            path = os.path.join(root, EXECUTABLE_NAME)

    assert(path != None), "Executable was not found"
    return path

@pytest.fixture(scope='session')
def artifacts():
    """Creates an Artifacts folder if one does not exists and moves logs into the folder upon test completion

        Yields:
            artifacts_folder (str): Path to the artifacts folder
    """
    os.chdir(sys.path[0])

    artifacts_folder = r"Artifacts"
    if not os.path.isdir(artifacts_folder):
        os.mkdir(artifacts_folder)

    yield artifacts_folder

    # Rename and move artifacts into folder
    current_test = os.environ.get('PYTEST_CURRENT_TEST').split(':')[-1].split(' ')[0].split('.')[0]

    DEBUG_LOG = r'Debug.log'
    MEMORY_FILE = r'Memory.bin'

    os.replace(DEBUG_LOG, os.path.join(artifacts_folder, '_'.join([current_test, DEBUG_LOG])))
    os.replace(MEMORY_FILE, os.path.join(artifacts_folder, '_'.join([current_test, MEMORY_FILE])))