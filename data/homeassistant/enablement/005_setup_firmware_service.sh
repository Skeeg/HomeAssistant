#!/usr/bin/env bash
sudo ln -s /etc/systemd/system/python-firmware-webserver.service "$(pwd)/python-firmware-webserver.service"
sudo systemctl enable python-firmware-webserver
