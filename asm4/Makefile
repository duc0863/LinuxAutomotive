#create executable file (.exe) from object file (.o)
asm401:
	gcc obj/asm401.o -o bin/exam

asm402:
	gcc obj/asm402.o -o bin/exam

asm403:
	gcc obj/asm403.o -o bin/exam

asm404:
	gcc obj/asm404.o -o bin/exam

asm405:
	gcc -c src/asm405.c -o obj/asm405.o -I./inc
	gcc obj/asm405.o -o bin/exam
	./bin/exam
asm406:
	gcc -c src/asm406.c -o obj/asm406.o -I./inc
	gcc obj/asm406.o -o bin/exam
	./bin/exam
#create object file (.o) from c file (.c)
all: 
	gcc -c src/asm401.c -o obj/asm401.o -I./inc
	gcc -c src/asm402.c -o obj/asm402.o -I./inc
	gcc -c src/asm403.c -o obj/asm403.o -I./inc
	gcc -c src/asm404.c -o obj/asm404.o -I./inc
	gcc -c src/asm405.c -o obj/asm405.o -I./inc
	gcc -c src/asm406.c -o obj/asm406.o -I./inc
clean:
	rm -rf obj/* bin/* 
	

