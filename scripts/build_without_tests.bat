cd ..

IF NOT EXIST build (
    mkdir build
)

cd build
cmake .. 
REM -G "MSYS Makefiles"
make