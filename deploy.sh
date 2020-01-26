#!/bin/bash

IP=192.168.1.9
PASSWORD=admin1252

sshpass -p $PASSWORD scp -r src/ CMakeLists.txt pi@$IP:/home/pi/iothings-zwave
sshpass -p $PASSWORD ssh -t pi@$IP "cd iothings-zwave; cmake -B build/; cmake --build build/"