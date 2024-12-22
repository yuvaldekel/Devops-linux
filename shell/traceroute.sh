#! /bin/bash

for ttl in {1..128}
do
    result=$(ping -c 1 -t $ttl -W 2 $1 2> /dev/null)
  
    if [[ $result == *"FROM"*"Time to live exceeeded"* ]]; then
      	echo $result | awk 'NR==2 {print $ttl" "$2}'
    else
	      echo "$ttl * * *"
    fi

    if echo "$result" | grep -q "time="; then
        echo "Reached destination."
        break
    fi
    
done
