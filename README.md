# Sunkell

A game engine built from scratch as a learning exercise.
Not production-ready software.

## Table of Contents

- [Sunkell](#Sunkell)
  - [Table of Contents](#table-of-contents)
  - [About the Project](#about-the-project)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
  - [Usage](#usage)
  - [Contributing](#contributing)
  - [License](#license)
  - [Contact](#contact)

## About the Project

Sunkell is an experimental video game engine built from scratch. It is developed primarily as a learning exercise, with the intent of practicing how to architect and implement a complex cross-platform software system. It succeeds an earlier project called "Phantom Drive," which was abandoned due to some poor design decisions made early in its development and an overall lack of direction.

While the goal is to eventually create a full-featured game using it, the emphasis is on creating well-encapsulated components with robust tests and thorough documentation.

As this is something worked on in the developer's spare time, progress *will* be slow. The first major release is likely a very long way off. That said, a number of individual components have reached a stable state and one may find them useful for their own projects, either as-is or as a reference.

## Getting Started

Instructions for setting up and running the project locally.

### Prerequisites

This project is written in C++ and uses the CMake build system. You will need to have a C++ compiler and CMake installed on your machine. To build and run the test suite, you will need the [doctest](https://github.com/doctest/doctest) library installed. Other than that, Sunkell only uses system libraries and does not have any external dependencies.

### Installation

Open the project directory in your terminal and run the following commands:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build build
```

This will generate the build files and compile the project. You can find the compiled binaries in the `build` directory. The test runner, if built, will be in the `build/tests` directory and the component libraries will be in `build/src`. The build system is not currently configured to install the libraries to a system-wide location.

## Usage

To run the test suite, execute:


```bash
ctest --test-dir build
```

If you want to use any of the components in your own project, you can include the relevant headers from the `src` directory and link against the compiled libraries found in the `build/src` directory.

What components are considered stable is not actively tracked here. You are advised to review which components have a test suite by running `./build/tests/run_tests.exe -lts` and then check whether those tests all pass successfully by running `./build/tests/run_tests.exe -ts=SUITE_NAME`, where `SUITE_NAME` is the name of the test suite you wish to check.

## Contributing

As this is a personal learning project, feature contributions are not currently being sought. However, if you have suggestions or find a problem, feel free to open an issue on the project's [GitHub repository](https://github.com/Leodmanx2/sunkell). Pull requests may be considered if they are sufficiently small or explained in enough detail to be used as learning material. Additional documentation or test coverage is also welcome.

## License

This project is licensed under the Mozilla Public License v2.0. See the [LICENSE](LICENSE) file for details.

MPL 2.0 is a weak copyleft license that allows you to use, modify, and distribute the code freely, even in proprietary software. However, any modifications to files covered by the MPL must be made available under the same license. In effect, this means you can extend the project by adding new files under a different license, but any changes to existing files must be shared back to the public.

## Contact

The developer may be contacted by sending an e-mail to [chris@chris-macleod.ca](mailto:chris@chris-macleod.ca).
