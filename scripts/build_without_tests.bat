cd ..

IF NOT EXIST build (
    mkdir build
)

cd build
cmake .. -DBUILD_TESTING:BOOL=OFF
REM -G "MSYS Makefiles"
make