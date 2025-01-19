#!/usr/bin/bash

# check if running from the util root or playground dir
if [ -f "util.cpp" ]; then
	cd playground || exit 1
elif [ ! -f "playground.cpp" ]; then
	echo "This script was run from $(pwd)."
	echo "Please run from either the util root dir or the playground dir."
	exit 1
fi

if [ ! -d "build" ]; then
	echo "Build directory not found, creating..."
	mkdir build
	cd build || exit 1
	cmake ..
else
	cd build || exit 1
	if [ ! -f "CMakeCache.txt" ]; then
		echo "CMakeCache not found, running cmake..."
		cmake ..
	fi
fi

cmake --build .

if [ $? -ne 0 ]; then
	echo "Error with build."
	exit 1
fi

if [ $# -gt 0 ] && [ $1 = "run" ]; then
	./util_playground
else
	echo "Built only. If you want to run after build add 'run' argument."
fi

