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
int pi_drawGraphics(ALLEGRO_BITMAP *image, int x, int y, int refresh, GameScreen *tela, GameScreen *nativeScreen, GameDisplay *display);

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
    SpriteGroup spriteGroupGrass;
    StillSprite spriteArrayGrass[20];

    int spriteNum = -1;

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
	pi_iniSpriteGroup(&spriteGroupGrass, &nativeScreen, ID_GROUP_SPRITES_GRASS);
	pi_loadStillSprite(&spriteGroupGrass, "grass_0", "grass_0");
	pi_loadStillSprite(&spriteGroupGrass, "grass_1", "grass_1");
	pi_loadStillSprite(&spriteGroupGrass, "grass_2", "grass_2");
	pi_loadStillSprite(&spriteGroupGrass, "grass_3", "grass_3");
	pi_loadStillSprite(&spriteGroupGrass, "grass_4", "grass_4");
	pi_loadStillSprite(&spriteGroupGrass, "grass_5", "grass_5");
	pi_loadStillSprite(&spriteGroupGrass, "grass_6", "grass_6");
	pi_loadStillSprite(&spriteGroupGrass, "grass_0", "grass_0");
	pi_loadStillSprite(&spriteGroupGrass, "grass_1", "grass_1");
	pi_loadStillSprite(&spriteGroupGrass, "grass_2", "grass_2");
	pi_loadStillSprite(&spriteGroupGrass, "grass_3", "grass_3");
	pi_loadStillSprite(&spriteGroupGrass, "grass_4", "grass_4");

	pi_iniSpriteGroup(&spriteGroupSky, &nativeScreen, ID_GROUP_SPRITES_SKY);
	pi_loadStillSprite(&spriteGroupSky, "moon", "moon");

    pi_iniSpriteGroup(&spriteGroupTrees, &nativeScreen, ID_GROUP_SPRITES_TREES);
    pi_loadStillSprite(&spriteGroupTrees, "tree1", "tree1");
    pi_loadStillSprite(&spriteGroupTrees, "tree2", "tree2");

//	spriteNum = pi_findSpriteByName(&spriteGroupSky, "moon");
	int i;
	
	// Configura a grama
	for (i = 0; i < spriteGroupGrass.arraySize - 1; i++){	
		if (spriteGroupGrass.spriteArray[i].canvas != NULL){
			spriteGroupGrass.spriteArray[i].x1 			= 0 + (i * spriteGroupGrass.spriteArray[i].width);
			printf("\nx1:%f", spriteGroupGrass.spriteArray[i].x1);
			spriteGroupGrass.spriteArray[i].y1 			= 1020;
			spriteGroupGrass.spriteArray[i].depth 		= 2.0;
			spriteGroupGrass.spriteArray[i].directionX 	= -1;
			spriteGroupGrass.spriteArray[i].directionY 	= 1;
			spriteGroupGrass.spriteArray[i].speedX 		= 1.0;
			spriteGroupGrass.spriteArray[i].speedY 		= 0.0;
			spriteGroupGrass.spriteArray[i].startY 		= spriteGroupGrass.spriteArray[i].y1;
			spriteGroupGrass.spriteArray[i].startX 		= nativeScreen.width + spriteGroupGrass.spriteArray[i].x1;
			spriteGroupGrass.spriteArray[i].endY   		= spriteGroupGrass.spriteArray[i].y1;
			spriteGroupGrass.spriteArray[i].endX 	    = 0.0;
			printf("\nstartX:%f", spriteGroupGrass.spriteArray[i].startX);
			spriteGroupGrass.spriteArray[i].id 	    	= 4;
			spriteGroupGrass.spriteArray[i].loop 	    = YES;
		}	
	}

//	if (spriteNum > -1){
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
//	}

//    spriteNum = pi_findSpriteByName(&spriteGroupTrees, "tree1");
//    if (spriteNum > -1){
        spriteGroupTrees.spriteArray[0].x1 			= 400;
        spriteGroupTrees.spriteArray[0].y1 			= 750;
        spriteGroupTrees.spriteArray[0].depth 		= 0.90;
        spriteGroupTrees.spriteArray[0].directionX 	= -1;
        spriteGroupTrees.spriteArray[0].directionY 	= 1;
        spriteGroupTrees.spriteArray[0].speedX 		= 1.0;
        spriteGroupTrees.spriteArray[0].speedY 		= 0.0;
        spriteGroupTrees.spriteArray[0].startY 		= spriteGroupTrees.spriteArray[0].y1;
        spriteGroupTrees.spriteArray[0].startX 		= 1920.0 + spriteGroupTrees.spriteArray[0].x1;
        spriteGroupTrees.spriteArray[0].endY   		= spriteGroupTrees.spriteArray[0].y1;
        spriteGroupTrees.spriteArray[0].endX 	   	= 0.0;
        spriteGroupTrees.spriteArray[0].id 	    	= 2;
        spriteGroupTrees.spriteArray[0].loop 	   	= YES;
//    }

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

	while(!exitGame){
		frame++;
		printf("\nFrame:%d", frame);
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		al_init_timeout(&timeout, 0.06);

		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

		if (event.type == ALLEGRO_EVENT_TIMER && get_event){

			DEBUG_ON("\ndebug:main():event.type:timer ");
			pi_drawGraphics(NULL, 10, 10, REFRESH, &nativeScreen, &nativeScreen, &gameDisplay); // Limpa o backbuffer
			pi_drawGraphics(al_load_bitmap("img/guile.png"), 1300, 100, 0, &telaPoderes, &nativeScreen, &gameDisplay); // Desenha o bitmap na escala correta
		//	pi_drawGraphics(al_load_bitmap("img/fallout.jpg"), 0, 10, 0, &telaAventura, &nativeScreen, &gameDisplay); // Desenha o bitmap na escala correta
						
		//	pi_AnimateSprite(&spriteGroupSky, &nativeScreen);
		//	pi_drawGraphics(spriteGroupSky.buffer, 0, 0, REFRESH, &telaAventura, &nativeScreen, &gameDisplay);

		//	pi_AnimateSprite(&spriteGroupTrees, &nativeScreen);
        //   pi_drawGraphics(spriteGroupTrees.buffer, 0, 0, 0, &telaAventura, &nativeScreen, &gameDisplay);

		//	pi_AnimateSprite(&spriteGroupGrass, &nativeScreen);
        //   pi_drawGraphics(spriteGroupGrass.buffer, 0, 0, 0, &telaAventura, &nativeScreen, &gameDisplay);

			//pi_loadBackground(&treeLine1);
			//pi_animateBackground(&treeLine1);
			//pi_drawGraphics(treeLine1.buffer, 0, 0, 0, &telaAventura, &nativeScreen, &gameDisplay);
/*
			pi_loadBackground(&sceneGrass2);
			pi_animateBackground(&sceneGrass2);
			pi_drawGraphics(sceneGrass2.buffer, 0, 0, 0, &telaAventura, &nativeScreen, &gameDisplay);

			pi_loadBackground(&sceneGrass);
			pi_animateBackground(&sceneGrass);
			pi_drawGraphics(sceneGrass.buffer, 0, 0, 0, &telaAventura, &nativeScreen, &gameDisplay);
*/		
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
int pi_drawGraphics(ALLEGRO_BITMAP *image, int x, int y, int refresh, GameScreen *tela, GameScreen *nativeScreen, GameDisplay *display){
	DEBUG_ON("\n----debug:drawGraphics():start");
	DEBUG_ON("\ndebug:tela:%d", tela->id);

	if (!image && tela->id != NATIVE_SCREEN){
		al_show_native_message_box(display->backbuffer, "Erro", "Erro", "Falha ao carregar a imagem!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_set_target_bitmap(tela->canvas);

	if (refresh){
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	if (tela->id == NATIVE_SCREEN) // Caso image=null e tela==0, sai da função após ter limpado o buffer
			return 0;

	al_draw_bitmap(image, x, y, 0);

	float x1 = tela->x1 * 1.0;
	float x2 = tela->x2 * 1.0;
	float y1 = tela->y1 * 1.0;
	float y2 = tela->y2 * 1.0;

	al_set_target_bitmap(nativeScreen->canvas);
	al_draw_bitmap(tela->canvas, 0, 0, 0);

	al_set_target_backbuffer(display->backbuffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_bitmap(nativeScreen->canvas, 0, 0, 0);

	DEBUG_ON("\n----debug:drawGraphics():end");

	return 0;
}
//----------------------------------------------------------------------
