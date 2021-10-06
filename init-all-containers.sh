dockerpath="/home/pi/docker"
logdate=$(date +"%Y%m%d")
logfile="$dockerpath"/scriptlogs/"$logdate".log
echo "############################################EXECUTE INIT SCRIPT#####################################" >> $logfile
date +"%Y%m%d_%H%M%S%z" >> $logfile
/usr/local/bin/docker-compose -f "$dockerpath/grafana-prometheus/docker-compose.yml" up -d >> $logfile 2>&1
/usr/local/bin/docker-compose -f "$dockerpath/mosquitto/docker-compose.yml" up -d >> $logfile 2>&1
/usr/local/bin/docker-compose -f "$dockerpath/pihole/docker-compose.yml" up -d >> $logfile 2>&1
docker start homeassistant >> $logfile