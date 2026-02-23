#!/bin/bash
set -e

make
sudo cp dist/cedit /usr/local/bin/cedit

echo "Installed: run with -> cedit file.txt"