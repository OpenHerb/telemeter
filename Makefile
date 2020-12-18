# Makefile for Arduino Interfacing
# ================================
# Makefile for linting, compiling, flashing larger scale ardunio projects and
# interfacing with the arduino serial monitor
# 
# Modified: 2020-11
# Copyright © 2020 Christian Sargusingh

OKG=\033[92m
# WARNING=\033[93m
FAIL=\033[91m
OKB=\033[94m
UNDERLINE=\033[4m
NC=\033[0m

# Source user env flags
include .env
export $(shell sed 's/=.*//' .env)

# scrape serial port from /dev
# TODO: scrape using `arduino-cli board list` (requires FBQN resolvers)
TTY = $$(ls /dev/tty.usbserial*)
kill_serial := $$(kill -9 $$(lsof ${TTY} | awk 'NR>1 {print $$2}'))

.PHONY: help
help:
	@echo Usage:
	@echo "  make [target]"
	@echo
	@echo Targets:
	@awk -F ':|##' \
		'/^[^\t].+?:.*?##/ {\
			printf "  %-30s %s\n", $$1, $$NF \
		 }' $(MAKEFILE_LIST)

.PHONY: all
all: lint compile flash

.PHONY: setup
setup: ## configure arduino-cli and install python cpplinter
	@printf "${OKB}Verifying arduino-cli installation ...  ${NC}\n"
	@if ! command -v arduino-cli &> /dev/null; then\
		printf "${FAIL} ✗ ${NC} arduino-cli command not found. If the arduino-cli tool is installed check to ensure it exists in your PATH\n";\
		exit 1; fi;
	@printf "${OKB}Configuring arduino-make environment ...  ${NC}\n"
	@arduino-cli config init;
	@arduino-cli core update-index;
	@arduino-cli core install ${CORE};
	@arduino-cli core upgrade;
	@printf "\nInstalling arduino-cli requirements.\n"
	@xargs -P1 arduino-cli lib install < requirements.txt;
	@python3 -m pip install --upgrade pip
	@python3 -m pip install cpplint
	@printf "${OKG} ✓ ${NC} Build environment configured.\n"
	

.PHONY: lint
lint: ## lint with cpplint for Google cpp guidelines and code styling
	@printf "${OKB}Linting filesystems ... \n\tExtensions:\t${OKG}${LINT_EXT} \n${OKB}\
		Source dir:\t${OKG}${SOURCE_PATH}\n\t${OKB}Include dir:\t${OKG}${LD_PATH}${NC}\n"
	@cpplint --recursive --extensions=${LINT_EXT} ${SOURCE_PATH} ${LD_PATH}
	@printf "${OKG} ✓ ${NC} Complete\n"

.PHONY: compile
compile: ## build arduino artefacts
	@printf "${OKB}Compiling ${OKG}${SOURCE_PATH}/ ${OKB}into ${OKG}${BUILD_PATH}/${NC}\n"
	@arduino-cli compile -v --warnings "all" \
		--libraries ${PWD}/${LD_PATH}\
		--fqbn ${FBQN} ${SOURCE_PATH}\
		--output-dir ${BUILD_PATH}
	@printf "${OKG} ✓ ${NC} Complete\n"

.PHONY: flash
flash: ## flash arduino build artefacts to board
	@printf "${OKB}Flashing ${BUILD_PATH} to ${TTY}${NC}\n"
	@if [[ -n "$$(lsof ${TTY})" ]]; then \
		printf "${OKB}Closing serial montior @ ${TTY}${NC}\n" \
		$(call kill_serial); fi;
	@arduino-cli upload -v -p ${TTY} --fqbn ${FBQN} ${SOURCE_PATH} --input-dir ${BUILD_PATH};
	@printf "${OKG} ✓ ${NC} Complete\n"

.PHONY: clean
clean: ## clear build artefacts and close serial monitor
	@printf "${OKB}Cleaning build artefacts: ${BUILD_PATH}${NC}\n";
	@rm -rfv ${BUILD_PATH};
	@if [[ -n "$$(lsof ${TTY})" ]]; then \
		printf "${OKB}Closing serial montior @ ${TTY}${NC}\n" \
		$(call kill_serial); fi;
	@printf "${OKG} ✓ ${NC} Complete\n"

.PHONY: monitor
monitor: ## Open serial port using tty. Ctrl-a + d to exit screen
	@screen ${TTY}
	# to reconnnect to serial monitor: screen -r [pid.]tty.host