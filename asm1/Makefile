

#
# Create the object files for the static library (without -fPIC)
#
static:
	ar rcs lib/static/libstatic.a obj/my_staticlib.o 

#
# object files for shared libraries need to be compiled as position independent
# code (-fPIC) because they are mapped to any position in the address space.
#
shared:
	gcc -fPIC -shared obj/my_sharedlib.o -o lib/shared/libshared.so

link:
	gcc obj/main.o -Llib/static -lstatic -o bin/exam
	#gcc obj/main.o -Llib/shared -lshared -I./inc -o bin/exam

all: 
	gcc -c main.c -o obj/main.o -I./inc
	gcc -c src/my_staticlib.c -o obj/my_staticlib.o -I./inc
	gcc -c src/my_sharedlib.c -o obj/my_sharedlib.o -shared -I./inc


clean:
	rm -rf obj/* bin/* lib/static/* lib/shared/*
	
