#
# Author:   Stefano Viola
# Licenze:  GPLv3
#
#
#
NAME = dtraffic
CC = gcc
all:
	$(CC) -o $(NAME) implements.c data-traffic.c

install:
	cp $(NAME) /bin
	rm dtraffic
