#!bin/sh

hostname=$(hostname)
architecture=$(uname -a | sed 's/PREEMPT_DYNAMIC //g')
cpu_phys=$(lscpu | grep -m 1 'CPU(s):' | awk '{print $2}' )
cpu_virt=$(nproc)
mem_usg=$(free -m | awk 'NR==2{printf "%s/%sMB (%.2f%%)", $3, $2, $3 * 100 / $2 }')

echo "Broadcast Message from $(hostname)\\n"
echo "	#Architecture: $architecture"
echo "	#CPU physical : $cpu_phys" 
echo "	#vCPU : $cpu_virt"
echo "	#Memory Usage: $mem_usg"

df -k -H ~ | awk 'NR==2{printf "	#Disk Usage: %.1f/%.1fGB (%.2f%%)\n", $3, $2, $3 * 100 / $2 }'
