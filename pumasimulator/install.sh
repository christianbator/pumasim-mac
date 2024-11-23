#!/bin/bash

echo "Installing the simulator into /opt/pumasim"

# Clean up previous installed files
rm -r /opt/pumasim 2> /dev/null
cp -r pumasim /opt

"Create a symbolic link to the binary file"
ln -sf /opt/pumasim/pumasim /usr/local/bin/pumasim 2> /dev/null
