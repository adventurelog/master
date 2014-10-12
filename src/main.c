/*
 * Baseado nos seguitnes códigos-fonte:
 * 		https://wiki.allegro.cc/index.php?title=Achieving_Resolution_Independence
 * 		https://wiki.allegro.cc/index.php?title=Allegro_5_Tutorial/Displays
 * 		https://wiki.allegro.cc/index.php?title=Creating_a_fullscreen_display_with_maximum/minimum_resolution
 * 		
 */
 
#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <stdio.h>

#include "pi_tools.h"

/* Para ativar/desativar o debug, descomentar/comentar a linha abaixo */
#define _SET_DEBUG_ON
#ifdef 	_SET_DEBUG_ON
	#define DEBUG_ON printf
#endif
#ifndef _SET_DEBUG_ON
	#define DEBUG_ON //
#endif

/* flags */
#define TELA_AVENTURA 1
#define TELA_PODERES  2

ALLEGRO_DISPLAY 	*display		= NULL; /* display do jogo */
ALLEGRO_DISPLAY_MODE disp_mode;
ALLEGRO_BITMAP 		*displayBuffer	= NULL; /* buffer de desenho do jogo que possibilita mudar a escala para outra resolução de tela */
ALLEGRO_BITMAP		*currentImage	= NULL;
ALLEGRO_BITMAP		*telaAventura	= NULL;
ALLEGRO_BITMAP		*telaPoderes	= NULL;

float scaleW, scaleH, displayScale, scaleX, scaleY = 1.0;
int displayWidth; /* Tela cheia: largura. */
int displayHeight; /* Tela cheia: altura. */
int telaA_x1, telaA_x2, telaA_y1, telaA_y2; /* Dimensões da Tela de Aventura */
int telaP_x1, telaP_x2, telaP_y1, telaP_y2; /* Dimensões da Tela de Poderes */

//----------------------------------------------------------------------
int pi_drawGraphics(ALLEGRO_BITMAP *image, int x, int y, int refresh, int tela);

//======================================================================
int main(int argc, char **argv[]){
	
	DEBUG_ON("\n================================");
	DEBUG_ON("\ndebug:main():start");
	DEBUG_ON("\n================================");
	
	/* Resolução original do jogo. */
	int gameScreenWidth = 1920;
	int gameScreenHeight = 1080;

	/* Modo da resolução da tela
	* 0: resolução máxima comportada
	* 1: metade
	* al_get_num_display_modes()-1: mínima
	*/
	int displayMode = 0;
	
	/* Inicia todos os addons utilizados no jogo. */
	if (pi_initAllegroAddons() < 0)
		return -1;
		
	/* Inicializa o jogo em tela cheia */
 	if (pi_setFullScreen(&displayMode, &displayWidth, &displayHeight, &gameScreenWidth, &gameScreenHeight) < 0)
		return -1;
		
	 /* Configura a escala das coordenadas e tamanho da imagem no display */
	setDisplayScale(&gameScreenWidth, &gameScreenHeight, &displayWidth, &displayHeight, &displayScale, &scaleW, &scaleH, &scaleX, &scaleY);
	
	/* Configura a Tela de Aventura de acordo com a resolução do monitor */
	pi_setTelaAventura(&gameScreenWidth, &gameScreenHeight, &telaA_x1, &telaA_x2, &telaA_y1, &telaA_y2);
	pi_setTelaPoderes(&gameScreenWidth, &gameScreenHeight, &telaP_x1, &telaP_x2, &telaP_y1, &telaP_y2);
	
	pi_drawGraphics(NULL, 10, 10, 1, 0); // Limpa o backbuffer
	pi_drawGraphics(al_load_bitmap("img/fallout.jpg"), 0, 10, 0, TELA_AVENTURA); // Desenha o bitmap na escala correta
	pi_drawGraphics(al_load_bitmap("img/guile.png"), 1300, 100, 0, TELA_PODERES); // Desenha o bitmap na escala correta
	// Inicio do looping principal
	
	al_flip_display();
	al_rest(3.0);
	
	DEBUG_ON("\ndebug:displayScale:%f", displayScale);
	
	// Termino do programa. Destrói os componentes criados para evitar vazamento de memória.
	al_destroy_display(display);
	al_destroy_bitmap(displayBuffer);
	al_destroy_bitmap(currentImage);

	DEBUG_ON("\n================================");
	DEBUG_ON("\ndebug:main():end");
	DEBUG_ON("\n================================\n");

}
//======================================================================
int pi_drawGraphics(ALLEGRO_BITMAP *image, int x, int y, int refresh, int tela){
	
	DEBUG_ON("\n----------------------");
	DEBUG_ON("\ndebug:drawGraphics():start");	
	DEBUG_ON("\n----------------------");
	DEBUG_ON("\ndebug:tela:%d", tela);	


	if (!image && tela != 0){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao carregar a imagem!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		//al_destroy_display(display);
		return -1;
	}
	
	ALLEGRO_BITMAP *target = NULL;
	
	/* flags */
	switch(tela){
		case TELA_AVENTURA:
			target = telaAventura;
			break;
		case TELA_PODERES:
			target = telaPoderes;
			break;
		default:
			target = displayBuffer;
	}
	
	al_set_target_bitmap(target);
	
	if (refresh){
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	if (tela == 0) /* Caso image=null e tela==0, sai da função após ter limpado o buffer */
			return 0;
	
	al_draw_bitmap(image, x, y, 0);

	al_set_target_bitmap(displayBuffer);
	if (tela == TELA_PODERES) /* Cria uma mascara para a tela de poderes */
			al_draw_bitmap_region(target, telaP_x1, telaP_y1, telaP_x2, telaP_y2, telaP_x1, telaP_y1, 0);
	else
		al_draw_bitmap(target, 0, 0, 0);

	al_set_target_backbuffer(display);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	al_draw_bitmap(displayBuffer, 0, 0, 0);

	DEBUG_ON("\ndebug:drawGraphics():end");	

	return 0;
}
//----------------------------------------------------------------------
