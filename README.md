# PiPeri (Raspberry Pi BlueTooth LE Peripheral)

## Introduction

This project is my feeble attempt at understanding the basics of low-level BlueTooth Low Energy Peripheral programing.
This implementation uses the [bunget](https://github.com/comarius/bunget) library to run peripheral code on a Pi. Many thanks to [comarius](https://github.com/comarius) for his efforts.

## Modifications to the bunget app

This is basically the same app that comes with bunget, with some code restructuring. In addition, I use the built-in LED instead of the bread-board version.

## Compiling the app

This project uses [CMake](https://cmake.org/)

To compile and link, issue:

```
cd src/tests
cmake .
make
```

## Running

```
sudo [BUNGET_TRACE=1|2|3] ./bin/piperi 0
```

## Contributing

* Fork it (git@github.com:ihassin/piperi.git)
* Create your feature branch (git checkout -b my-new-feature)
* Commit your changes (git commit -am 'Add some feature')
* Push to the branch (git push origin my-new-feature)
* Create a new Pull Request

## Code of conduct

Our code of conduct is [here](https://github.com/ihassin/piperi/blob/master/code_of_conduct.md).

# License

All yours to use and distribute, but be aware of the bunget license as described [here](https://github.com/comarius/bunget).
