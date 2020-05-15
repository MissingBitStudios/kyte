# Kyte

[![Latest Release](https://img.shields.io/github/v/release/MissingBitStudios/kyte)](https://github.com/MissingBitStudios/kyte/releases)
[![Build Status](https://travis-ci.org/MissingBitStudios/kyte.svg?branch=master)](https://travis-ci.org/github/MissingBitStudios/kyte)
[![Documentation Status](https://readthedocs.org/projects/kyte/badge/?version=latest)](https://kyte.readthedocs.io/en/latest/?badge=latest)

Kyte is a shader language and compiler.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

* CMake

### Checkout

```sh
git clone https://github.com/MissingBitStudios/kyte.git
cd kyte
mkdir build
cd build
cmake ..
cmake --build .
```

## Documentation

The Syntax, API reference, and command line options are available on https://kyte.readthedocs.io

## Built With

* [argparse](https://github.com/p-ranav/argparse)
* [Bison](https://www.gnu.org/software/bison/)
* [googletest](https://github.com/google/googletest)
* [re2c](http://re2c.org/)
* [SPIRV-Cross](https://github.com/KhronosGroup/SPIRV-Cross)
* [SPIRV-Headers](https://github.com/KhronosGroup/SPIRV-Headers)
* [SPIRV-Tools](https://github.com/KhronosGroup/SPIRV-Tools)

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/spec/v2.0.0.html) for versioning. For the versions available, see the [releases page](https://github.com/MissingBitStudios/kyte/releases). 

## Authors

* [widberg](https://github.com/widberg)
* [pcguy123](https://github.com/pcguy123)

See also the list of [contributors](https://github.com/MissingBitStudios/kyte/graphs/contributors) who participated in this project.

## License

This project is licensed under the Creative Commons Attribution 4.0 International Public License (CC-BY-4.0) - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgements

* Thank you to the authors of Bison and re2c.
* Thank you to [Bisqwit](https://www.youtube.com/user/Bisqwit) for his informative [compiler series](https://github.com/bisqwit/compiler_series).
