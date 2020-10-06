#!/bin/bash

run_os="`uname`"

if [ $run_os == "Darwin" ]; then
  export DYLD_LIBRARY_PATH=../lib
else
  export LD_LIBRARY_PATH=../lib
fi
../bin/ConvertImage --convert=../conf/convert_image.json