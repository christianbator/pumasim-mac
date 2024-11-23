#! /bin/zsh

# XQuartz graphics forwarding
defaults write org.xquartz.X11 nolisten_tcp -bool NO
defaults write org.xquartz.X11 no_auth -bool NO
defaults write org.xquartz.X11 enable_iglx -bool YES

mkdir -p ~/.xinitrc.d

cat << 'EOF' > ~/.xinitrc.d/xhost-config.sh
#!/bin/sh

xhost +localhost
xhost +\$(hostname)
EOF

chmod +x ~/.xinitrc.d/xhost-config.sh

green="\033[32m"
reset="\033[0m"

echo -e "> Successfully configured XQuartz ${green}✔${reset}"
