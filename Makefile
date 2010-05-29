
NAME = dtraffic
CC = gcc
all:
	$(CC) -o $(NAME) implements.c  parameters.c device.c data-traffic.c

install:
	cp $(NAME) /bin
	rm dtraffic
