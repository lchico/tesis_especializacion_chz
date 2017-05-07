#!/bin/bash

while [ 1 ] ; do
	sed -i "s/ON/OFF/" ajax.shtml
	sleep 2
	sed -i "s/OFF/ON/" ajax.shtml
	sleep 2
done

