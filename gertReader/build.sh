#!/bin/bash

build() {
	g++ -c "$1" -o "obj/${1%.*}.o" -Wall -Wextra -g -O0
}

if [ "$1" = "clean" ]; then
	echo "Clean build"
	rm obj/src/*.o
	for i in src/*.cpp; do
		echo "Building $i ..."
		build $i
	done
elif [ -z "$1" ]; then
	for i in src/*.cpp; do
		echo "Building $i ..."
		if [ "`md5sum $i`" != "`grep $i .hashes`" ]; then
			build $i
		else
			echo "No change"
		fi
	done
else
	echo "Just $1 ..."
	build $1
fi

md5sum src/*.cpp > .hashes

echo "Linking ..."
OBJ_LIST=`find obj/ -type f -iname "*.o"`
g++ -o gr $OBJ_LIST -lSDL2
