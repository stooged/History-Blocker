#!/bin/bash
pushd tool
make clean
popd
pushd History_Blocker
make clean
popd
rm -f html_payload/History_Blocker.html
rm -f bin/History_Blocker.bin

