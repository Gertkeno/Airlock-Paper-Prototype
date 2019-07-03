if [ -z "$1" ]; then
	echo "requires SDL dir"
	exit
fi

CXX="x86_64-w64-mingw32-g++"
SDL_DIR="$1/x86_64-w64-mingw32"

mkdir -p winobj/src

build() {
	$CXX -c $1 -o "winobj/${1%.*}.o" -I"$SDL_DIR/include/" -DSDL_MAIN_HANDLED
}

for file in src/*.c*; do
	echo "$file ..."
	build $file
done

OBJ_LIST=`find winobj/ -type f -iname '*.o'`
$CXX -o gr.exe $OBJ_LIST -L"$SDL_DIR/lib/" -lSDL2 -static-libgcc -static-libstdc++
