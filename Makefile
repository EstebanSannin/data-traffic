
NAME = dtraffic



all:
	echo "Compiling..."
	gcc -o $(NAME) implements.c data-traffic.c
