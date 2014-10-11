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

#include "pi_display_tools.h"
#include "pi_transform_tools.h"

/* Para ativar/desativar o debug, descomentar/comentar a linha abaixo */
#define _SET_DEBUG_ON
#ifdef _SET_DEBUG_ON
	#define DEBUG_ON printf
#endif
#ifndef _SET_DEBUG_ON
	#define DEBUG_ON //
#endif

/* display do jogo */
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_DISPLAY_MODE disp_mode;
/* buffer de desenho do jogo que possibilita mudar a escala para outra resolução de tela */
ALLEGRO_BITMAP 	*displayBuffer = NULL;
ALLEGRO_BITMAP	*currentImage = NULL;

//----------------------------------------------------------------------
int pi_drawScaledBitmap(ALLEGRO_BITMAP *image, int x, int y, int refresh);
//======================================================================
int main(int argc, char **argv[]){

	/* Resolução original do jogo. */
	int gameScreenWidth = 1920;
	int gameScreenHeight = 1080;

	/* Modo da resolução da tela
	* 0: resolução máxima comportada
	* 1: metade
	* al_get_num_display_modes()-1: mínima
	*/
	int displayMode = 0;

	float scaleW, scaleH, displayScale, scaleX, scaleY = 1.0;
	int displayWidth; /* Tela cheia: largura. */
	int displayHeight; /* Tela cheia: altura. */
	
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
	
	/* Inicializa o jogo em tela cheia */
 	if (pi_setFullScreen(&displayMode, &displayWidth, &displayHeight, &gameScreenWidth, &gameScreenHeight) < 0)
		return -1;
		
	 /* Configura a escala das coordenadas e tamanho da imagem no display */
	setDisplayScale(&gameScreenWidth, &gameScreenHeight, &displayWidth, &displayHeight, &displayScale, &scaleW, &scaleH, &scaleX, &scaleY);
	
	currentImage = al_load_bitmap("img/fallout.jpg");
	pi_drawScaledBitmap(currentImage, 10, 10, 1); // Desenha o bitmap na escala correta

	currentImage = al_load_bitmap("img/guile.png");
	pi_drawScaledBitmap(currentImage, 1918, 1078, 0); // Desenha o bitmap na escala correta
	// Inicio do looping principal
	
	al_flip_display();
	al_rest(3.0);
	
	DEBUG_ON("\ndebug:displayScale:%f\n", displayScale);
	
	// Termino do programa. Destrói os componentes criados para evitar vazamento de memória.
	al_destroy_display(display);
	al_destroy_bitmap(currentImage);
}
//======================================================================
int pi_drawScaledBitmap(ALLEGRO_BITMAP *image, int x, int y, int refresh){
	
	DEBUG_ON("\ndebug:drawScaledBitmap\n");	
	if (!image){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao carregar a imagem!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		//al_destroy_display(display);
		return -1;
	}
	
	al_set_target_bitmap(displayBuffer);
	
	if (refresh)
		al_clear_to_color(al_map_rgb(0, 0, 0));
	
	al_draw_bitmap(image, x, y, 0);
	
	al_set_target_backbuffer(display);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	//al_draw_scaled_bitmap(displayBuffer, 0, 0, al_get_bitmap_width(displayBuffer), al_get_bitmap_height(displayBuffer), 0, 0, scaleW, scaleH, 0);
	al_draw_bitmap(displayBuffer, 0, 0, 0);
	return 0;
}
//----------------------------------------------------------------------
