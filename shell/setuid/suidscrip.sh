#! /bin/bash

echo hello

current=$(ls -l trysuid | wc -l)
next=$((current-1))

echo $next
touch trysuid/file$next
