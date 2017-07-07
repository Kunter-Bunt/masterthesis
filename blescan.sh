#!/bin/bash

while :; do
	date
	hcitool lescan &
	sleep 1
	pkill -P -2 $$
	hciconfig hci0 down
	hciconfig hci0 up
	sleep 1
	echo ""
	echo ""
done
#!/bin/bash

while :
do
	sudo timeout 1s hcitool lescan
done

