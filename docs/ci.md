# Continous Integration
Modified: 2021-05

This project currently has 2 ci build jobs hosted remotely on github actions runners:
1. source code linting by `cpplint`
2. compile by `arduino-cli`

## Lint Job
The linter uses `cpplint` and is configured using the `CPPLINT.cfg` file in root. It statically checks the source code to ensure Cpp Doxygen and Google styling guidelines

## Build Job
The build job compiles the source code using `arduino-cli` and stores the artefacts in the project actions page. In the future it will be beneficial for version archiving.