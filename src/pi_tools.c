/*
 * Código baseado no tutorial disponível em:
 * 		  https://wiki.allegro.cc/index.php?title=Achieving_Resolution_Independence
 */
#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <stdio.h>


#include "pi_data.h"

/* Para ativar/desativar o debug, descomentar/comentar a linha abaixo */
//#define _SET_DEBUG_ON
#define _SET_DEBUG_FILE

#ifdef 	_SET_DEBUG_ON
	#define DEBUG_ON printf
#endif
#ifndef _SET_DEBUG_ON
	#define DEBUG_ON //
#endif

#ifdef 	_SET_DEBUG_FILE
	#define DEBUG_FILE printf
#endif
#ifndef _SET_DEBUG_FILE
	#define DEBUG_FILE //
#endif

//======================================================================
int pi_iniSpriteGroup(SpriteGroup *sg, GameScreen *display, int id){
	DEBUG_ON("\n----debug:iniGroupSprites():start");
	int i;
	float spdY, spdX, offsetX, offsetY, dirX, dirY;
	
	sg->id = id;

	if (id == ID_GROUP_SPRITES_SKY){
		sg->depth		= 1;
		sg->x1			= 0.0;
		sg->y1			= 1020.0;
		sg->arraySize	= 20;
		
		sg->dirPath		= "img/sky/png/";
		sg->buffer		= al_create_bitmap(display->width, display->height);
		
		sg->directionX	= 1;
		sg->directionY	= 1;
		sg->speedX		= 0.0;
		sg->speedY		= 0.0;
	}	
	
	for (i = 0; i < sg->arraySize - 1; i++){
		sg->spriteArray[i].canvas = NULL;
		sg->spriteArray[i].id 		= 0;
		sg->spriteArray[i].x1 		= 0.0;
		sg->spriteArray[i].y1 		= 0.0;
		sg->spriteArray[i].speedX 	= 1.0;
		sg->spriteArray[i].speedY 	= 1.0;
		sg->spriteArray[i].depth 	= 1;
		sg->spriteArray[i].width	= 1;
		sg->spriteArray[i].height	= 1;
		sg->spriteArray[i].reload	= 1;
		sg->spriteArray[i].rest 	= 0;
		sg->spriteArray[i].directionX	= 1;
		sg->spriteArray[i].directionY 	= 1;
		sg->spriteArray[i].incrementX1 	= 0;
		sg->spriteArray[i].incrementY1 	= 0;
		sg->spriteArray[i].rest_countdown = sg->spriteArray[i].rest;		
	}
	
	return 0;
}
//----------------------------------------------------------------------
int pi_loadStillSprite(SpriteGroup *sg, char *fileName, char *tagName){
	
	int i;
	char fullPath[MAX_FILE_PATH_SIZE];

	for (i = 0; i < sg->arraySize - 1; i++){
		
		if (sg->spriteArray[i].reload == 1){
			sprintf(fullPath, "%s%s.png", sg->dirPath, fileName);
			DEBUG_FILE("\ndebug:loadStillSprite:fullFilePath:%s\n", fullPath);
			const char *file = fullPath;

			sg->spriteArray[i].canvas = al_load_bitmap(file);
			sg->spriteArray[i].reload = 0;
			return 0;
		}
	}
		
	return 0;
}
//----------------------------------------------------------------------
int pi_AnimateSpriteGroup(SpriteGroup *sg){
	int i;
	
	al_set_target_bitmap(sg->buffer);
	
	for (i = 0; i < sg->arraySize - 1; i++){
		sg->spriteArray[i].x1 += sg->spriteArray[i].incrementX1;
		sg->spriteArray[i].y1 += sg->spriteArray[i].incrementY1;
		
		al_draw_bitmap(sg->spriteArray[i].canvas, sg->spriteArray[i].x1, sg->spriteArray[i].x1);
	}
}
//----------------------------------------------------------------------
int pi_iniBackground(BGImageStream *bg, GameScreen *display, int layer){
	DEBUG_ON("\n----debug:iniBackground():start");
	int i;
	float spdY, spdX, offsetX, offsetY, dirX, dirY;
	//char fullPath[MAX_FILE_PATH_SIZE];

	bg->layer = layer;

	if (layer == LAYER_SCENE_GRASS){
		bg->tileCount 	= 7;
		bg->id 			= layer;
		bg->width 		= 502;
		bg->height 		= 105;
		bg->depth		= 1;
		bg->x1			= 0.0;
		bg->y1			= 1020.0;
		bg->currentIndex = 0;
		bg->totalNumImgs = 7;
		bg->rest			= bg->depth;
		bg->rest_countdown	= bg->rest;
		
		bg->fileNamePrefix	= "grass_";
		bg->dirPath			= "img/ground/png/";
		bg->buffer			= al_create_bitmap(display->width, display->height);
		
		dirX = -1;
		dirY = 1;
		spdX = 2.0;
		spdY = 0.0;
		offsetX = bg->width;
		offsetY = 0.0;
	}
	else if (layer == LAYER_SCENE_GRASS_2){
		bg->tileCount 	= 7;
		bg->id 			= layer;
		bg->width 		= 502;
		bg->height 		= 105;
		bg->depth		= 0.98;
		bg->x1			= 50.0;
		bg->y1			= 1010.0;
		bg->currentIndex = 0;
		bg->totalNumImgs = 7;
		bg->rest			= bg->depth;
		bg->rest_countdown	= bg->rest;
		
		bg->fileNamePrefix	= "grass_";
		bg->dirPath			= "img/ground/png/";
		bg->buffer			= al_create_bitmap(display->width, display->height);
		
		dirX = -1;
		dirY = 1;
		spdX = 2.0;
		spdY = 0.0;
		offsetX = bg->width;
		offsetY = 0.0;
	}
	
	int count = bg->tileCount - 1;

	for (i = 0; i <= count; i++){
		//sprintf(fullPath, "%s%s%d.png", bg->dirPath, bg->fileNamePrefix, i);
		//DEBUG_ON("\ndebug:loadBackGround:fullFilePath:%s", fullPath);
		//const char *file = fullPath;
		bg->tileSequence[i].canvas 	= al_create_bitmap(bg->width, bg->height);
		bg->tileSequence[i].width 	= bg->width;
		bg->tileSequence[i].height 	= bg->height;
		bg->tileSequence[i].x1		= bg->x1 + (i * offsetX);
		bg->tileSequence[i].y1		= bg->y1 + (i * offsetY);
		bg->tileSequence[i].speedX 	= spdX;
		bg->tileSequence[i].speedY 	= spdY;
		bg->tileSequence[i].reload	= 1; 
		bg->tileSequence[i].depth	= bg->depth;
		bg->tileSequence[i].rest	= bg->tileSequence[i].depth;
		bg->tileSequence[i].directionX 	= dirX;
		bg->tileSequence[i].directionY 	= dirY;
		bg->tileSequence[i].rest_countdown = 0;
		
		al_set_target_bitmap(bg->tileSequence[i].canvas);
		al_set_clipping_rectangle(bg->tileSequence[i].x1, bg->tileSequence[i].y1, bg->tileSequence[i].width, bg->tileSequence[i].height);
	}
	
	DEBUG_ON("\n----debug:iniBackground():end");
	return 0;
}
//----------------------------------------------------------------------
int pi_loadBackground(BGImageStream *bg){
	DEBUG_ON("\n----debug:loadBackground():start");

	int count = bg->tileCount - 1;
	int index = bg->currentIndex;
	int i;
	char fullPath[MAX_FILE_PATH_SIZE];
	
	for (i = 0; i <= count; i++){
		if (bg->tileSequence[i].reload){
			if (index > bg->totalNumImgs)
				index = 0;	
		
			
			sprintf(fullPath, "%s%s%d.png", bg->dirPath, bg->fileNamePrefix, index);
			DEBUG_ON("\ndebug:loadBackGround:fullFilePath:%s", fullPath);
			const char *file = fullPath;
			
			//al_rest(0.5);
			bg->tileSequence[i].canvas = al_load_bitmap(file);
			bg->tileSequence[i].reload = 0;
			
			index++;
		}
	}

	bg->currentIndex = index;
	
	DEBUG_ON("\n----debug:loadBackground():end");
	return 0;
}
//----------------------------------------------------------------------
int pi_animateBackground(BGImageStream *bg){
	//DEBUG_ON("\n----debug:animateBackground():start");
	
	int i;
	int count = bg->tileCount - 1;
	al_set_target_bitmap(bg->buffer);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	
	//if (bg->rest_countdown <= 0){
		
		//bg->rest_countdown = bg->rest;

		for (i = 0; i <= count; i++){			
			bg->tileSequence[i].x1 += (bg->tileSequence[i].speedX * bg->tileSequence[i].directionX * bg->tileSequence[i].depth) / 0.5;
			bg->tileSequence[i].y1 += (bg->tileSequence[i].speedY * bg->tileSequence[i].directionY);
		
			al_draw_bitmap(bg->tileSequence[i].canvas, bg->tileSequence[i].x1, bg->tileSequence[i].y1, 0);
			//DEBUG_ON("\n----debug:animateBackground():tileSequence[%d].depth = %f", i, bg->tileSequence[i].depth);
			DEBUG_ON("\n----debug:animateBackground():tileSequence[%d].x1 = %f", i, bg->tileSequence[i].x1);
			//DEBUG_ON("\n----debug:animateBackground():tileSequence[%d].y1 = %f", i, bg->tileSequence[i].y1);

			if (bg->tileSequence[i].x1 + bg->tileSequence[i].width < bg->x1){

				//DEBUG_ON("\n----debug:animateBackground():reload");
				//bg->tileSequence[i].reload = 1;
				bg->tileSequence[i].x1 = (count * bg->width) + 1.0; 
			}
		}
	//}
	//else
		//bg->rest_countdown--;
	
	
	//DEBUG_ON("\n----debug:animateBackground():end");
	return 0;
}
//----------------------------------------------------------------------
int pi_iniScreens(GameScreen *nativeScreen, GameScreen *telaPoderes, GameScreen *telaAventura){
	/* Inicializa todas as telas principais de desenho do jogo */
	
	nativeScreen->canvas	= al_create_bitmap(1920, 1080);
	nativeScreen->x1		= 0;
	nativeScreen->x2		= 1920;
	nativeScreen->y1		= 0;
	nativeScreen->y2		= 1080;
	nativeScreen->width		= 1920;
	nativeScreen->height	= 1080;
	nativeScreen->scaledX	= 1.0;
	nativeScreen->scaledY	= 1.0;
	nativeScreen->scaledW	= 1920.0;
	nativeScreen->scaledH	= 1080.0;
	nativeScreen->id		= NATIVE_SCREEN;
	
	telaAventura->id = TELA_AVENTURA;

	telaPoderes->id	 = TELA_PODERES;
}
//----------------------------------------------------------------------
int pi_iniAllegroAddons(GameDisplay *display){
	DEBUG_ON("\n----debug:iniAllegroAddons():start");
	
	/* ATENÇÃO! Todos os addons e estrutura de dados devem ser incializados dentro desta função */
				
	if (!al_init()){
		al_show_native_message_box(display->backbuffer, "Erro!", "Allegro 5.x", "Falha ao inicializar o Allegro 5!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	if (!al_init_image_addon()){
		al_show_native_message_box(display->backbuffer, "Erro!", "Image:", "Falha ao inicializar al_init_image_addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	if (!al_init_primitives_addon()){
		al_show_native_message_box(display->backbuffer, "Erro!", "Primitives:", "Falha ao inicializar allegro_primitives!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	if (!al_install_keyboard()){
		al_show_native_message_box(display->backbuffer, "Erro!", "Keyboard:", "Falha ao inicializar o teclado!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	DEBUG_ON("\n----debug:iniAllegroAddons():end");
	return 0;
}
//----------------------------------------------------------------------
int pi_setTelaAventura(GameScreen *nativeScreen, GameScreen *telaAventura, GameDisplay *display){
	/* Inicializa a tela do cenário do jogo calculando seu tamanho em relação a resolução original do jogo.
	   Ela compõe 2/3 do tamanho total do display. */

	DEBUG_ON("\n----debug:setTelaAventura():start");
	
	telaAventura->x1 = 0;
	telaAventura->x2 = (nativeScreen->width / 3) * 2;
	telaAventura->y1 = 0;
	telaAventura->y2 = nativeScreen->height;
	
	telaAventura->canvas = al_create_bitmap(telaAventura->x2, telaAventura->y2);
	if (!telaAventura->canvas){
		al_show_native_message_box(display->backbuffer, "Erro", "Erro", "Falha ao inicializar a Tela de Aventura!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	al_set_target_bitmap(telaAventura->canvas);
	al_clear_to_color(al_map_rgb(100, 50, 200));
	
	DEBUG_ON("\ndebug:telaAventura:x2:%f", telaAventura->x2);
	DEBUG_ON("\ndebug:telaAventura:y2:%f", telaAventura->y2);
	DEBUG_ON("\n----debug:setTelaAventura():end\n");
	
	return 0;
}
//----------------------------------------------------------------------
int pi_setTelaPoderes(GameScreen *nativeScreen, GameScreen *telaPoderes, GameDisplay *display){
	/* Inicializa a tela de poderes calculando seu tamanho em relação a resolução original do jogo.
	 * Ela compõe 1/3 do tamanho total do display. */

	DEBUG_ON("\n----debug:setTelaPoderes():start");
	
	telaPoderes->x1 	= ((nativeScreen->width / 3) * 2);
	telaPoderes->x2 	= nativeScreen->width;
	telaPoderes->width 	= nativeScreen->width - ((nativeScreen->width / 3) * 2);
	telaPoderes->y1 	= nativeScreen->y1;
	telaPoderes->y2 	= nativeScreen->y2;
	telaPoderes->height = nativeScreen->height;
	
	telaPoderes->canvas = al_create_bitmap(nativeScreen->width, nativeScreen->height);
	if (!telaPoderes->canvas){
		al_show_native_message_box(display->backbuffer, "Erro", "Erro", "Falha ao inicializar a Tela de Poderes!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	al_set_target_bitmap(telaPoderes->canvas);
	al_clear_to_color(al_map_rgb(0, 0, 0)); // limpa a tela

	al_set_clipping_rectangle(telaPoderes->x1, telaPoderes->y1, telaPoderes->width, telaPoderes->height);
	al_clear_to_color(al_map_rgb(200, 50, 100));
	
	
	
	DEBUG_ON("\ndebug:telaPoderes:x1:%f", telaPoderes->x1);
	DEBUG_ON("\ndebug:telaPoderes:y1:%f", telaPoderes->y1);
	DEBUG_ON("\n----debug:setTelaPoderes():end\n");
	
	return 0;
}
//----------------------------------------------------------------------
void pi_setDisplayScale(GameScreen *nativeScreen, GameDisplay *gameDisplay){
	/* Calcula o valor da escala do monitor de acordo
	   com a resolução inicial em que o jogo foi criado e a do monitor em uso */
	
	DEBUG_ON("\n----debug:setDisplayScale():start");
	// Calcula a proporção da escala
	float scaledX, scaledY;
	
	scaledX = (float)(gameDisplay->width)  / nativeScreen->width;
	scaledY = (float)(gameDisplay->height) / nativeScreen->height;
	
	/* Acha qual é o menor entre sx e sy e calcula a escala.
	   O cálculo é feito pelo menor valor para evitar que a imagem não ultrapasse os limites do monitor.*/
	if (scaledX < scaledY){
		gameDisplay->scale = scaledX;
	}
	else{
		gameDisplay->scale = scaledX;
	}
		
	/* Calcula as escalas a serem utilizadas */
	nativeScreen->scaledW = nativeScreen->width  * gameDisplay->scale;
	nativeScreen->scaledH = nativeScreen->height * gameDisplay->scale;
	
	/* Configura as novas escalas para X e Y */
	
	ALLEGRO_TRANSFORM trans;
	al_identity_transform(&trans);
	al_scale_transform(&trans, scaledX, scaledY);
	al_use_transform(&trans);
	
	DEBUG_ON("\ndebug:gameDisplay:scale:%f", 	 gameDisplay->scale);
	DEBUG_ON("\ndebug:nativeScreen:scaledW:%f",  nativeScreen->scaledW);
	DEBUG_ON("\ndebug:nativeScreen:scaledH:%f",  nativeScreen->scaledH);
	DEBUG_ON("\ndebug:gameDisplay:width:%d", 	 gameDisplay->width);
	DEBUG_ON("\ndebug:gameDisplay:height:%d", 	 gameDisplay->height);
	DEBUG_ON("\ndebug:nativeScreen:width:%d", 	 nativeScreen->width);
	DEBUG_ON("\ndebug:nativeScreen:height:%d\n", nativeScreen->height);
	
	DEBUG_ON("\n----debug:setDisplayScale():end\n");
	return;	
}
//----------------------------------------------------------------------
int pi_setFullScreen(GameScreen *nativeScreen, GameDisplay *display){
	
	DEBUG_ON("\n----debug:setFullScreen():start");
	// Configura para tela cheia.
	
	al_set_new_bitmap_flags(ALLEGRO_MAG_LINEAR);
	ALLEGRO_DISPLAY_MODE disp_data;
	
	al_get_display_mode(display->mode, &disp_data); // Armazena em disp_data a maior resolução suportada pelo monitor

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	
	display->width 	= disp_data.width;
	display->height = disp_data.height;

	display->backbuffer = al_create_display(display->width, display->height); // Cria o display em tela cheia.
	// Cria o buffer de desenho da tela. Todas as outras imagens são criadas dentro dele, assim basta mudar a escala dele.
	// e todo o resto é ajustado automaticamente.
	nativeScreen->canvas = al_create_bitmap(nativeScreen->width, nativeScreen->height);
	
	if (!display->backbuffer){
		al_show_native_message_box(display->backbuffer, "Erro", "Erro", "Falha ao inicializar o display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display->backbuffer);
		return -1;
	}

	if (!nativeScreen->canvas){
		al_show_native_message_box(display->backbuffer, "Erro", "Erro", "Falha ao inicializar o displayBuffer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	DEBUG_ON("\n----debug:setFullScreen():end\n");
	return 0;
}
//----------------------------------------------------------------------
