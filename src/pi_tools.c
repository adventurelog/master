/*
 * Código baseado no tutorial disponível em:
 * 		  https://wiki.allegro.cc/index.php?title=Achieving_Resolution_Independence
 */
#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <stdio.h>

/* Para ativar/desativar o debug, descomentar/comentar a linha abaixo */
#define _SET_DEBUG_ON
#ifdef 	_SET_DEBUG_ON
	#define DEBUG_ON printf
#endif
#ifndef _SET_DEBUG_ON
	#define DEBUG_ON //
#endif

ALLEGRO_DISPLAY	*display;
ALLEGRO_BITMAP	*displayBuffer;
ALLEGRO_BITMAP	*telaAventura;
ALLEGRO_BITMAP	*telaPoderes;
//======================================================================
int pi_initAllegroAddons(void){
	
	/* ATENÇÃO! Todos os addons devem ser incializados dentro desta função */
	
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	
	if (!al_init()){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao inicializar o Allegro 5!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	if (!al_init_image_addon()){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao inicializar al_init_image_addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	if (!al_init_primitives_addon()){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao inicializar allegro_primitives!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	return 0;
}
//----------------------------------------------------------------------
int pi_setTelaAventura(int *gameScreenWidth, int *gameScreenHeight, int *telaA_x1, int *telaA_x2, int *telaA_y1, int *telaA_y2){
	/* Inicializa a tela do cenário do jogo calculando seu tamanho em relação a resolução do monitor.
	 * Ela compõe 2/3 do tamanho total do display e salva suas dimensões nas variáveis telaA_x1,
	 * telaA_x2, telaA_y1, telaA_y2.
	 */

	DEBUG_ON("\n----------------------");
	DEBUG_ON("\ndebug:setTelaAventura():start");
	DEBUG_ON("\n----------------------");
	
	*telaA_x1 = 0;
	*telaA_x2 = (*gameScreenWidth / 3) * 2;
	*telaA_y1 = 0;
	*telaA_y2 = *gameScreenHeight;
	
	telaAventura = al_create_bitmap(*telaA_x2, *telaA_y2);
	if (!telaAventura){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao inicializar a Tela de Aventura!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	al_set_target_bitmap(telaAventura);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	DEBUG_ON("\ndebug:telaA_x2:%d", *telaA_x2);
	DEBUG_ON("\ndebug:telaA_y2:%d", *telaA_y2);
	DEBUG_ON("\ndebug:setTelaAventura():end\n");
	
	return 0;
}
//----------------------------------------------------------------------
int pi_setTelaPoderes(int *gameScreenWidth, int *gameScreenHeight, int *telaP_x1, int *telaP_x2, int *telaP_y1, int *telaP_y2){
	/* Inicializa a tela de poderes calculando seu tamanho em relação a resolução do monitor.
	 * Ela compõe 2/3 do tamanho total do display e salva suas dimensões nas variáveis telaP_x1,
	 * telaP_x2, telaP_y1, telaP_y2.
	 */

	DEBUG_ON("\n----------------------");
	DEBUG_ON("\ndebug:setTelaPoderes():start");
	DEBUG_ON("\n----------------------");
	
	*telaP_x1 = ((*gameScreenWidth / 3) * 2);
	*telaP_x2 = *gameScreenWidth - ((*gameScreenWidth / 3) * 2);
	*telaP_y1 = 0;
	*telaP_y2 = *gameScreenHeight;
	
	telaPoderes = al_create_bitmap(*gameScreenWidth, *gameScreenHeight);
	if (!telaPoderes){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao inicializar a Tela de Poderes!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	al_set_target_bitmap(telaPoderes);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	DEBUG_ON("\ndebug:telaP_x2:%d", *telaP_x1);
	DEBUG_ON("\ndebug:telaP_y2:%d", *telaP_y2);
	DEBUG_ON("\ndebug:setTelaPoderes():end\n");
	
	return 0;
}
//----------------------------------------------------------------------
void setDisplayScale(int *startW, int *startH, int *targetW, int *targetH,
					float *displayScale, float *scaleW, float *scaleH, float *scaleX, float *scaleY){
	/* Calcula o valor da escala do monitor de acordo
	   com a resolução inicial e a final e salva nas variáveis
	   displayScale, scaleW, scaleH, scaleX e scaleY */
	
	DEBUG_ON("\n----------------------");
	DEBUG_ON("\ndebug:setDisplayScale():start");
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
	
	DEBUG_ON("\ndebug:setDisplayScale():end\n");
	return;	
}
//----------------------------------------------------------------------
int pi_setFullScreen(int *displayMode, int *displayWidth, int *displayHeight, int *gameScreenWidth,
						int *gameScreenHeight){
	
	DEBUG_ON("\n----------------------");
	DEBUG_ON("\ndebug:setFullScreen():start");
	DEBUG_ON("\n----------------------");
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
	
	DEBUG_ON("\ndebug:setFullScreen():end\n");
	return 0;
}
//----------------------------------------------------------------------
