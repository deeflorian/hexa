CPPFLAGS = -g -O2 -Wall
# -g: requests the compiler and linker to generate and retain symbol information in the executable itself
LDFLAGS = -lm -lGL -lglut -lGLU -lX11 -lrt
# -lm: linker option, tells the linker to link with (-l) the m library (libm.so/dll). That's the math library. You often need it if you #include <math.h>.

main: main.cc 3d_ext.cc blocklist.cc camera.cc level.cc 3d_ext.h blocklist.h camera.h level.h shifter.hpp
	g++ main.cc 3d_ext.cc blocklist.cc camera.cc level.cc -o main $(CFLAGS) $(LDFLAGS)

clean:
	rm main
