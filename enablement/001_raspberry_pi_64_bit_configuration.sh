#!/bin/bash
sudo raspi-config

# dpkg --print-architecture
sudo apt-get update && sudo apt-get upgrade
# uname -a

sudo dpkg --add-architecture armhf

sudo apt-get update && sudo apt-get upgrade
wget -O - https://repo.saltstack.com/py3/debian/10/armhf/latest/SALTSTACK-GPG-KEY.pub | sudo apt-key add -
echo 'deb http://repo.saltstack.com/py3/debian/10/armhf/latest buster main' | sudo tee -a /etc/apt/sources.list.d/saltstack.list > /dev/null;
sudo apt-get install salt-minion -y

sudo apt-get update && sudo apt-get upgrade

sudo apt-get install apt-transport-https ca-certificates curl gnupg lsb-release jq libffi-dev libssl-dev python3-dev vim git libpam-ssh-agent-auth traceroute:armhf nslookup

curl -fsSL https://download.docker.com/linux/debian/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg

dpkg --print-architecture

echo "deb [arch=$(dpkg --print-architecture) \
  signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] \
  https://download.docker.com/linux/debian \
  $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

sudo apt-get update

sudo apt-get install docker-ce docker-ce-cli containerd.io

sudo usermod -aG docker pi

# /etc/os-release contains operating system variables.  Executing it brings them into the current shell environment.
# shellcheck disable=SC1091
. /etc/os-release; echo "$ID"

# echo "multiple string awk, return last word" | awk '{print $NF}'

sudo python3 -m pip install docker-compose
docker-compose
while IFS="" read -r dockercompose
do 
  while IFS="" read -r image
  do 
    docker pull "$image";
    # echo "$image" 
  done < <(echo "$dockercompose" | grep image | sed 's/^    image: //g')
done < <(find "$HOME/docker/" -name docker-compose.yml 2>/dev/null)

for m in $(docker images | tail -n +2 | awk '{print $1":"$2}' | sort | uniq | sed 's/:<none>$//g'); 
do 
  docker image inspect $m | grep Arch; 
done

GODOWNLOAD=$(curl https://golang.org/dl/ -s | sed -n '/Stable versions/,${p;/Archived versions/q}' | grep linux-arm64 | cut -d'"' -f6 | sort -r | head -1 | cut -d"/" -f3)
wget https://golang.org/dl/$GODOWNLOAD --directory-prefix "$HOME/Downloads"
sudo tar -C /usr/local -xzf "$HOME/Downloads/$GODOWNLOAD"
rm "$HOME/Downloads/$GODOWNLOAD"
unset GODOWNLOAD

# shellcheck disable=SC2016
echo 'GOPATH=$HOME/go
PATH=$PATH:/usr/local/go/bin:$GOPATH/go/bin' >> ~/.profile

go install github.com/glendc/go-external-ip/cmd/exip@latest

mkdir "$HOME/.ssh"

scp -r rpeay@10.2.2.4:/home/rpeay/.ssh /home/pi/.ssh

# ps -awwux | grep agent | awk '{print $2}' | xargs --verbose kill
pgrep -f "ssh-agent" | xargs --verbose kill
eval "$(ssh-agent -s)"; ssh-add /home/pi/.ssh/id_rsa

mkdir "$HOME/docker"
cd "$HOME/docker" || exit

git clone git@github.com:Skeeg/grafana-prometheus.git "$HOME/docker/grafana-prometheus"
cd "$HOME/docker/grafana-prometheus/" || exit
sudo chown -R 65534 "$HOME/docker/grafana-prometheus/prometheus/data"

scp -r rpeay@10.2.2.4:/home/pi/mosquitto "$HOME/docker/mosquitto"

sudo chmod -R 755 "$HOME/docker/mosquitto/"
sudo chown 1883:1883 "$HOME/docker/mosquitto/log/"
sudo chown 1883:1883 "$HOME/docker/mosquitto/data/"

# for m in $(docker images | tail -n +2 | awk '{print $1":"$2}' | sort | uniq | sed 's/:<none>$//g'); do docker image inspect "$m" | jq --raw-output -c '[.[].RepoTags[], .[].Architecture]'; done

# pinout