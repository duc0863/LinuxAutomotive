502:
	gcc -c src/asm502.c -o obj/asm502.o -I./inc
	gcc obj/asm502.o -o bin/exam
	./bin/exam

server:
	gcc obj/server.o -o bin/runserver
	./bin/runserver

client:
	gcc obj/client.o -o bin/runclient
	./bin/runclient

all: 
	gcc -c src/server.c -o obj/server.o -I./inc
	gcc -c src/client.c -o obj/client.o -I./inc


clean:
	rm -rf obj/* bin/* 
	