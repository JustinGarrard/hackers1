#! /bin/sh
amixer set Master 100%
bluetoothctl << EOF
discoverable on
pairable on
agent NoInputNoOutput
EOF
bt-agent -c NoInputNoOutput
