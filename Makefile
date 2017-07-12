all: folder cliente servidor
INC		= -I./inc
CC_BBB  = arm-linux-gnueabihf-gcc
ARQ		= obj/server.o \
		  obj/IP.o 

ARQ_BBB = obj/cliente.o \
		  obj/IP.o

cliente:
	$(CC_BBB) $(INC) -c src/cliente.c -o obj/cliente.o
	$(CC_BBB) $(INC) -c src/IP.c -o obj/IP.o
	$(CC_BBB) $(ARQ_BBB) -o bin/cliente.x

servidor:
	gcc $(INC) -c src/server.c -o obj/server.o
	gcc $(INC) -c src/IP.c -o obj/IP.o
	gcc $(ARQ) -o bin/server.x -lpthread

folder:
	mkdir -p obj bin

clean:
	rm -f obj/*.o bin/*.x
