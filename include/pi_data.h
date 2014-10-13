#ifndef PI_DATA
	#define PI_DATA
	#include <allegro5/allegro.h>

/*	
	extern ALLEGRO_DISPLAY *display;
	extern ALLEGRO_BITMAP *displayBuffer;
	extern ALLEGRO_BITMAP *telaAventura;
	extern ALLEGRO_BITMAP *telaPoderes;
*/
	#define TELA_AVENTURA 1
	#define TELA_PODERES  2
	#define NATIVE_SCREEN 3
	#define REFRESH 1

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

#endif

