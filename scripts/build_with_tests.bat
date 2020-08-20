cd ..

IF NOT EXIST build (
    mkdir build
)

cd build
cmake .. -DBUILD_TESTING:BOOL=ON
REM -G "MSYS Makefiles"
make