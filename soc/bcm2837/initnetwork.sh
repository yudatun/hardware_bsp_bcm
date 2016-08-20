#!/system/bin/sh

# Setup networking when boot starts
#ifconfig eth0 10.0.0.25 netmask 255.255.255.0 up
#route add default gw 10.0.0.1

# Open up port 5555 for adb
iptables -I INPUT -p tcp --dport 5555 -j ACCEPT -w

iptables -I INPUT -p tcp --dport 80 -j ACCEPT -w
iptables -I INPUT -p tcp --dport 443 -j ACCEPT -w
