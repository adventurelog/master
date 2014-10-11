/*
 * Biblioteca de ferramentas para controlar o display.
 * 
 * Codigo de ajuda para globalizar as variaveis display e displayBuffer:
 * 			http://cboard.cprogramming.com/game-programming/30462-draw-bitmap*-argument-allegro-objects-again.html
*/

#ifndef PI_DISPLAY_TOOLS
	#define PI_DISPLAY_TOOLS
	#include <allegro5/allegro.h>
	
	extern ALLEGRO_DISPLAY *display;
	extern ALLEGRO_BITMAP *displayBuffer;
#endif

int pi_setFullScreen(int *displayMode, int *displayWidth, int *displayHeight, int *gameScreenWidth,
						int *gameScreenHeight);
