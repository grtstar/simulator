killall -9 lcm-tunnel
if [ x"$1" != x ]; then
    echo "#!/bin/bash" > ./src/lcm_tunnel/launch/scripts/lcm_tunnel.sh
    echo "lcm-tunnel $1" >> ./src/lcm_tunnel/launch/scripts/lcm_tunnel.sh
fi
roslaunch c1_description robot.launch
