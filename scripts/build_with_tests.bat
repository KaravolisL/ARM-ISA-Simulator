cd ..

IF NOT EXIST build (
    mkdir build
)

cd build
cmake .. -DENABLE_TESTS:BOOL=ON
REM -G "MSYS Makefiles"
make