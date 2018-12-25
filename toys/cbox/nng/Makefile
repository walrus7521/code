all: client server

server: server.c
	clang -Wall server.c -o server -L/usr/local/lib -lnng

client: client.c
	clang -Wall client.c -o client -L/usr/local/lib -lnng

clean:
	rm -rf client server

