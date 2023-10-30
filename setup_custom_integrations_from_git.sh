#!/usr/bin/env bash
show-upstream() { git remote show origin | grep Fetch | rev | cut -d" " -f1 | rev; }

cd /home/pi/docker/homeassistant || exit
alias gecko-git="GIT_DIR=/home/pi/docker/homeassistant/repos/gecko-bare GIT_WORK_TREE=/home/pi/docker/homeassistant git"
rm -rf /home/pi/docker/homeassistant/repos/gecko-bare
rm -rf /home/pi/docker/homeassistant/custom_components/gecko
gecko-git clone --bare git@github.com:gazoodle/gecko-home-assistant.git /home/pi/docker/homeassistant/repos/gecko-bare
gecko-git sparse-checkout init
gecko-git sparse-checkout set --no-cone '/custom_components/gecko'
gecko-git config --local status.showUntrackedFiles no
gecko-git read-tree -mu HEAD

cd /home/pi/docker/homeassistant || exit
alias smartthings-git="GIT_DIR=/home/pi/docker/homeassistant/repos/smartthings-bare GIT_WORK_TREE=/home/pi/docker/homeassistant git"
rm -rf /home/pi/docker/homeassistant/repos/smartthings-bare
rm -rf /home/pi/docker/homeassistant/custom_components/smartthings
smartthings-git clone --bare git@github.com:veista/smartthings.git /home/pi/docker/homeassistant/repos/smartthings-bare
smartthings-git sparse-checkout init
smartthings-git sparse-checkout set --no-cone '/custom_components/smartthings'
smartthings-git config --local status.showUntrackedFiles no
smartthings-git read-tree -mu HEAD

git restore README.md

