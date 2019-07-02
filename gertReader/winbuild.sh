CXX="x86_64-w64-mingw32-g++"
if [ -z "$1" ]; then
	echo "requires SDL dir"
	exit
fi

$CXX src/*.c* -o gr.exe -I"$1/x86_64-w64-mingw32/include/" -L"$1/x86_64-w64-mingw32/lib/" -lSDL2 -DSDL_MAIN_HANDLED -static-libgcc -static-libstdc++
