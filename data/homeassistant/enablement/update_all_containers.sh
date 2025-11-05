#!/usr/bin/env bash
dockerpath="/home/pi/docker"
logdate=$(date +"%Y%m%d")
logfile="$dockerpath"/scriptlogs/"$logdate".log

echo "###########################################EXECUTE UPDATE SCRIPT####################################" >> "$logfile"
while IFS="" read -r dockercompose;
do
  while IFS="" read -r image;
  do
    echo "docker pull $image" >> "$logfile" 2>&1
    docker pull "$image" >> "$logfile" 2>&1;
  done < <(grep image < "$dockercompose" | sed 's/^    image: //g');
done < <(find "$HOME/docker/" -name docker-compose.yml 2>/dev/null);
