#!/bin/bash
udm-login() {
  #shellcheck disable=2016
  USAGE='
    Usage:
    > udm-login [UDM.Address] [username] [*password*]
    # *Use an appropriate secrets method and NEVER type passwords directly into a terminal prompt.
    > udm-login 192,168.0.1 $(secret get UDM_USERNAME) $(secret get UDM_PASSWORD)
  '
  ARG_LENGTH="$#"
  if [ $ARG_LENGTH -eq "3" ]
  then
    UDM_COOKIE=$(mktemp)
    UDM_HEADERS=$(mktemp)
    curl --cookie "${UDM_COOKIE}" --cookie-jar "${UDM_COOKIE}" --insecure -H 'Content-Type: application/json' \
      -D "${UDM_HEADERS}" --data "{\"username\": \"$2\", \"password\": \"$3\"}" "https://$1/api/auth/login"
    UDM_CSRF="$(awk -v FS=': ' '/^x-csrf-token/{print $2}' "${UDM_HEADERS}" | tr -d '\r')"
    export UDM_COOKIE UDM_HEADERS UDM_CSRF
  else
    echo $USAGE
  fi
}

active-tasmotas() {
  curl -k --silent -b "${UDM_COOKIE}" \
    -H "Content-Type: application/json" \
    -H "X-CSRF-Token: ${UDM_CSRF}" \
    https://10.2.2.1/proxy/network/api/s/default/stat/sta | \
    jq -c '.data[] | select (.oui == "Espressif Inc.") '
}

all-tasmotas() {
  curl -k --silent -b "${UDM_COOKIE}" \
    -H "Content-Type: application/json" \
    -H "X-CSRF-Token: ${UDM_CSRF}" \
    https://10.2.2.1/proxy/network/api/s/default/rest/user | \
    jq -c '.data[] | select (.oui == "Espressif Inc.") | {mac,hostname,_id}'
}



