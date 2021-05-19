# Developers Guide
Modified: 2021-05


## Environment Configuration
The development environment is optimized for vscode for macos or linux. Some of the configuration is recommended and not required.

### Preinstallations
Clone the repository:
```bash
git clone https://github.com/OpenHerb/telemeter.git
```
Install the `arduino-cli` tool. Be sure to set the `INSTALLATION_PATH` to a location that is within your system path. (You can check your system path using `env | grep PATH`)
```bash
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=INSTALLATION_PATH sh
```
For more installation information visit the [arduino-cli docs](https://arduino.github.io/arduino-cli/latest/installation/)

### Environment variables
All dev utilities are orchestrated by the makefile in root and the arduino-cli tool. The makefile scripts use an environment file to configure the context.

Make a copy of the `sample.env` and rename it to `.env`. Most of the development environment variables are preconfigured. The one that will need to be updated is your tty path `$TTY` (i.e. the serial port your arduino is connected to). The environment file also has specification on

### Project Dependancies
Setup and configure `arduino-cli` and install the neccessary dependancies:
```bash
make setup
```

### Tests and Misc
Test the project by connecting your arduino board through USB. These make targets compile and flash the source code to your arduino board.
```bash
make compile;
make flash
```
Open the serial monitor and observe the output from the serial port using `make monitor`
Clean the project environment using `make clean`
Run `make` for more information on make targets
