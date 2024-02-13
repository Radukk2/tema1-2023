# Copyright 2023 Constantinescu Radu

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS = infinite_product codeinvim gigel_and_the_checkboard nomogram

build: $(TARGETS)

infinite_product: infinite_product.c
	$(CC) $(CFLAGS) infinite_product.c -lm -o infinite_product

codeinvim: codeinvim.c
	$(CC) $(CFLAGS) codeinvim.c -o codeinvim

gigel_and_the_checkboard: gigel_and_the_checkboard.c
	$(CC) $(CFLAGS) gigel_and_the_checkboard.c -o gigel_and_the_checkboard

nomogram: nomogram.c
	$(CC) $(CFLAGS) nomogram.c -o nomogram

pack:
	zip -FSr 323CA_ConstantinescuRadu_Ioan_Tema1.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
