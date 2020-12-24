#This was an initial population attempt for a prometheus monitor config from historical tasmota devices deployed.

#Pass IP List and collect Device Name for generating entries
# rm devnames.txt
# for n in $(cat ./iplist.txt)
# do
#   unset m
#   m=$(curl "http://$n/cm?cmnd=devicename" -s | jq --raw-output .DeviceName | tr '[:upper:]' '[:lower:]');
#   if [ -z $m ];
#   then echo "var failed for $n";
#   else 
#     echo $m >> devnames.txt
#     echo $m;
#   fi
# done


#Pass DeviceNames and generate Custom Card Config
FILENAME='prometheus_config.yml'
rm $FILENAME
indexCounter=0


cat << EOF > $FILENAME
scrape_configs:
  - job_name: 'tasmotas'  # Becomes a label
    static_configs:
EOF

for n in $(cat ./iplist.txt)
do
  printf '{"IPAddress":"'$n'"}'
  devName=`curl "http://$n/cm?cmnd=hostname" -s | jq --raw-output .Hostname`
  echo -e '\r\r\r'

  entityName=$(echo $devName)_status
  cat << EOF >> $FILENAME
      - targets:
        - '$n:80'
        labels:
          hostname: '$devName'
          location: '$devName'
EOF

  indexCounter=$indexCounter+10
done

cat $FILENAME