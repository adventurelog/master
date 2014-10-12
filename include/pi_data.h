#ifndef PI_DATA
	#define PI_DATA
	#include <allegro5/allegro.h>
	
	extern ALLEGRO_DISPLAY *display;
	extern ALLEGRO_BITMAP *displayBuffer;
	extern ALLEGRO_BITMAP *telaAventura;
	extern ALLEGRO_BITMAP *telaPoderes;

typedef struct{
		ALLEGRO_BITMAP *canvas;
		int x1;
		int x2;
		int y1;
		int y2;
		int width;
		int height;
		float DisplayScale;
		float scaledX;
		float scaledY;
		float scaledW;
		float scaledH;
	} GameScreen;
#endif

