/*
 * Biblioteca de ferramentas para controlar o display.
 *
 * Codigo de ajuda para globalizar as variaveis display e displayBuffer:
 * 			http://cboard.cprogramming.com/game-programming/30462-draw-bitmap*-argument-allegro-objects-again.html
 *
*/

#ifndef H_PI_TOOLS
	#define H_PI_TOOLS
	#include <allegro5/allegro.h>
	#include "pi_data.h"

	int pi_iniAllegroAddons(GameDisplay *);

	void pi_setDisplayScale	(GameScreen*, GameDisplay*);
	int pi_setFullScreen	(GameScreen*, GameDisplay*);
	int pi_setTelaAventura	(GameScreen*, GameScreen*, GameDisplay*);
	int pi_setTelaPoderes	(GameScreen*, GameScreen*, GameDisplay*);
	int pi_iniScreens		(GameScreen*, GameScreen*, GameScreen*);

	int pi_iniBackground	(BGImageStream*, GameScreen*, int);
	int pi_loadBackground	(BGImageStream*);
	int pi_animateBackground(BGImageStream*);

	int pi_iniSpriteGroup	 (SpriteGroup*, GameScreen*, int);
	int pi_loadStillSprite	 (SpriteGroup*, char*, char*);
	int pi_findSpriteByName	 (SpriteGroup*, char*);
	int pi_AnimateSprite	 (SpriteGroup*, GameScreen*);
	int pi_AnimateSpriteSheet(SpriteSheet*, GameScreen*);

#endif
