#!/system/bin/sh

# Open up port 5555 for adb
iptables -I INPUT -p tcp --dport 5555 -j ACCEPT -w

# Open up port 8888 for smartcar
iptables -I INPUT -p tcp --dport 8888 -j ACCEPT -w
