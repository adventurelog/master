INCLUDE=-I ../include
CC=gcc
CFLAGS=
PKG_CONFIG=`pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_dialog-5.0 allegro_primitives-5.0`
SRC=main.c pi_display_tools.c pi_transform_tools.c
OBJ=$(SRC:.c=.o)
EXECUTABLE=adventurelog

all: 
	gcc $(SRC) -o $(EXECUTABLE) $(PKG_CONFIG) $(INCLUDE) -std=c99 
