aes: aes.c
	gcc -D_POSIX_THREADS -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto -lpthread aes.c -o aes

crypt: crypt.c
	gcc -D_POSIX_THREADS -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto -lpthread crypt.c -o crypt

sha256: sha256.c
	gcc -D_POSIX_THREADS -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto -lpthread sha256.c -o sha256

sslconnect: sslconnect.c
	gcc -D_POSIX_THREADS -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto -lpthread sslconnect.c -o sslconnect

server: server.c
	gcc -D_POSIX_THREADS -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto -lpthread server.c -o server

clean:
	rm -rf aes crypt sha256 sslconnect server

