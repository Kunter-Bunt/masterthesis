#!/bin/bash

ifconfig wlp1s0 down
iwconfig wlp1s0 mode monitor
ifconfig wlp1s0 up

tshark -S -l -i wlp1s0 -Y 'wlan.fc.type_subtype eq 4' -T fields -e frame.time_epoch -e wlan.sa_resolved -e wlan.sa -e radiotap.dbm_antsignal  -e wlan.bssid_resolved -e wlan.bssid
