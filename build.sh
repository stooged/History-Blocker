#!/bin/bash
set -e
pushd tool
make
popd
pushd History_Blocker
make
popd
mkdir -p bin
rm -f bin/History_Blocker.bin
cp History_Blocker/History_Blocker.bin bin/History_Blocker.bin
mkdir -p html_payload
tool/bin2js bin/History_Blocker.bin > html_payload/payload.js
FILESIZE=$(stat -c%s "bin/History_Blocker.bin")
PNAME=$"History Blocker"
cp exploit.template html_payload/History_Blocker.html
sed -i -f - html_payload/History_Blocker.html << EOF
s/#NAME#/$PNAME/g
s/#BUF#/$FILESIZE/g
s/#PAY#/$(cat html_payload/payload.js)/g
EOF
rm -f History_Blocker/History_Blocker.bin
rm -f html_payload/payload.js
