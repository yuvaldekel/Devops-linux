#! /bin/bash

for ttl in {1..128}
do
    result=$(ping -c 1 -t $ttl -W 2 $1 2> /dev/null)
  
    if [[ $result =~ "Time to live exceeded" ]]; then
      	awk -v ttl="$ttl" 'NR==2 {print ttl" "$2}' <<< "$result"
    
    elif echo "$result" | grep -q "time="; then
      	awk -v ttl="$ttl" 'NR==1 {print ttl" "$2}' <<< "$result"
        echo "Reached destination."
        break
    
    else
        echo "$ttl * * *"
    fi

done
