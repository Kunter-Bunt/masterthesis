#!/bin/bash

while :; do
	nmcli r wifi on
	date 
	echo "Starting Hotspot"
	nmcli d wifi hotspot ssid ideapad password XCV,234,xcv &
	sleep 900
	date
	echo "Killing Hotspot"
	nmcli r wifi off
	sleep 300
done
