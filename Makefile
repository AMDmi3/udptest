all: server client

server: server.c
	${CC} ${CFLAGS} -o server server.c

client: client.c
	${CC} ${CFLAGS} -o client client.c
