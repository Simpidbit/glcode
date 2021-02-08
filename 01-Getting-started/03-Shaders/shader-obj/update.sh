mv spshader.c.bak spshader.c
gcc ./spshader.c ./glad.c -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lsimpidbit -ldl -lm -o libspshader.so -fPIC -shared
sudo cp ./libspshader.so /usr/lib
sudo cp ./spshader.h /usr/include
mv spshader.c spshader.c.bak
