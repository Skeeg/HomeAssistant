#Pass IP List and collect Device Name for generating entries
rm devnames.txt
for n in $(cat ./iplist.txt)
do
  unset m
  m=$(curl "http://$n/cm?cmnd=devicename" -s | jq --raw-output .DeviceName | tr '[:upper:]' '[:lower:]');
  if [ -z $m ];
  then echo "var failed for $n";
  else 
    echo $m >> devnames.txt
    echo $m;
  fi
done


#Pass DeviceNames and generate Custom Card Config
rm customcardstart.yml customcardmiddle.yml customcardend.yml customcard.yml
indexCounter=0

cat << EOF > customcardstart.yml
card:
  entities:
EOF

cat << EOF > customcardmiddle.yml
  show_header_toggle: false
  title: MQTT & Wifi Connections
  type: 'custom:hui-entities-card'
entities:
EOF

cat << EOF > customcardend.yml
type: 'custom:config-template-card'
variables:
EOF

for devName in $(cat ./devnames.txt)
do
  entityName=$(echo $devName)_status
  cat << EOF >> customcardstart.yml
    - entity: sensor.$entityName
      icon: >-
        \${vars[$(($indexCounter+4))] >= -67 ? 'mdi:wifi' :
        vars[$(($indexCounter+4))] >= -70 ? 'mdi:wifi-strength-3' :
        vars[$(($indexCounter+4))] >= -80 ? 'mdi:wifi-strength-2' :
        'mdi:wifi-strength-1' }
      name: "\${
          vars[$(($indexCounter+2))] +
          ' : ' +
          vars[$(($indexCounter+4))] +
          'dBm : ' +
            ( vars[$(($indexCounter+4))] >= -35 ? 'Amazing' :
            vars[$(($indexCounter+4))] >= -67 ? 'Great' :
            vars[$(($indexCounter+4))] >= -70 ? 'Okay' :
            vars[$(($indexCounter+4))] >= -80 ? 'Bad' :
            'Unusable' ) +
          ' Signal ' +
          vars[$(($indexCounter+6))] +
          ' Downtime out of ' +
          vars[$(($indexCounter+1))] +
          ', ' +
          vars[$(($indexCounter+5))] +
          ' Wireless Events.   ' +
          vars[$(($indexCounter+7))] +
          ' MQTT Messages.   ' +
          vars[$(($indexCounter+8))] +
          '% Processing Time.  : ' +
          vars[$(($indexCounter+9))] +
          ' on Hardware : ' +
          vars[$(($indexCounter+3))]
        }"
EOF

  cat << EOF >> customcardmiddle.yml
  - sensor.$entityName
EOF

  cat << EOF >> customcardend.yml
  - 'states[''sensor.$entityName''].state'
  - 'states[''sensor.$entityName''].attributes[''Uptime'']'
  - 'states[''sensor.$entityName''].attributes[''IPAddress'']'
  - 'states[''sensor.$entityName''].attributes[''Module or Template'']'
  - 'states[''sensor.$entityName''].attributes[''Signal (dBm)'']'
  - 'states[''sensor.$entityName''].attributes[''WiFi LinkCount'']'
  - 'states[''sensor.$entityName''].attributes[''WiFi Downtime'']'
  - 'states[''sensor.$entityName''].attributes[''MqttCount'']'
  - 'states[''sensor.$entityName''].attributes[''LoadAvg'']'
  - 'states[''sensor.$entityName''].attributes[''Hostname'']'
EOF
  indexCounter=$indexCounter+10
done
cat customcardstart.yml customcardmiddle.yml customcardend.yml > customcard.yml
cat customcard.yml