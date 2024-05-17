#!/bin/sh

while :
do
	if [[ -e '/usr/sbin/openvpn' ]]; then
		echo "openvpn exist"
	else
		echo "no openvpn, quit!"
		exit
	fi
	if [[ -e '/etc/venom_hualien_001.ovpn' ]]; then
		echo "ovpn client config exist!"
	else
		echo "no ovpn client !"
		exit
	fi

	openvpn /etc/venom_hualien_001.ovpn  #client file need to change every machine
	sleep 5
done
