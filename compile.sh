#!/bin/sh

BUILD_DIR="build"

if [ $# -eq 0 ]; then
  echo "./compile.sh -m  =  Create makefile build\n./compile.sh -c  =  Compile existing makefiles"
  exit
fi


if [ "${1}" = "-m" ]; then
  mkdir ${BUILD_DIR}
  cd ${BUILD_DIR}
  cmake ..
fi

if [ "${1}" = "-c" ]; then
  cd ${BUILD_DIR}
  make -j4
fi
