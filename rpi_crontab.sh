echo "*/3 * * * * /usr/bin/env bash -c 'source /home/pi/docker/init-all-containers.sh'" | sudo tee /var/spool/cron/crontabs > /dev/null
sudo chown pi:crontab /var/spool/cron/crontabs/pi
