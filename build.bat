g++ -c -I%JAVA_HOME%\include -I%JAVA_HOME%\include\win32 miniz.c bot_Decompress.cpp
g++ -shared -o bot_Decompress.dll miniz.o bot_Decompress.o -Wl,--add-stdcall-alias