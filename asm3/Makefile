
#create executable file (.exe) from object file (.o)
asm301:
	gcc obj/asm301.o -o bin/exam

asm302:
	gcc obj/asm302.o -o bin/exam

asm303:
	gcc obj/asm303.o -o bin/exam

asm304:
	gcc obj/asm304.o -o bin/exam

asm305:
	gcc obj/asm305.o -o bin/exam

#create object file (.o) from c file (.c)
all: 
	gcc -c src/asm301.c -o obj/asm301.o -I./inc
	gcc -c src/asm302.c -o obj/asm302.o -I./inc
	gcc -c src/asm303.c -o obj/asm303.o -I./inc
	gcc -c src/asm304.c -o obj/asm304.o -I./inc
	gcc -c src/asm305.c -o obj/asm305.o -I./inc
clean:
	rm -rf obj/* bin/* 
	
