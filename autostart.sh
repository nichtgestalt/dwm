#!/bin/sh

dwmblocks &
nitrogen --restore &
sxhkd -c ~/.config/erzengel/scripts/sxhkdrc-dwm &
picom --experimental-backends &
setxkbmap de neo &
unclutter -idle 3 -root &
xset r rate 250 30 &
