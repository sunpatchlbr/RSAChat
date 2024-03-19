CC = gcc
CFLAGS = -g -Wall
DEPS = RSA.h

%.o: %.c $(DEPS)
	$(CC) $< $(CFLAGS) -c -o $@

rsatest: main.o RSA.o
	$(CC) $(CFLAGS) -o rsatester main.o rsa.o
