#!/bin/bash

mkdir -p libs/spacebattle/include/autogenerated/adapters
mkdir -p libs/spacebattle/include/autogenerated/interfaces
cd autogenerator/
./build_autogen.sh
cd ..
./autogenerator/build/autogenerator libs/spacebattle/ifaceproto/ libs/spacebattle/include/autogenerated/

