cd ..

IF NOT EXIST build (
    mkdir build
)

cd build
cmake .. -DENABLE_TESTS
REM -G "MSYS Makefiles"
make