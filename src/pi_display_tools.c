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
//======================================================================

ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *displayBuffer;

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
