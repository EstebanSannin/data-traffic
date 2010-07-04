#
# Author:   Stefano Viola
# Licenze:  GPLv3
#
#
#
NAME = ethFix

all: compile
	

compile:
	$(CC) -o $(NAME) implements.c main.c
