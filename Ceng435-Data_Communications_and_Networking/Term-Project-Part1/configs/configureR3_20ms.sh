s=$(getent ahosts "s" | cut -d " " -f 1 | uniq)
d=$(getent ahosts "d" | cut -d " " -f 1 | uniq)

s_adapter=$(ip route get $s | grep -Po '(?<=(dev )).*(?= src| proto)')
d_adapter=$(ip route get $d | grep -Po '(?<=(dev )).*(?= src| proto)')

#s_random_delay=$(( ( RANDOM % 50 )  + 80 ))"ms"
#d_random_delay=$(( ( RANDOM % 50 )  + 80 ))"ms"

sudo tc qdisc del dev $s_adapter root netem
sudo tc qdisc del dev $d_adapter root netem

sudo tc qdisc add dev $s_adapter root netem delay 20ms 5ms distribution normal
sudo tc qdisc add dev $d_adapter root netem delay 20ms 5ms distribution normal
