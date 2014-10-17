#ifndef H_PI_DATA
	#define H_PI_DATA
	#include <allegro5/allegro.h>
	
	#define TELA_AVENTURA 1
	#define TELA_PODERES  2
	#define NATIVE_SCREEN 3
	#define REFRESH 4
	#define YES 5
	#define	NO 6
	#define DIR_OPPOSITE -1 // inverte a direção do movimento
	#define DIR_KEEP 1 // mantém o moviment na direção atual
	
	#define LAYER_BG_FULL 2

typedef struct{
		ALLEGRO_BITMAP *canvas;
		int id;
		int x1;
		int x2;
		int y1;
		int y2;
		int width;
		int height;
		float scaledX;
		float scaledY;
		float scaledW;
		float scaledH;
} GameScreen;

typedef struct{
		ALLEGRO_DISPLAY *display;
		int width;
		int height;
		int mode;
		float scale;
} GameDisplay;

typedef struct {
		ALLEGRO_BITMAP *canvas;
		int looping;
		int x1;
		int y1;
		int animX;
		int animY;
		int direction;
		int depth;
		int width;
		int height;
		int layer;
} ImageTile;

typedef struct {
	int tileCount;
	int id;
	char fileNamePrefix[];
	char dirPath[];
	ImageTile tileSequence[];
} BGImageStream;

#endif

