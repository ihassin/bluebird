# bluebird

# Set up

This project is compiled and linked on a Raspberry Pi.
I use NetBeans for remote development and debug. You can see a tutorial on how to set this up [here](http://ihassin.github.io/mac%20os%20x/gnu/netbeans/remote%20compilation/remote%20debugging/remote%20execution/raspberry%20pi/rpi/2018/01/24/remote-execution-mac-raspberrypi.html).

# Compiling

This project uses [CMake](https://cmake.org/).
To compile and link, issue:

```
cmake .
make
```

# Running tests

This project is tested by [Unity](https://github.com/ThrowTheSwitch/Unity).

# Running the demo

## Peripheral

```
cd bin
sudo ./peripheral
```
