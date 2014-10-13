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
#define _SET_DEBUG_ON
#ifdef 	_SET_DEBUG_ON
	#define DEBUG_ON printf
#endif
#ifndef _SET_DEBUG_ON
	#define DEBUG_ON //
#endif
/*
ALLEGRO_DISPLAY	*display;
ALLEGRO_BITMAP	*displayBuffer;
ALLEGRO_BITMAP	*telaAventura;
ALLEGRO_BITMAP	*telaPoderes;
*/
//======================================================================
int pi_iniScreens(GameScreen *nativeScreen, GameScreen *telaPoderes, GameScreen *telaAventura){
	/* Inicializa todas as telas principais de desenho do jogo */
	
	(*nativeScreen).canvas	= al_create_bitmap(1920, 1080);
	(*nativeScreen).x1		= 0;
	(*nativeScreen).x2		= 1920;
	(*nativeScreen).y1		= 0;
	(*nativeScreen).y2		= 1080;
	(*nativeScreen).width	= 1920;
	(*nativeScreen).height	= 1080;
	(*nativeScreen).scaledX	= 1.0;
	(*nativeScreen).scaledY	= 1.0;
	(*nativeScreen).scaledW	= 1920.0;
	(*nativeScreen).scaledH	= 1080.0;
	(*nativeScreen).id		= NATIVE_SCREEN;
	
	(*telaAventura).id = TELA_AVENTURA;

	(*telaPoderes).id = TELA_PODERES;	
}
//----------------------------------------------------------------------
int pi_iniAllegroAddons(GameDisplay *display){
	
	/* ATENÇÃO! Todos os addons e estrutura de dados devem ser incializados dentro desta função */
			
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	
	if (!al_init()){
		al_show_native_message_box((*display).display, "Erro", "Erro", "Falha ao inicializar o Allegro 5!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	if (!al_init_image_addon()){
		al_show_native_message_box((*display).display, "Erro", "Erro", "Falha ao inicializar al_init_image_addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	if (!al_init_primitives_addon()){
		al_show_native_message_box((*display).display, "Erro", "Erro", "Falha ao inicializar allegro_primitives!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	return 0;
}
//----------------------------------------------------------------------
int pi_setTelaAventura(GameScreen *nativeScreen, GameScreen *telaAventura, GameDisplay *display){
	/* Inicializa a tela do cenário do jogo calculando seu tamanho em relação a resolução original do jogo.
	   Ela compõe 2/3 do tamanho total do display. */

	DEBUG_ON("\n----debug:setTelaAventura():start");
	
	(*telaAventura).x1 = 0;
	(*telaAventura).x2 = ((*nativeScreen).width / 3) * 2;
	(*telaAventura).y1 = 0;
	(*telaAventura).y2 = (*nativeScreen).height;
	
	(*telaAventura).canvas = al_create_bitmap((*telaAventura).x2, (*telaAventura).y2);
	if (!(*telaAventura).canvas){
		al_show_native_message_box((*display).display, "Erro", "Erro", "Falha ao inicializar a Tela de Aventura!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	al_set_target_bitmap((*telaAventura).canvas);
	al_clear_to_color(al_map_rgb(100, 50, 200));
	
	DEBUG_ON("\ndebug:telaAventura:x2:%d", (*telaAventura).x2);
	DEBUG_ON("\ndebug:telaAventura:y2:%d", (*telaAventura).y2);
	DEBUG_ON("\n----debug:setTelaAventura():end\n");
	
	return 0;
}
//----------------------------------------------------------------------
int pi_setTelaPoderes(GameScreen *nativeScreen, GameScreen *telaPoderes, GameDisplay *display){
	/* Inicializa a tela de poderes calculando seu tamanho em relação a resolução original do jogo.
	 * Ela compõe 1/3 do tamanho total do display. */

	DEBUG_ON("\n----debug:setTelaPoderes():start");
	
	(*telaPoderes).x1 = (((*nativeScreen).width / 3) * 2);
	(*telaPoderes).x2 = (*nativeScreen).width;
	(*telaPoderes).width = (*nativeScreen).width - (((*nativeScreen).width / 3) * 2);
	(*telaPoderes).y1 = (*nativeScreen).y1;
	(*telaPoderes).y2 = (*nativeScreen).y2;
	(*telaPoderes).height = (*nativeScreen).height;
	
	(*telaPoderes).canvas = al_create_bitmap((*nativeScreen).width, (*nativeScreen).height);
	if (!(*telaPoderes).canvas){
		al_show_native_message_box((*display).display, "Erro", "Erro", "Falha ao inicializar a Tela de Poderes!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	al_set_target_bitmap((*telaPoderes).canvas);
	al_clear_to_color(al_map_rgb(0, 0, 0)); // limpa a tela

	al_set_clipping_rectangle((*telaPoderes).x1, (*telaPoderes).y1, (*telaPoderes).width, (*telaPoderes).height);
	al_clear_to_color(al_map_rgb(200, 50, 100));
	
	
	
	DEBUG_ON("\ndebug:telaPoderes:x1:%d", (*telaPoderes).x1);
	DEBUG_ON("\ndebug:telaPoderes:y1:%d", (*telaPoderes).y1);
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
	
	scaledX = (float)((*gameDisplay).width)  / (*nativeScreen).width;
	scaledY = (float)((*gameDisplay).height) / (*nativeScreen).height;
	
	/* Acha qual é o menor entre sx e sy e calcula a escala.
	   O cálculo é feito pelo menor valor para evitar que a imagem não ultrapasse os limites do monitor.*/
	if (scaledX < scaledY){
		(*gameDisplay).scale = scaledX;
	}
	else{
		(*gameDisplay).scale = scaledX;
	}
	
	/* Calcula as escalas a serem utilizadas */
	(*nativeScreen).scaledW = (*nativeScreen).width  * (*gameDisplay).scale;
	(*nativeScreen).scaledH = (*nativeScreen).height * (*gameDisplay).scale;
	
	/* Configura as novas escalas para X e Y */
	
	ALLEGRO_TRANSFORM trans;
	al_identity_transform(&trans);
	al_scale_transform(&trans, scaledX, scaledY);
	al_use_transform(&trans);
	
	DEBUG_ON("\ndebug:gameDisplay:scale:%f", 	 (*gameDisplay).scale);
	DEBUG_ON("\ndebug:nativeScreen:scaledW:%f",  (*nativeScreen).scaledW);
	DEBUG_ON("\ndebug:nativeScreen:scaledH:%f",  (*nativeScreen).scaledH);
	DEBUG_ON("\ndebug:gameDisplay:width:%d", 	 (*gameDisplay).width);
	DEBUG_ON("\ndebug:gameDisplay:height:%d", 	 (*gameDisplay).height);
	DEBUG_ON("\ndebug:nativeScreen:width:%d", 	 (*nativeScreen).width);
	DEBUG_ON("\ndebug:nativeScreen:height:%d\n", (*nativeScreen).height);
	
	DEBUG_ON("\n----debug:setDisplayScale():end\n");
	return;	
}
//----------------------------------------------------------------------
int pi_setFullScreen(GameScreen *nativeScreen, GameDisplay *display){
	
	DEBUG_ON("\n----debug:setFullScreen():start");
	// Configura para tela cheia.
	
	ALLEGRO_DISPLAY_MODE disp_data;
	
	al_get_display_mode((*display).mode, &disp_data); // Armazena em disp_data a maior resolução suportada pelo monitor

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	
	(*display).width = disp_data.width;
	(*display).height = disp_data.height;

	(*display).display = al_create_display((*display).width, (*display).height); // Cria o display em tela cheia.
	// Cria o buffer de desenho da tela. Todas as outras imagens são criadas dentro dele, assim basta mudar a escala dele.
	// e todo o resto é ajustado automaticamente.
	(*nativeScreen).canvas = al_create_bitmap((*nativeScreen).width, (*nativeScreen).height);
	
	if (!(*display).display){
		al_show_native_message_box((*display).display, "Erro", "Erro", "Falha ao inicializar o display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	if (!(*nativeScreen).canvas){
		al_show_native_message_box((*display).display, "Erro", "Erro", "Falha ao inicializar o displayBuffer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	DEBUG_ON("\n----debug:setFullScreen():end\n");
	return 0;
}
//----------------------------------------------------------------------
