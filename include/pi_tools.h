/*
 * Biblioteca de ferramentas para controlar o display.
 * 
 * Codigo de ajuda para globalizar as variaveis display e displayBuffer:
 * 			http://cboard.cprogramming.com/game-programming/30462-draw-bitmap*-argument-allegro-objects-again.html
 * 			
*/

#ifndef PI_TOOLS
	#define PI_TOOLS
	#include <allegro5/allegro.h>
	#include "pi_data.h"
	
	extern ALLEGRO_DISPLAY *display;
	extern ALLEGRO_BITMAP *displayBuffer;
	extern ALLEGRO_BITMAP *telaAventura;
	extern ALLEGRO_BITMAP *telaPoderes;
	extern GameScreen gameScreen;
#endif

int pi_setFullScreen(GameScreen *nativeScreen, int *displayMode, int *displayWidth, int *displayHeight, int *gameScreenWidth,
						int *gameScreenHeight);

void setDisplayScale(int *startW, int *startH, int *targetW, int *targetH,
					float *displayScale, float *scaleW, float *scaleH, float *scaleX, float *scaleY);

int pi_setTelaAventura(int *gameScreenWidth, int *gameScreenHeight, int *telaA_x1, int *telaA_x2, int *telaA_y1, int *telaA_y2);
int pi_setTelaPoderes(int *gameScreenWidth, int *gameScreenHeight, int *telaP_x1, int *telaP_x2, int *telaP_y1, int *telaP_y2);

int pi_iniAllegroAddons(void);

int pi_iniScreens(GameScreen *nativeScreen, GameScreen *telaPoderes, GameScreen *telaAventura);
