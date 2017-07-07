#!/bin/bash

sudo tshark -i bluetooth0 -Y 'btcommon.eir_ad.entry.device_name == "Bluefruit52"' -T fields -e frame.time -e bthci_evt.bd_addr -e btcommon.eir_ad.entry.device_name -e bthci_evt.rssi
