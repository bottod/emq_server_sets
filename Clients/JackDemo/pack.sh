#!/bin/sh
exe="mqtt_s" #name
des="/home/jack/Downloads/cli/" #path
deplist=$(ldd $exe | awk '{if(match($3,"/")){printf("%s "),$3}}')
cp $deplist $des
