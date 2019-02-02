client: common.c client.c
	gcc -D_POSIX_THREADS -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto -lpthread thread.c common.c client.c -o client
clean:
	rm -rf client

