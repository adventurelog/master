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

int pi_setFullScreen(GameScreen *nativeScreen, GameDisplay *gameDisplay);

void pi_setDisplayScale(GameScreen *nativeScreen, GameDisplay *display);

int pi_setTelaAventura(GameScreen *nativeScreen, GameScreen *telaAventura, GameDisplay *display);
int pi_setTelaPoderes(GameScreen *nativeScreen, GameScreen *telaPoderes, GameDisplay *display);

int pi_iniAllegroAddons(GameDisplay *display);

int pi_iniScreens(GameScreen *nativeScreen, GameScreen *telaPoderes, GameScreen *telaAventura);
