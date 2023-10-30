#!/bin/bash

udm-login 10.2.2.1 "$(secret get UDM_USERNAME)" "$(secret get UDM_PASSWORD)"

echo "[" > at.raw
active-tasmotas | jq -c ". | [.mac, .ip]" | sed 's/,/,\"ip\":/' | sed 's/\[/{\"mac":/' | sed 's/\]/},/' >> at.raw
echo "]" >> at.raw
tr '\n' ' ' < at.raw | sed 's/,[[:space:]]\]/\]/g' | jq -c '.' > at.json
