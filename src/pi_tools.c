/*
 * Código baseado no tutorial disponível em:
 * 		  https://wiki.allegro.cc/index.php?title=Achieving_Resolution_Independence
 */
#include "allegro5/allegro.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <stdio.h>

/* Para ativar o debug, descomentar a linha abaixo */
#define _SET_DEBUG_ON
#ifdef _SET_DEBUG_ON
	#define DEBUG_ON printf
#endif
#ifndef _SET_DEBUG_ON
	#define DEBUG_ON //
#endif

ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *displayBuffer;
//======================================================================
void setDisplayScale(int *startW, int *startH, int *targetW, int *targetH,
					float *displayScale, float *scaleW, float *scaleH, float *scaleX, float *scaleY){
	/* Calcula o valor da escala do monitor de acordo
	   com a resolução inicial e a final e salva nas variáveis
	   displayScale, scaleW, scaleH, scaleX e scaleY */
	
	DEBUG_ON("\ndebug:setDisplayScale\n");
	// Calcula a proporção da escala
	*scaleX = (float)(*targetW) / *startW;
	*scaleY = (float)(*targetH) / *startH;
	
	/* Acha qual é o menor entre sx e sy e calcula a escala.
	   O cálculo é feito pelo menor valor para evitar que a imagem não ultrapasse os limites do monitor.*/
	if (*scaleX < *scaleY){
		*displayScale = *scaleX;
	}
	else{
		*displayScale = *scaleY;
	}
	
	/* Calcula as escalas a serem utilizadas */
	*scaleW = *startW * *displayScale;
	*scaleH = *startH * *displayScale;
	
	/* Configura as novas escalas para X e Y */
	
	ALLEGRO_TRANSFORM trans;
	al_identity_transform(&trans);
	al_scale_transform(&trans, *scaleX, *scaleY);
	al_use_transform(&trans);
	
	DEBUG_ON("\ndebug:scale:%f", *displayScale);
	DEBUG_ON("\ndebug:ScaleW:%f", *scaleW);
	DEBUG_ON("\ndebug:ScaleH:%f", *scaleH);
	DEBUG_ON("\ndebug:displayWidth:%d", *targetW);
	DEBUG_ON("\ndebug:displayHeight:%d", *targetH);
	DEBUG_ON("\ndebug:gameScreenWidth:%d", *startW);
	DEBUG_ON("\ndebug:gameScreenHeight:%d\n", *startH);
	
	return;	
}
//----------------------------------------------------------------------
int pi_setFullScreen(int *displayMode, int *displayWidth, int *displayHeight, int *gameScreenWidth,
						int *gameScreenHeight){
	
	DEBUG_ON("\ndebug:setFullScreen\n");
	// Configura para tela cheia.
	
	ALLEGRO_DISPLAY_MODE disp_data;
	
	al_get_display_mode(*displayMode, &disp_data); // Armazena em disp_data a maior resolução suportada pelo monitor

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	
	*displayWidth = disp_data.width;
	*displayHeight = disp_data.height;

	display = al_create_display(*displayWidth, *displayHeight); // Cria o display em tela cheia.
	// Cria o buffer de desenho da tela. Todas as outras imagens são criadas dentro dele, assim basta mudar a escala dele.
	// e todo o resto é ajustado automaticamente.
	displayBuffer = al_create_bitmap(*gameScreenWidth, *gameScreenHeight);
	
	if (!display){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao inicializar o display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	if (!displayBuffer){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao inicializar o displayBuffer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	return 0;
}
//----------------------------------------------------------------------
