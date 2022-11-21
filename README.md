# Game Engine

A simple game engine.

## Usage

To build and run the application run the following commands.

```
cmake -S <path to GameEngine> -B build
cd build
make
./GameEngine
```

### Documentation

To build the documentation run the following commands.

```
cmake -S <path to GameEngine> -B build
cd build
make doc
```

The generated documentation can be found in `html/index.html`.

### Test

To build and run the tests run the following commands.

```
cmake -S <path to GameEngine> -B build
cd build
ctest --verbose
```

Note that `ctest` have other flags that can e.g. select which tests to run.

### Requirements

The following are required

* gcc
* cmake
* doxygen
* graphviz
* cppcheck
* clang-tidy

On an Ubuntu system these can be installed with the following commands.

```
sudo apt-get update && sudo apt-get upgrade -y
sudo apt autoremove -y
sudo apt-get install gcc -y
sudo apt-get install cmake -y
sudo apt-get install doxygen -y
sudo apt install graphviz -y
sudo apt-get install cppcheck -y
sudo apt-get install clang-tidy -y
```
