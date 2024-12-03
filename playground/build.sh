#!/usr/bin/bash

if [ ! -d "build" ]; then
	echo "Build directory not found, creating..."
	mkdir build
	cd build
	cmake ..
else
	cd build
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

