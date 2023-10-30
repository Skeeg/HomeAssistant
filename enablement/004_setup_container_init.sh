#!/usr/bin/env bash
sudo cp "$(pwd)/init_all_containers.sh" "/home/pi/docker/init_all_containers.sh"
sudo cp "$(pwd)/update_all_containers.sh" "/home/pi/docker/update_all_containers.sh"
crontab << EOF
SHELL=/bin/bash
*/3 * * * * /usr/bin/env bash -c 'source /home/pi/docker/init_all_containers.sh'
EOF
sudo chown pi:crontab /var/spool/cron/crontabs/pi
