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
	DEBUG_ON("\n================================");
	DEBUG_ON("\ndebug:main():start");
	DEBUG_ON("\n================================");

	GameScreen nativeScreen; // tela original do jogo.
	GameScreen telaAventura;
	GameScreen telaPoderes;
	GameDisplay gameDisplay = {.mode = 0}; // display onde aparecem as telas de Aventura e Poderes		
	BGImageStream sceneGrass;
	BGImageStream sceneGrass2;
	BGImageStream treeLine1;
	SpriteGroup spriteGroupSky;
	
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
	pi_iniBackground(&sceneGrass, &nativeScreen, LAYER_SCENE_GRASS);
	pi_loadBackground(&sceneGrass);

	pi_iniBackground(&sceneGrass2, &nativeScreen, LAYER_SCENE_GRASS_2);
	pi_loadBackground(&sceneGrass2);

	pi_iniBackground(&treeLine1, &nativeScreen, LAYER_SCENE_TREELINE_1);
	pi_loadBackground(&treeLine1);
	
	/* Configura SPRITES*/
	pi_iniSpriteGroup(&spriteGroupSky, &nativeScreen, ID_GROUP_SPRITES_SKY);
	pi_loadStillSprite(&spriteGroupSky, 0, 0, 0, 0, "moon", "moon");
	
	int spriteNum = pi_findSpriteByName(&spriteGroupSky, "moon");
	if (spriteNum > -1){
		spriteGroupSky.spriteArray[spriteNum].x1 			= 400;
		spriteGroupSky.spriteArray[spriteNum].y1 			= 210;
		spriteGroupSky.spriteArray[spriteNum].depth 		= 0.1;
		spriteGroupSky.spriteArray[spriteNum].directionX 	= -1;
		spriteGroupSky.spriteArray[spriteNum].directionY 	= -1;
		spriteGroupSky.spriteArray[spriteNum].speedX 		= 0.4;
		spriteGroupSky.spriteArray[spriteNum].speedY 		= 0.4;
	}
	
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
	
	while(!exitGame){
		
		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		al_init_timeout(&timeout, 0.06);
		
		bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);
				
		if (event.type == ALLEGRO_EVENT_TIMER && get_event){
			
			DEBUG_ON("\ndebug:main():event.type:timer ");
			pi_drawGraphics(NULL, 10, 10, REFRESH, &nativeScreen, &nativeScreen, &gameDisplay); // Limpa o backbuffer
			pi_drawGraphics(al_load_bitmap("img/guile.png"), 1300, 100, 0, &telaPoderes, &nativeScreen, &gameDisplay); // Desenha o bitmap na escala correta
		//	pi_drawGraphics(al_load_bitmap("img/fallout.jpg"), 0, 10, 0, &telaAventura, &nativeScreen, &gameDisplay); // Desenha o bitmap na escala correta
	
			pi_AnimateSpriteGroup(&spriteGroupSky, &nativeScreen);
			pi_drawGraphics(spriteGroupSky.buffer, 0, 0, REFRESH, &telaAventura, &nativeScreen, &gameDisplay);
			
			pi_loadBackground(&treeLine1);
			pi_animateBackground(&treeLine1);
			pi_drawGraphics(treeLine1.buffer, 0, 0, 0, &telaAventura, &nativeScreen, &gameDisplay);

			pi_loadBackground(&sceneGrass2);
			pi_animateBackground(&sceneGrass2);
			pi_drawGraphics(sceneGrass2.buffer, 0, 0, 0, &telaAventura, &nativeScreen, &gameDisplay);

			pi_loadBackground(&sceneGrass);
			pi_animateBackground(&sceneGrass);
			pi_drawGraphics(sceneGrass.buffer, 0, 0, 0, &telaAventura, &nativeScreen, &gameDisplay);
			
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

	DEBUG_ON("\n================================");
	DEBUG_ON("\ndebug:main():end");
	DEBUG_ON("\n================================\n");

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
