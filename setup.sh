#!/bin/bash

ifconfig wlp1s0 down
iwconfig wlp1s0 mode monitor
ifconfig wlp1s0 up
