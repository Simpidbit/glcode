mv spshader.cpp.bak spshader.cpp
g++ ./spshader.cpp ./glad.c -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lsimpidbitxx -ldl -lm -o libspshader.so -fPIC -shared
sudo cp ./libspshader.so /usr/lib
sudo cp ./spshader.h /usr/include
mv spshader.cpp spshader.cpp.bak
