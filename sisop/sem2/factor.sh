#!/bin/bash
# factor.sh

n=$1
first=1
for (( i=2; i<=n; i++ )); do
    while (( n % i == 0 )); do
        if [ $first -ne 1 ]; then
            echo -n " "
        fi
        echo -n "$i"
        (( n /= i ))
        first=0
    done
done
echo
