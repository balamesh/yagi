#!/bin/bash
sudo apt-get install g++-multilib libncurses5-dev libreadline6-dev

cd libantlr3c-3.4/
arch=$(uname -i)
# echo $arch

# Check whether --enable-abiflags was given.
if [ "$arch" = "x86_64" ]; then
  echo "64 bit build"
  ./configure --enable-64bit
else
  echo "32 bit build"
  ./configure
fi

make
sudo make install

cd ..
mkdir -p build
cd build
cmake ../
make
