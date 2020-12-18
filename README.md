# OpenHerb Telemeter
[![cpplint](https://github.com/OpenHerb/telemeter/workflows/cpplint/badge.svg?branch=master)](https://github.com/OpenHerb/telemeter/actions?query=workflow%3Acpplint)

![img](/docs/img/icon-transparent.png)

- [OpenHerb Telemeter](#openherb-telemeter)
  - [Quickstart](#quickstart)
  - [License](#license)

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

2. Populate `.env` file with environment configurables. For more information about environment configuration see the [docs](/docs/README.md).

3. Setup and configure `arduino-cli` and `cpplint`, run:
    ```bash
    make setup
    ```
4. Test the project by connecting your arduino board through USB. These make targets compile and flash the source code to your arduino board.
    ```bash
    make compile;
    make flash
    ```
5. Open the serial monitor and observe the output from the serial port using `make monitor`
6. Clean the project environment using `make clean`


Run `make` for more information on make targets

## License
[GNU General Public License v3.0](LICENSE)