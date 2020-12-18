# Documentation

## Environment Configuration
In the workspace root there is a `.env` file that holds config settings for the project Makefile

### $SOURCE_PATH

### $LD_PATH

### $BOARD

### $CORE

### $LINT_EXT

## Vscode
This section is only written for projects using the `avr-gcc` compiler for their projects. 

The vscode configuration files can allow you to configure Microsoft's intellisense engine for autocompletion and linting alongside the cpp linter to enable a integrated development environment feel to your vscode workspace when developing arduino projects.

### `c_cpp_properties.json`
Since we are using an external compiler (`avr-gcc`) to compile our arduino project we mainly use this file to configure our intellisense autocompletion and checks alongside our cpplinter. The include paths provided are the default paths the arduino compiler. There are numerous issues I have found of people getting frustrated that intellisense highlights a missing include path but still compiles and runs. This is because intellisense is not aware of `avr-gcc` built-in include search directive. We set these built-in include paths so intellisense and `avr-gcc` are seeing your project from the same perspective.

Note that the pin states include path may have to be modified depending on your board type. For the standard board types the `standard` file should be sufficient. The available pinstates files on MacOS are located here:
```bash
ls /Users/${USER}/Library/Arduino15/packages/arduino/hardware/avr/1.8.3/variants;
```

### `arduino-make.workspace`
This file is for workspace/project specific settings. Learn more at https://code.visualstudio.com/docs/getstarted/settings