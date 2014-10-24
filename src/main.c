/*
 * Baseado nos seguitnes códigos-fonte:
 * 		https://wiki.allegro.cc/index.php?title=Achieving_Resolution_Independence
 * 		https://wiki.allegro.cc/index.php?title=Allegro_5_Tutorial/Displays
 * 		https://wiki.allegro.cc/index.php?title=Creating_a_fullscreen_display_with_maximum/minimum_resolution
 * 		https://wiki.allegro.cc/index.php?title=Basic_Keyboard_Example
 *
 */

#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pi_tools.h"
#include "pi_data.h"

/* Para ativar/desativar o debug, descomentar/comentar a linha abaixo */
//#define _SET_DEBUG_ON
#ifdef 	_SET_DEBUG_ON
	#define DEBUG_ON printf
#endif
#ifndef _SET_DEBUG_ON
	#define DEBUG_ON //
#endif

//----------------------------------------------------------------------
int pi_drawGraphics(ALLEGRO_BITMAP *image, float x, float y, int refresh, GameScreen *tela, GameScreen *nativeScreen, GameDisplay *display);

//======================================================================
int main(int argc, char **argv[]){
	printf("\n================================");
	printf("\ndebug:main():start");
	printf("\n================================");

	GameScreen nativeScreen; // tela original do jogo.
	GameScreen telaAventura;
	GameScreen telaPoderes;
	GameDisplay gameDisplay = {.mode = 0}; // display onde aparecem as telas de Aventura e Poderes
	BGImageStream sceneGrass;
	BGImageStream sceneGrass2;
	BGImageStream treeLine1;
	SpriteGroup spriteGroupSky;
    SpriteGroup spriteGroupTrees;
    SpriteGroup spriteGroupTrees2;
    SpriteGroup spriteGroupGrass;
    SpriteGroup spriteGroupGrass2;
    SpriteGroup spriteGroupTombs;
    SpriteGroup spriteGroupFog;
    SpriteGroup spriteGroupFog2;
    SpriteGroup spriteGroupGround;
    SpriteGroup spriteGroupGhost;
    //StillSprite spriteArrayGrass[20];

    int spriteNum = -1;
	int i;
	srand(10);

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *gameTimer = NULL;
	int exitGame = 0, redraw = false;

	/* Inicia todos os addons utilizados no jogo. */
	if (pi_iniAllegroAddons(&gameDisplay) < 0)
		return -1;

	gameTimer = al_create_timer(1.0 / FPS);

	/* Configura as telas do jogo*/
	pi_iniScreens(&nativeScreen, &telaAventura, &telaPoderes); // Inicializa as telas do jogo.
	DEBUG_ON("\ndebug:nativeScreen:x2=%f", nativeScreen.x2);

	/* Configura BACKGROUND*/
	//pi_iniBackground(&sceneGrass, &nativeScreen, LAYER_SCENE_GRASS);
	//pi_loadBackground(&sceneGrass);

	//pi_iniBackground(&sceneGrass2, &nativeScreen, LAYER_SCENE_GRASS_2);
	//pi_loadBackground(&sceneGrass2);

	//pi_iniBackground(&treeLine1, &nativeScreen, LAYER_SCENE_TREELINE_1);
	//pi_loadBackground(&treeLine1);

	/* Configura SPRITES*/
	pi_iniSpriteGroup(&spriteGroupGround, &nativeScreen, ID_GROUP_SPRITES_GROUND);
	pi_loadStillSprite(&spriteGroupGround, "ground", "ground");

	pi_iniSpriteGroup(&spriteGroupGhost, &nativeScreen, ID_GROUP_SPRITES_GHOST);
	pi_loadStillSprite(&spriteGroupGhost, "ghost1", "ghost1");
	pi_loadStillSprite(&spriteGroupGhost, "ghost1", "ghost2");
	pi_loadStillSprite(&spriteGroupGhost, "ghost1", "ghost3");

	pi_iniSpriteGroup(&spriteGroupFog, &nativeScreen, ID_GROUP_SPRITES_FOG);
	pi_loadStillSprite(&spriteGroupFog, "fog2", "fog2");
	pi_loadStillSprite(&spriteGroupFog, "fog3", "fog3");
	pi_loadStillSprite(&spriteGroupFog, "fog4", "fog4");
	pi_loadStillSprite(&spriteGroupFog, "fog5", "fog5");
	pi_loadStillSprite(&spriteGroupFog, "fog6", "fog6");

	pi_iniSpriteGroup(&spriteGroupFog2, &nativeScreen, ID_GROUP_SPRITES_FOG);
	pi_loadStillSprite(&spriteGroupFog2, "fog4", "fog4");
	pi_loadStillSprite(&spriteGroupFog2, "fog6", "fog6");
	pi_loadStillSprite(&spriteGroupFog2, "fog3", "fog3");
	pi_loadStillSprite(&spriteGroupFog2, "fog5", "fog5");

	pi_iniSpriteGroup(&spriteGroupTombs, &nativeScreen, ID_GROUP_SPRITES_TOMBS);
	pi_loadStillSprite(&spriteGroupTombs, "cross1", "cross1");
	pi_loadStillSprite(&spriteGroupTombs, "cross2", "cross2");
	pi_loadStillSprite(&spriteGroupTombs, "cross3", "cross3");
	pi_loadStillSprite(&spriteGroupTombs, "tomb1", "tomb1");
	pi_loadStillSprite(&spriteGroupTombs, "cross2", "cross2");
	pi_loadStillSprite(&spriteGroupTombs, "tomb1", "tomb1");
	pi_loadStillSprite(&spriteGroupTombs, "tomb2", "tomb2");
	pi_loadStillSprite(&spriteGroupTombs, "tomb1", "tomb1");
	pi_loadStillSprite(&spriteGroupTombs, "tomb2", "tomb2");
	pi_loadStillSprite(&spriteGroupTombs, "cross3", "cross3");
	pi_loadStillSprite(&spriteGroupTombs, "tomb1", "tomb1");
	pi_loadStillSprite(&spriteGroupTombs, "tomb2", "tomb2");

	pi_iniSpriteGroup(&spriteGroupGrass, &nativeScreen, ID_GROUP_SPRITES_GRASS);
	pi_loadStillSprite(&spriteGroupGrass, "grass_0", "grass_0");
	pi_loadStillSprite(&spriteGroupGrass, "grass_1", "grass_1");
	pi_loadStillSprite(&spriteGroupGrass, "grass_2", "grass_2");
	pi_loadStillSprite(&spriteGroupGrass, "grass_3", "grass_3");
	pi_loadStillSprite(&spriteGroupGrass, "grass_4", "grass_4");
	pi_loadStillSprite(&spriteGroupGrass, "grass_5", "grass_5");
	pi_loadStillSprite(&spriteGroupGrass, "grass_6", "grass_6");
	pi_loadStillSprite(&spriteGroupGrass, "grass_0", "grass_7");
	pi_loadStillSprite(&spriteGroupGrass, "grass_1", "grass_8");
	pi_loadStillSprite(&spriteGroupGrass, "grass_2", "grass_9");
	pi_loadStillSprite(&spriteGroupGrass, "grass_3", "grass_10");
	pi_loadStillSprite(&spriteGroupGrass, "grass_4", "grass_12");
	pi_loadStillSprite(&spriteGroupGrass, "grass_0", "grass_13");
	pi_loadStillSprite(&spriteGroupGrass, "grass_6", "grass_14");
	pi_loadStillSprite(&spriteGroupGrass, "grass_1", "grass_15");
	pi_loadStillSprite(&spriteGroupGrass, "grass_2", "grass_16");
	pi_loadStillSprite(&spriteGroupGrass, "grass_3", "grass_17");
	pi_loadStillSprite(&spriteGroupGrass, "grass_4", "grass_18");
	pi_loadStillSprite(&spriteGroupGrass, "grass_5", "grass_19");
	pi_loadStillSprite(&spriteGroupGrass, "grass_3", "grass_20");
	pi_loadStillSprite(&spriteGroupGrass, "grass_4", "grass_21");
	pi_loadStillSprite(&spriteGroupGrass, "grass_5", "grass_22");
	pi_loadStillSprite(&spriteGroupGrass, "grass_6", "grass_23");
	pi_loadStillSprite(&spriteGroupGrass, "grass_0", "grass_24");
	pi_loadStillSprite(&spriteGroupGrass, "grass_1", "grass_25");
	pi_loadStillSprite(&spriteGroupGrass, "grass_2", "grass_26");
	pi_loadStillSprite(&spriteGroupGrass, "grass_3", "grass_27");
	pi_loadStillSprite(&spriteGroupGrass, "grass_4", "grass_28");
	pi_loadStillSprite(&spriteGroupGrass, "grass_5", "grass_29");
	pi_loadStillSprite(&spriteGroupGrass, "grass_5", "grass_30");
	pi_loadStillSprite(&spriteGroupGrass, "grass_3", "grass_31");
	pi_loadStillSprite(&spriteGroupGrass, "grass_4", "grass_32");
	pi_loadStillSprite(&spriteGroupGrass, "grass_5", "grass_33");
	pi_loadStillSprite(&spriteGroupGrass, "grass_3", "grass_34");

	pi_iniSpriteGroup(&spriteGroupSky, &nativeScreen, ID_GROUP_SPRITES_SKY);
	pi_loadStillSprite(&spriteGroupSky, "moon", "moon");
	pi_loadStillSprite(&spriteGroupSky, "sky", "moon");

    pi_iniSpriteGroup(&spriteGroupTrees, &nativeScreen, ID_GROUP_SPRITES_TREES);
    pi_loadStillSprite(&spriteGroupTrees, "tree3", "tree2");
    pi_loadStillSprite(&spriteGroupTrees, "tree6", "tree3");
    pi_loadStillSprite(&spriteGroupTrees, "tree3", "tree4");
    pi_loadStillSprite(&spriteGroupTrees, "tree1", "tree5");
    pi_loadStillSprite(&spriteGroupTrees, "tree3", "tree6");
    pi_loadStillSprite(&spriteGroupTrees, "tree7", "tree7");
    pi_loadStillSprite(&spriteGroupTrees, "tree1", "tree8");

    pi_iniSpriteGroup(&spriteGroupTrees2, &nativeScreen, ID_GROUP_SPRITES_TREES);
    pi_loadStillSprite(&spriteGroupTrees2, "tree8", "tree2");
    pi_loadStillSprite(&spriteGroupTrees2, "tree2", "tree3");
    pi_loadStillSprite(&spriteGroupTrees2, "tree5", "tree4");
    pi_loadStillSprite(&spriteGroupTrees2, "tree2", "tree5");
    pi_loadStillSprite(&spriteGroupTrees2, "tree4", "tree6");
    pi_loadStillSprite(&spriteGroupTrees2, "tree8", "tree7");
    pi_loadStillSprite(&spriteGroupTrees2, "tree5", "tree8");

//	spriteNum = pi_findSpriteByName(&spriteGroupSky, "moon");
	
	// Configura a nevoa
	for (i = 0; i < spriteGroupFog.arraySize - 1; i++){	
		if (spriteGroupFog.spriteArray[i].canvas != NULL){
			spriteGroupFog.spriteArray[i].x1 			= (i * spriteGroupFog.spriteArray[i].width);
			printf("\nx1:%f", spriteGroupGrass.spriteArray[i].x1);
			spriteGroupFog.spriteArray[i].y1 			= 940;
			spriteGroupFog.spriteArray[i].depth 		= 0.85;
			spriteGroupFog.spriteArray[i].directionX 	= -1;
			spriteGroupFog.spriteArray[i].directionY 	= 1;
			spriteGroupFog.spriteArray[i].speedX 		= 1.0;
			spriteGroupFog.spriteArray[i].speedY 		= 0.0;
			spriteGroupFog.spriteArray[i].startY 		= spriteGroupFog.spriteArray[i].y1;
			spriteGroupFog.spriteArray[i].startX 		= 1920 + spriteGroupFog.spriteArray[i].x1;
			spriteGroupFog.spriteArray[i].endY   		= spriteGroupFog.spriteArray[i].y1;
			spriteGroupFog.spriteArray[i].endX 	    	= 0.0;
			printf("\nstartX:%f", spriteGroupFog.spriteArray[i].startX);
			spriteGroupFog.spriteArray[i].id 	    	= 4;
			spriteGroupFog.spriteArray[i].loop 	   		= YES;
		}	
	}
	for (i = 0; i < spriteGroupFog2.arraySize - 1; i++){	
		if (spriteGroupFog2.spriteArray[i].canvas != NULL){
			spriteGroupFog2.spriteArray[i].x1 			= (i * spriteGroupFog2.spriteArray[i].width) + 200;
			printf("\nx1:%f", spriteGroupFog2.spriteArray[i].x1);
			spriteGroupFog2.spriteArray[i].y1 			= 940;
			spriteGroupFog2.spriteArray[i].depth 		= 0.95;
			spriteGroupFog2.spriteArray[i].directionX 	= -1;
			spriteGroupFog2.spriteArray[i].directionY 	= 1;
			spriteGroupFog2.spriteArray[i].speedX 		= 1.0;
			spriteGroupFog2.spriteArray[i].speedY 		= 0.0;
			spriteGroupFog2.spriteArray[i].startY 		= spriteGroupFog2.spriteArray[i].y1;
			spriteGroupFog2.spriteArray[i].startX 		= 1920 + spriteGroupFog2.spriteArray[i].x1;
			spriteGroupFog2.spriteArray[i].endY   		= spriteGroupFog2.spriteArray[i].y1;
			spriteGroupFog2.spriteArray[i].endX 	   	= 0.0;
			printf("\nstartX:%f", spriteGroupFog.spriteArray[i].startX);
			spriteGroupFog2.spriteArray[i].id 	    	= 4;
			spriteGroupFog2.spriteArray[i].loop 	   	= YES;
		}	
	}

	// Configura a grama
	for (i = 0; i < spriteGroupGrass.arraySize - 1; i++){	
		if (spriteGroupGrass.spriteArray[i].canvas != NULL){
			spriteGroupGrass.spriteArray[i].x1 			= (i * spriteGroupGrass.spriteArray[i].width);
			printf("\nx1:%f", spriteGroupGrass.spriteArray[i].x1);
			spriteGroupGrass.spriteArray[i].y1 			= 1080  - 40;
			spriteGroupGrass.spriteArray[i].depth 		= 1.7;
			spriteGroupGrass.spriteArray[i].directionX 	= -1;
			spriteGroupGrass.spriteArray[i].directionY 	= 1;
			spriteGroupGrass.spriteArray[i].speedX 		= 1.0;
			spriteGroupGrass.spriteArray[i].speedY 		= 0.0;
			spriteGroupGrass.spriteArray[i].startY 		= spriteGroupGrass.spriteArray[i].y1;
			spriteGroupGrass.spriteArray[i].startX 		= 1920 + spriteGroupGrass.spriteArray[i].x1;
			spriteGroupGrass.spriteArray[i].endY   		= spriteGroupGrass.spriteArray[i].y1;
			spriteGroupGrass.spriteArray[i].endX 	    = 0.0;
			printf("\nstartX:%f", spriteGroupGrass.spriteArray[i].startX);
			spriteGroupGrass.spriteArray[i].id 	    	= 4;
			spriteGroupGrass.spriteArray[i].loop 	    = YES;
		}	
	}
    spriteGroupGrass2 = spriteGroupGrass;
	for (i = 0; i < spriteGroupGrass2.arraySize - 1; i++){	
		if (spriteGroupGrass2.spriteArray[i].canvas != NULL){
			spriteGroupGrass2.spriteArray[i].x1 			= (i * spriteGroupGrass2.spriteArray[i].width);
			spriteGroupGrass2.spriteArray[i].y1 			= 1080  - 50;
			spriteGroupGrass2.spriteArray[i].depth 		= 1.0;
			spriteGroupGrass2.spriteArray[i].directionX 	= -1;
			spriteGroupGrass2.spriteArray[i].directionY 	= 1;
			spriteGroupGrass2.spriteArray[i].speedX 		= 1.0;
			spriteGroupGrass2.spriteArray[i].speedY 		= 0.0;
			spriteGroupGrass2.spriteArray[i].startY 		= spriteGroupGrass2.spriteArray[i].y1;
			spriteGroupGrass2.spriteArray[i].startX 		= 1920 + spriteGroupGrass2.spriteArray[i].x1;
			spriteGroupGrass2.spriteArray[i].endY   		= spriteGroupGrass2.spriteArray[i].y1;
			spriteGroupGrass2.spriteArray[i].endX 	    = 0.0;
			spriteGroupGrass2.spriteArray[i].id 	    	= 4;
			spriteGroupGrass2.spriteArray[i].loop 	    = YES;
		}	
	}

//	Configura a lua
		spriteGroupSky.spriteArray[0].x1 			= 400;
		spriteGroupSky.spriteArray[0].y1 			= 210;
		spriteGroupSky.spriteArray[0].depth 		= 0.1;
		spriteGroupSky.spriteArray[0].directionX 	= -1;
		spriteGroupSky.spriteArray[0].directionY 	= 1;
		spriteGroupSky.spriteArray[0].speedX 		= 0.4;
		spriteGroupSky.spriteArray[0].speedY 		= 0.0;
        spriteGroupSky.spriteArray[0].startY 		= 0.0;
        spriteGroupSky.spriteArray[0].startX 		= 0.0;
        spriteGroupSky.spriteArray[0].endY   		= 0.0;
        spriteGroupSky.spriteArray[0].endX 	    	= 0.0;
        spriteGroupSky.spriteArray[0].id 	    	= 1;
        spriteGroupSky.spriteArray[0].loop 	    	= NO;

//	Configura a o céu de fundo
		spriteGroupSky.spriteArray[1].x1 			= 0;
		spriteGroupSky.spriteArray[1].y1 			= 1080 - spriteGroupSky.spriteArray[1].height;
		spriteGroupSky.spriteArray[1].depth 		= 1.0;
		spriteGroupSky.spriteArray[1].directionX 	= 1;
		spriteGroupSky.spriteArray[1].directionY 	= 1;
		spriteGroupSky.spriteArray[1].speedX 		= 0.0;
		spriteGroupSky.spriteArray[1].speedY 		= 0.0;
        spriteGroupSky.spriteArray[1].startY 		= 0.0;
        spriteGroupSky.spriteArray[1].startX 		= 0.0;
        spriteGroupSky.spriteArray[1].endY   		= 0.0;
        spriteGroupSky.spriteArray[1].endX 	    	= 0.0;
        spriteGroupSky.spriteArray[1].id 	    	= 1;
        spriteGroupSky.spriteArray[1].loop 	    	= NO;

//	Configura o chão
		spriteGroupGround.spriteArray[0].x1 			= 0;
		spriteGroupGround.spriteArray[0].y1 			= 1080 - spriteGroupGround.spriteArray[0].height;
		spriteGroupGround.spriteArray[0].depth 			= 1.0;
		spriteGroupGround.spriteArray[0].directionX 	= 1;
		spriteGroupGround.spriteArray[0].directionY 	= 1;
		spriteGroupGround.spriteArray[0].speedX 		= 0.0;
		spriteGroupGround.spriteArray[0].speedY 		= 0.0;
        spriteGroupGround.spriteArray[0].startY 		= 0.0;
        spriteGroupGround.spriteArray[0].startX 		= 0.0;
        spriteGroupGround.spriteArray[0].endY   		= 0.0;
        spriteGroupGround.spriteArray[0].endX 	    	= 0.0;
        spriteGroupGround.spriteArray[0].id 	    	= 1;
        spriteGroupGround.spriteArray[0].loop 	    	= NO;

//	Configura os fantasmas
	for (i = 0; i < spriteGroupGhost.arraySize - 1; i++){	
		if (spriteGroupGhost.spriteArray[i].canvas != NULL){
			float r = (rand() / 1000000000.0);
			float r2 = (rand() / 1000000000.0);
			spriteGroupGhost.spriteArray[i].x1 			= 1920 + (r * r);
			spriteGroupGhost.spriteArray[i].y1 			= 990;
			spriteGroupGhost.spriteArray[i].depth 		= 1.5;
			spriteGroupGhost.spriteArray[i].directionX 	= -1;
			spriteGroupGhost.spriteArray[i].directionY 	= 1;
			spriteGroupGhost.spriteArray[i].speedX 		= 2.0 * r;
			spriteGroupGhost.spriteArray[i].speedY 		= 0.0;
			spriteGroupGhost.spriteArray[i].startY 		= spriteGroupGhost.spriteArray[0].y1;
			spriteGroupGhost.spriteArray[i].startX 		= 1920.0;
			spriteGroupGhost.spriteArray[i].endY   		= spriteGroupGhost.spriteArray[0].y1;
			spriteGroupGhost.spriteArray[i].endX 	    = 0.0;
			spriteGroupGhost.spriteArray[i].id 	    	= 1;
			spriteGroupGhost.spriteArray[i].randVar    	= r;
			spriteGroupGhost.spriteArray[i].randVar2    = r2;
			spriteGroupGhost.spriteArray[i].loop 	    = YES;
		}
	}

	// configura arvores profundidade 1
	for (i = 0; i < spriteGroupTrees.arraySize - 1; i++){	
		if (spriteGroupTrees.spriteArray[i].canvas != NULL){
			float r = (rand() / 100000000.0);
			//printf("\nrand:%f", r);
			spriteGroupTrees.spriteArray[i].x1 			= (spriteGroupTrees.spriteArray[i].width * i) * r;
			spriteGroupTrees.spriteArray[i].y1 			= nativeScreen.scaledH - spriteGroupTrees.spriteArray[i].height - 10;
			//printf("\ny1:%f", spriteGroupTrees.spriteArray[i].y1);
			spriteGroupTrees.spriteArray[i].depth 		= 1.0;
			spriteGroupTrees.spriteArray[i].directionX 	= -1;
			spriteGroupTrees.spriteArray[i].directionY 	= 1;
			spriteGroupTrees.spriteArray[i].speedX 		= 1.0;
			spriteGroupTrees.spriteArray[i].speedY 		= 0.0;
			spriteGroupTrees.spriteArray[i].startY 		= spriteGroupTrees.spriteArray[i].y1;
			spriteGroupTrees.spriteArray[i].startX 		= nativeScreen.scaledW + spriteGroupTrees.spriteArray[i].x1;
			spriteGroupTrees.spriteArray[i].endY   		= spriteGroupTrees.spriteArray[i].y1;
			spriteGroupTrees.spriteArray[i].endX 	   	= 0.0;
			spriteGroupTrees.spriteArray[i].id 	    	= i;
			spriteGroupTrees.spriteArray[i].loop 	   	= YES;
		}
	}

	// configura arvores profundidade 2
	for (i = 0; i < spriteGroupTrees2.arraySize - 1; i++){	
		if (spriteGroupTrees2.spriteArray[i].canvas != NULL){
			float r = (rand() / 100000000.0);
			printf("\nrand:%f", r);

			spriteGroupTrees2.spriteArray[i].x1 			= 300 + (spriteGroupTrees2.spriteArray[i].width * i) * r;
			spriteGroupTrees2.spriteArray[i].y1 			= 1080 - spriteGroupTrees2.spriteArray[i].height - 10;
			printf("\ny1:%f", spriteGroupTrees2.spriteArray[i].y1);
			spriteGroupTrees2.spriteArray[i].depth 			= 0.7;
			spriteGroupTrees2.spriteArray[i].directionX 	= -1;
			spriteGroupTrees2.spriteArray[i].directionY 	= 1;
			spriteGroupTrees2.spriteArray[i].speedX 		= 1.0;
			spriteGroupTrees2.spriteArray[i].speedY 		= 0.0;
			spriteGroupTrees2.spriteArray[i].startY 		= spriteGroupTrees2.spriteArray[i].y1;
			spriteGroupTrees2.spriteArray[i].startX 		= 1920 + spriteGroupTrees2.spriteArray[i].x1;
			spriteGroupTrees2.spriteArray[i].endY   		= spriteGroupTrees2.spriteArray[i].y1;
			spriteGroupTrees2.spriteArray[i].endX 	   		= 0.0;
			spriteGroupTrees2.spriteArray[i].id 	    	= i;
			spriteGroupTrees2.spriteArray[i].loop 	   		= YES;

		}
	}
	
	// configura o cemitério
	for (i = 0; i < spriteGroupTombs.arraySize - 1; i++){	
		if (spriteGroupTombs.spriteArray[i].canvas != NULL){
			float r = (rand() / 100000000.0);
			printf("\nrand:%f", r);
			spriteGroupTombs.spriteArray[i].x1 			= (spriteGroupTombs.spriteArray[i].width * i) * r + 20;
			spriteGroupTombs.spriteArray[i].y1 			= nativeScreen.height - spriteGroupTombs.spriteArray[i].height - 5;
			//printf("\ny1:%f", spriteGroupTrees.spriteArray[i].y1);
			spriteGroupTombs.spriteArray[i].depth 		= 1.3;
			spriteGroupTombs.spriteArray[i].directionX 	= -1;
			spriteGroupTombs.spriteArray[i].directionY 	= 1;
			spriteGroupTombs.spriteArray[i].speedX 		= 1.0;
			spriteGroupTombs.spriteArray[i].speedY 		= 0.0;
			spriteGroupTombs.spriteArray[i].startY 		= spriteGroupTombs.spriteArray[i].y1;
			spriteGroupTombs.spriteArray[i].startX 		= nativeScreen.width + spriteGroupTombs.spriteArray[i].x1;
			spriteGroupTombs.spriteArray[i].endY   		= spriteGroupTombs.spriteArray[i].y1;
			spriteGroupTombs.spriteArray[i].endX 	   	= 0.0;
			spriteGroupTombs.spriteArray[i].id 	    	= i;
			spriteGroupTombs.spriteArray[i].loop 	   	= YES;
		}
	}

/*
		spriteGroupTrees.spriteArray[1].x1 			= 1200;
		spriteGroupTrees.spriteArray[1].y1 			= 700;
		spriteGroupTrees.spriteArray[1].depth 		= 0.8;
		spriteGroupTrees.spriteArray[1].directionX 	= -1;
		spriteGroupTrees.spriteArray[1].directionY 	= 1;
		spriteGroupTrees.spriteArray[1].speedX 		= 1.0;
		spriteGroupTrees.spriteArray[1].speedY 		= 0.0;
		spriteGroupTrees.spriteArray[1].startY 		= spriteGroupTrees.spriteArray[1].y1;
		spriteGroupTrees.spriteArray[1].startX 		= 1920.0 + spriteGroupTrees.spriteArray[1].x1;
		spriteGroupTrees.spriteArray[1].endY   		= spriteGroupTrees.spriteArray[1].y1;
		spriteGroupTrees.spriteArray[1].endX 	   	= 0.0;
		spriteGroupTrees.spriteArray[1].id 	    	= 3;
		spriteGroupTrees.spriteArray[1].loop 	   	= YES;

*/
	/* Inicializa o jogo em tela cheia */
 	if (pi_setFullScreen(&nativeScreen, &gameDisplay) < 0)
		return -1;

	 /* Configura a escala das coordenadas e tamanho da imagem no display */
	pi_setDisplayScale(&nativeScreen, &gameDisplay);

	/* Configura as telas de Aventura e Poderes de acordo com a resolução original do jogo
	   configurada em nativeScreen */
	pi_setTelaAventura(&nativeScreen, &telaAventura, &gameDisplay);
	pi_setTelaPoderes(&nativeScreen, &telaPoderes, &gameDisplay);

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(gameTimer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//***** INICIO DO LOOPING PRINCIAPL
	al_start_timer(gameTimer);
	
	int frame = 0;
	ALLEGRO_BITMAP *ground = NULL;
	ground = al_load_bitmap("img/ground/png/ground.png");
	ALLEGRO_BITMAP *sky = NULL;
	sky = al_load_bitmap("img/sky/png/sky.png");
	ALLEGRO_BITMAP *moon = NULL;
	moon = al_load_bitmap("img/sky/png/moon.png");


	while(!exitGame){
		al_set_target_backbuffer(gameDisplay.backbuffer);
		al_set_clipping_rectangle(0, 0, gameDisplay.width, gameDisplay.height);
		frame++;
		//printf("\nFrame:%d", frame);
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		al_init_timeout(&timeout, 0.06);

		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

		if (event.type == ALLEGRO_EVENT_TIMER && get_event){
			//al_hold_bitmap_drawing(true);

			DEBUG_ON("\ndebug:main():event.type:timer ");
		//	pi_drawGraphics(NULL, 10, 10, REFRESH, &nativeScreen, &nativeScreen, &gameDisplay); // Limpa o backbuffer
		//	pi_drawGraphics(al_load_bitmap("img/guile.png"), 1300, 100, 0, &telaPoderes, &nativeScreen, &gameDisplay); // Desenha o bitmap na escala correta
		//	pi_drawGraphics(al_load_bitmap("img/fallout.jpg"), 0, 10, 0, &telaAventura, &nativeScreen, &gameDisplay); // Desenha o bitmap na escala correta
						
			pi_drawGraphics(moon, 400, 300, REFRESH, &telaAventura, &nativeScreen, &gameDisplay);
			pi_drawGraphics(sky, 0, 950, 0, &telaAventura, &nativeScreen, &gameDisplay);

			//pi_AnimateSprite(&spriteGroupSky, &nativeScreen);
			//pi_drawGraphics(spriteGroupSky.spriteArray[1].canvas, spriteGroupSky.spriteArray[1].x1, spriteGroupSky.spriteArray[1].y1, REFRESH, &telaAventura, &nativeScreen, &gameDisplay);
			//pi_drawGraphics(spriteGroupSky.spriteArray[0].canvas, spriteGroupSky.spriteArray[0].x1, spriteGroupSky.spriteArray[0].y1, 0, &telaAventura, &nativeScreen, &gameDisplay);

			pi_drawGraphics(ground, 0, 1065, 0, &telaAventura, &nativeScreen, &gameDisplay);
//			pi_AnimateSprite(&spriteGroupGround, &nativeScreen);
//			pi_drawGraphics(spriteGroupGround.spriteArray[0].canvas, spriteGroupGround.spriteArray[0].x1, spriteGroupGround.spriteArray[0].y1, 0, &telaAventura, &nativeScreen, &gameDisplay);

			pi_AnimateSprite(&spriteGroupTrees2, &nativeScreen);
			for (i = 0; i < spriteGroupTrees2.arraySize - 1; i++){	
				if (spriteGroupTrees2.spriteArray[i].canvas != NULL){
					pi_drawGraphics(spriteGroupTrees2.spriteArray[i].canvas, spriteGroupTrees2.spriteArray[i].x1, spriteGroupTrees2.spriteArray[i].y1, 0, &telaAventura, &nativeScreen, &gameDisplay);
				}
				else
					break;
			}
			pi_AnimateSprite(&spriteGroupFog, &nativeScreen);
			for (i = 0; i < spriteGroupFog.arraySize - 1; i++){	
				if (spriteGroupFog.spriteArray[i].canvas != NULL){
					pi_drawGraphics(spriteGroupFog.spriteArray[i].canvas, spriteGroupFog.spriteArray[i].x1, spriteGroupFog.spriteArray[i].y1, 0, &telaAventura, &nativeScreen, &gameDisplay);
				}
				else
					break;
			}
/*
			pi_AnimateSprite(&spriteGroupFog2, &nativeScreen);
			for (i = 0; i < spriteGroupFog2.arraySize - 1; i++){	
				if (spriteGroupFog2.spriteArray[i].canvas != NULL){
					pi_drawGraphics(spriteGroupFog2.spriteArray[i].canvas, spriteGroupFog2.spriteArray[i].x1, spriteGroupFog2.spriteArray[i].y1, 0, &telaAventura, &nativeScreen, &gameDisplay);
				}
				else
					break;
			}
*/
			pi_AnimateSprite(&spriteGroupTrees, &nativeScreen);
			for (i = 0; i < spriteGroupTrees.arraySize - 1; i++){	
				if (spriteGroupTrees.spriteArray[i].canvas != NULL){
					pi_drawGraphics(spriteGroupTrees.spriteArray[i].canvas, spriteGroupTrees.spriteArray[i].x1, spriteGroupTrees.spriteArray[i].y1, 0, &telaAventura, &nativeScreen, &gameDisplay);
				}
				else
					break;
			}

			pi_AnimateSprite(&spriteGroupGrass2, &nativeScreen);
			for (i = 0; i < spriteGroupGrass2.arraySize - 1; i++){	
				if (spriteGroupGrass2.spriteArray[i].canvas != NULL){
					pi_drawGraphics(spriteGroupGrass2.spriteArray[i].canvas, spriteGroupGrass2.spriteArray[i].x1, spriteGroupGrass2.spriteArray[i].y1, 0, &telaAventura, &nativeScreen, &gameDisplay);
				}
				else
					break;
			}

			pi_AnimateSprite(&spriteGroupTombs, &nativeScreen);
			for (i = 0; i < spriteGroupTombs.arraySize - 1; i++){	
				if (spriteGroupTombs.spriteArray[i].canvas != NULL){
					pi_drawGraphics(spriteGroupTombs.spriteArray[i].canvas, spriteGroupTombs.spriteArray[i].x1, spriteGroupTombs.spriteArray[i].y1, 0, &telaAventura, &nativeScreen, &gameDisplay);
				}
				else
					break;
			}

			pi_AnimateSprite(&spriteGroupGhost, &nativeScreen);
			for (i = 0; i < spriteGroupGhost.arraySize - 1; i++){	
				if (spriteGroupGhost.spriteArray[i].canvas != NULL){
					pi_drawGraphics(spriteGroupGhost.spriteArray[i].canvas, spriteGroupGhost.spriteArray[i].x1, spriteGroupGhost.spriteArray[i].y1, 0, &telaAventura, &nativeScreen, &gameDisplay);
				}
				else
					break;
			}

			pi_AnimateSprite(&spriteGroupGrass, &nativeScreen);
			for (i = 0; i < spriteGroupGrass.arraySize - 1; i++){	
				if (spriteGroupGrass.spriteArray[i].canvas != NULL){
					pi_drawGraphics(spriteGroupGrass.spriteArray[i].canvas, spriteGroupGrass.spriteArray[i].x1, spriteGroupGrass.spriteArray[i].y1, 0, &telaAventura, &nativeScreen, &gameDisplay);
				}
				else
					break;
			}
			
			//al_hold_bitmap_drawing(false);

			redraw = true;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN && get_event){
				break;
		}

		if (redraw){
			redraw = false;

			al_flip_display();
		}
	}

	//**** Fim do programa. Destrói os componentes criados para evitar vazamento de memória.
	al_destroy_timer(gameTimer);
	al_destroy_display(gameDisplay.backbuffer);
	al_destroy_bitmap(nativeScreen.canvas);
	al_destroy_bitmap(telaPoderes.canvas);
	al_destroy_bitmap(telaAventura.canvas);
	//al_destroy_bitmap(currentImage);

	printf("\n================================");
	printf("\ndebug:main():end");
	printf("\n================================\n");

}
//======================================================================
int pi_drawGraphics(ALLEGRO_BITMAP *image, float x, float y, int refresh, GameScreen *tela, GameScreen *nativeScreen, GameDisplay *display){
	DEBUG_ON("\n----debug:drawGraphics():start");
	DEBUG_ON("\ndebug:tela:%d", tela->id);
/*
	if (!image && tela->id != NATIVE_SCREEN){
		al_show_native_message_box(display->backbuffer, "Erro", "Erro", "Falha ao carregar a imagem!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
*/
//	al_set_target_bitmap(tela->canvas);
	//al_set_target_backbuffer(display->backbuffer);

	if (refresh){
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	if (tela->id == NATIVE_SCREEN) // Caso image=null e tela==0, sai da função após ter limpado o buffer
			return 0;

	//al_draw_bitmap(image, x, y, 0);

	/*float x1 = tela->x1 * 1.0;
	float x2 = tela->x2 * 1.0;
	float y1 = tela->y1 * 1.0;
	float y2 = tela->y2 * 1.0;*/

	//al_set_target_bitmap(nativeScreen->canvas);
	//al_draw_bitmap(tela->canvas, 0, 0, 0);

//	al_set_target_backbuffer(display->backbuffer);
	//al_clear_to_color(al_map_rgb(0, 0, 0));

	//al_draw_bitmap(nativeScreen->canvas, 0, 0, 0);
	//if (tela->id == TELA_AVENTURA) al_set_clipping_rectangle(0, 0, (display->width/3)*2, display->height);
	al_draw_bitmap(image, x, y, 0);
	//al_draw_bitmap_region(image, 0, 0, tela->width, tela->height, x, y, 0);

	DEBUG_ON("\n----debug:drawGraphics():end");

	return 0;
}
//----------------------------------------------------------------------
