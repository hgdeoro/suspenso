#!/bin/bash

set -x

sudo ip addr add 10.5.5.1/24 dev {{ laptop_lan_dev }}
sudo iptables -I INPUT -i {{ laptop_lan_dev }} -j ACCEPT
sudo systemctl start isc-dhcp-server

sudo iptables -t nat -I POSTROUTING -s 10.5.5.5 -o {{ laptop_inet_dev }} -j MASQUERADE
sudo iptables  -I FORWARD -i {{ laptop_lan_dev }} -s 10.5.5.5 -j ACCEPT
echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward
