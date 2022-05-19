#!/bin/bash

# already done by workflow
#pip install -U platformio
#platformio update

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m'

lines=$(find ./examples/ -maxdepth 1 -mindepth 1 -type d)
retval=0
while read line; do
  if [[ "$line" != *esp8266 && "$line" != *esp32 ]]
  then
    echo -e "========================== BUILDING $line =========================="
    echo -e "${YELLOW}SKIPPING${NC}"
    continue
  fi
  echo -e "========================== BUILDING $line =========================="
  if [[ -e "$line/platformio.ini" ]]
  then
    # skipping
    #output=$(platformio ci --lib="." --project-conf="$line/platformio.ini" $line 2>&1)
    :
  else
    if [[ "$line" == *esp8266 ]]
    then
      output=$(platformio ci --lib="." --project-conf="scripts/CI/platformio_esp8266.ini" $line 2>&1)
    else
      output=$(platformio ci --lib="." --project-conf="scripts/CI/platformio_esp32.ini" $line 2>&1)
    fi
  fi
  if [ $? -ne 0 ]; then
    echo "$output"
    echo -e "Building $line ${RED}FAILED${NC}"
    retval=1
  else
    echo -e "${GREEN}SUCCESS${NC}"
  fi
done <<< "$lines"

exit "$retval"
