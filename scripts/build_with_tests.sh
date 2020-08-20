cd ..

if [ ! -d build ]
    then
        echo "Creating build folder"
        mkdir build
fi

cd build
cmake .. -DBUILD_TESTING:BOOL=ON # -G "MSYS Makefiles"
make