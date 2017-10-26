# tfc

# Building

## Requirements:
  * A compiler that supports C++ 17 (gcc or clang)
  * Boost
  * Eigen
  * CMake
  * Linux
  
## Setup Environment
Before build the project you need to get all Tensorflow protofiles and build the Protobuf, there is a script to help with this part.
But, before you need to install Shell++.

### Install Shell++
First you need intall the requirements to build Shell++
```
# apt-get install -y build-essential
# apt-get install -y libboost-all-dev libreadline6 libreadline6-dev git cmake
```

With the requirements installed, make a clone of the repository
```
$ git clone git@github.com:alexst07/shell-plus-plus.git
```
After the clone, change to directory of the project
```
$ cd shell-plus-plus
```
To compile the project, you need create a directory when the cmake files will
be generated, and so, build the project

```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

### Execute setup script
On the project root directory
```
$ shpp scripts/setup.sh
```

## Compiling
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
