#!/bin/sh
xhost +
sudo -H -u jason chromium --disable-audio-output --mute-audio --enable-gpu-rasterization --disable-pings --enable-remote-extensions --force-renderer-accessibility --disable-quic --enable-tcp-fast-open --enable-features=VaapiVideoDecoder --enable-accelerated-video-decode --ignore-gpu-blacklist --autoplay-policy=no-user-gesture-required --window-size=320,240 --window-position=10,10 --app=http://icast.tw/icast/educ/
