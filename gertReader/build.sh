#!/bin/bash

CXX="g++"

build() {
	$CXX -c "$1" -o "obj/${1%.*}.o" -Wall -Wextra $2
}

hashed_build() {
	for i in src/*.c*; do
		echo "Building $i ..."
		if [ "`md5sum $i`" != "`grep $i .hashes`" ]; then
			build $i $1
		else
			echo "No change"
		fi
	done
}

clean_build() {
	echo "Clean build"
	rm obj/src/*.o
	for i in src/*.c*; do
		echo "Building $i ..."
		build $i $1
	done
}

mkdir -p obj/src/

if [ "$1" = "clean" ]; then
	clean_build "-g O0"
elif [ "$1" = "release" ]; then
	clean_build "-DNDEBUG -O3"
elif [ -z "$1" ]; then
	hashed_build "-g -O0"
else
	echo "Just $1 ..."
	build $1
fi

md5sum src/*.cpp > .hashes

echo "Linking ..."
OBJ_LIST=`find obj/ -type f -iname "*.o"`
$CXX -o gr $OBJ_LIST -lSDL2
