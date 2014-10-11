IDIR=-I include
SDIR=src

CC=gcc
CFLAGS=

PKG_CONFIG=`pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_dialog-5.0 allegro_primitives-5.0`

_SRC=main.c pi_display_tools.c pi_transform_tools.c

SRC=$(patsubst %,$(SDIR)/%,$(_SRC))

EXECUTABLE=adventurelog


all: 
	gcc $(SRC) -o $(EXECUTABLE) $(PKG_CONFIG) $(IDIR) -std=c99;
