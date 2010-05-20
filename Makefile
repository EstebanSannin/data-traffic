
NAME = dtraffic

all:
	gcc -o $(NAME) implements.c  parameters.c data-traffic.c

install:
	cp $(NAME) /bin
	rm dtraffic
