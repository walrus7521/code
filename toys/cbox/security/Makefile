CC=gcc
CFLAGS= -g -Wall -D_POSIX_THREADS
INC_PATH= /usr/local/opt/openssl/include
LIB_PATH= /usr/local/opt/openssl/lib
LIBS= -lssl -lcrypto -lpthread
BINS= aes crypt sha256 sslconnect server prime engine
SYMS= aes.dSYM crypt.dSYM sha256.dSYM sslconnect.dSYM server.dSYM prime.dSYM engine.dSYM
RM= rm -rf

all: $(BINS)

aes: aes.c
	$(CC) $(CFLAGS) -I$(INC_PATH) -L$(LIB_PATH) $(LIBS) aes.c -o aes

crypt: crypt.c
	$(CC) $(CFLAGS) -I$(INC_PATH) -L$(LIB_PATH) $(LIBS) crypt.c -o crypt

sha256: sha256.c
	$(CC) $(CFLAGS) -I$(INC_PATH) -L$(LIB_PATH) $(LIBS) sha256.c -o sha256

sslconnect: sslconnect.c
	$(CC) $(CFLAGS) -I$(INC_PATH) -L$(LIB_PATH) $(LIBS) sslconnect.c -o sslconnect

server: server.c
	$(CC) $(CFLAGS) -I$(INC_PATH) -L$(LIB_PATH) $(LIBS) server.c -o server

prime: prime.c
	$(CC) $(CFLAGS) -I$(INC_PATH) -L$(LIB_PATH) $(LIBS) prime.c -o prime

engine: engine.c
	$(CC) $(CFLAGS) -I$(INC_PATH) -L$(LIB_PATH) $(LIBS) engine.c -o engine

clean:
	$(RM) $(BINS) $(SYMS)

