import pytest
import os
import sys

@pytest.fixture
def find_executable():
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
    os.chdir(sys.path[0])

    ARTIFACTS_FOLDER = r"Artifacts"
    if not os.path.isdir(ARTIFACTS_FOLDER):
        os.mkdir(ARTIFACTS_FOLDER)

    yield ARTIFACTS_FOLDER

    # Rename and move artifacts into folder
    current_test = os.environ.get('PYTEST_CURRENT_TEST').split(':')[-1].split(' ')[0].split('.')[0]

    DEBUG_LOG = r'Debug.log'
    MEMORY_FILE = r'Memory.bin'

    os.replace(DEBUG_LOG, os.path.join(ARTIFACTS_FOLDER, '_'.join([current_test, DEBUG_LOG])))
    os.replace(MEMORY_FILE, os.path.join(ARTIFACTS_FOLDER, '_'.join([current_test, MEMORY_FILE])))