
#create executable file (.exe) from object file (.o)
asm201:
	gcc obj/asm201.o -o bin/exam

asm203:
	./bin/exam203 result203.txt 5 w "hello world"

asm204:
	./bin/exam204 pqc.txt
#create object file (.o) from c file (.c)
all: 
	gcc -c src/asm201.c -o obj/asm201.o -I./inc
	gcc -o ./bin/exam203 src/asm203.c -I./inc
	gcc -o ./bin/exam204 src/asm204.c -I./inc
clean:
	rm -rf obj/* bin/* 
	
