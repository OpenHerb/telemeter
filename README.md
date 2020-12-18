# Arduino Make
[![Arduino Make](https://github.com/cSDes1gn/arduino-make/workflows/Arduino%20Make/badge.svg?branch=master)](https://github.com/cSDes1gn/arduino-make/actions)

![img](/docs/img/ArduinoCommunityLogo.png)

- [Arduino Make](#arduino-make)
  - [Quickstart](#quickstart)
    - [Vscode](#vscode)
  - [License](#license)

Arduino Make is a repository template for building large scale arduino projects. It attempts to homogenize best practices for C/C++ development in accordance with [Google Style C++](https://google.github.io/styleguide/cppguide.html) and [DOxygen](https://www.doxygen.nl/manual/index.html) while meeting the requirements for `arduino-cli` runtimes. The environment is controlled by an easy to use Makefile with a built-in linter to enforce good coding habits and consistent and flexible arduino project design.

## Quickstart
1. Preinstallations and environment configuration
    Clone the repository:
    ```bash
    git clone https://github.com/cSDes1gn/arduino-make.git
    ```
    Install the `arduino-cli` tool. Be sure to set the `INSTALLATION_PATH` to a location that is within your system path. (You can check your system path using `env | grep PATH`)
    ```bash
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=INSTALLATION_PATH sh
    ```
    For more installation information visit the [arduino-cli docs](https://arduino.github.io/arduino-cli/latest/installation/)

2. Populate `.env` file with environment configurables. For more information about environment configuration see the [docs]().

3. Setup and configure `arduino-cli` and `cpplint`, run:
    ```bash
    make setup
    ```
4. Test the demo project by connecting your arduino board through USB. These make targets compile and flash the demo to your arduino board.
    ```bash
    make compile;
    make flash
    ```
1. Open the serial monitor and observe the output from the serial port using `make monitor`
6. Clean the project environment using `make clean`
Run `make` for more information on make targets

### Vscode
This repository includes `.vscode` `c_cpp_properties.json` and `.code-workspace` files for vscode environment setup. For more information on these configuration files see the [docs]().

## License
[MIT License](LICENSE)