# Kyte

[![Latest Release](https://img.shields.io/github/v/release/MissingBitStudios/kyte)](https://github.com/MissingBitStudios/kyte/releases)
[![Build Status](https://travis-ci.org/MissingBitStudios/kyte.svg?branch=master)](https://travis-ci.org/github/MissingBitStudios/kyte)
[![Documentation Status](https://readthedocs.org/projects/kyte/badge/?version=latest)](https://kyte.readthedocs.io/en/latest/?badge=latest)
[![Track on https://trello.com/b/TJq9cxr2/kyte](https://img.shields.io/badge/track-on_trello-007BC2.svg?logo=trello&logoColor=ffffff&labelColor=026AA7)](https://trello.com/b/TJq9cxr2/kyte)

Kyte is a shader language and compiler.

## Code Sample

sample.ky
```
import "stl.ky";
expose namespace stl;

vertex_main :: (pos : vec3) $ ky_position : vec4 {
	return vec4(pos, 1.0f);
}

fragment_main :: () $ ky_color : vec4 {
	return vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
```

## Output Formats

* SPIR-V Binary
* SPIR-V ASM

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

* CMake >= 3.15
* Python >= 3 (Because SPIRV-Tools has it marked as required even with tests disabled for some reason)

### Checkout

```sh
git clone https://github.com/MissingBitStudios/kyte.git
cd kyte
git submodule update --init --recursive
```

### Build

The following options are available to control which targets are generated by CMake.

| Option | Description | Default |
| --- | --- | --- |
| KYTE_COMPILER | Generate kytec target | ON |
| KYTE_DOCS | Generate documentation target (Requires Sphynx) | OFF |
| KYTE_GEN_STL | Generate STL files (Requires Python) | OFF |
| KYTE_GRAMMAR | Build gammar (Requires Bison and re2c) | OFF |
| KYTE_INSTALL | Generate install targets | OFF |
| KYTE_TESTS | Generate test target | OFF |

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

### Update

```sh
git pull
git submodule sync
git submodule update --init --recursive
```

### Install

Run cmake with the `KYTE_INSTALL` option enabled, then run the following command.

```sh
cmake --install
```

## Documentation

The language syntax, API reference, and kytec command-line options are available on https://kyte.readthedocs.io.

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

## Changelog

All notable changes to this project will be documented in [CHANGELOG.md](CHANGELOG.md). The changelog format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/) and adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## Versioning

We use [SemVer](http://semver.org/spec/v2.0.0.html) for versioning. For the versions available, see the [releases page](https://github.com/MissingBitStudios/kyte/releases). 

## Authors

* [widberg](https://github.com/widberg)
* [pcguy123](https://github.com/pcguy123)

See also the list of [contributors](https://github.com/MissingBitStudios/kyte/graphs/contributors) who participated in this project.

## License

This project is licensed under the Creative Commons Attribution 4.0 International Public License (CC-BY-4.0) - see the [LICENSE.md](LICENSE.md) file for details.
