#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <stdio.h>

#include "../lib/pi_transform_tools.h"

/* Para ativar/desativar o debug, descomentar/comentar a linha abaixo */
#define _SET_DEBUG_ON
#ifdef _SET_DEBUG_ON
	#define DEBUG_ON printf
#endif
#ifndef _SET_DEBUG_ON
	#define DEBUG_ON //
#endif

/* Resolução original do jogo. */
int gameScreenWidth = 1920;
int gameScreenHeight = 1080;

/* display do jogo */
ALLEGRO_DISPLAY *display = NULL;
/* buffer de desenho do jogo que possibilita mudar a escala para outra resolução de tela */
ALLEGRO_BITMAP 	*displayBuffer = NULL;
ALLEGRO_BITMAP	*image = NULL;

float scaleW, scaleH, displayScale = 1.0;
int displayWidth; /* Tela cheia: largura. */
int displayHeight; /* Tela cheia: altura. */

//----------------------------------------------------------------------
int pi_setFullScreen(void);
int pi_drawScaledBitmap(ALLEGRO_BITMAP *image, int x, int y, int refresh);
//======================================================================
int main(int argc, char **argv[]){
			
	if (!al_init()){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao inicializar o Allegro 5!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}
	
	if (!al_init_image_addon()){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao inicializar al_init_image_addon!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}
	
	pi_setFullScreen(); // Inicializa o jogo em tela cheia
	
	image = al_load_bitmap("../img/fallout.jpg");
	pi_drawScaledBitmap(image, 10, 10, 1); // Desenha o bitmap na escala correta

	image = al_load_bitmap("../img/guile.png");
	pi_drawScaledBitmap(image, 1918, 1078, 0); // Desenha o bitmap na escala correta
	// Inicio do looping principal
	
	al_flip_display();
	al_rest(3.0);
	
	// Termino do programa. Destrói os componentes criados para evitar vazamento de memória.
	al_destroy_display(display);
	al_destroy_bitmap(image);
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
	
	al_draw_scaled_bitmap(displayBuffer, 0, 0, al_get_bitmap_width(displayBuffer), al_get_bitmap_height(displayBuffer), 0, 0, scaleW, scaleH, 0);
	
	return 0;
}

//----------------------------------------------------------------------
int pi_setFullScreen(void){
	
	DEBUG_ON("\ndebug:setFullScreen\n");
	// Configura para tela cheia.
	
	ALLEGRO_DISPLAY_MODE disp_data;
	
	al_get_display_mode(0, &disp_data); // Armazena em disp_data a maior resolução suportada pelo monitor

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	
	displayWidth = disp_data.width;
	displayHeight = disp_data.height;

	display = al_create_display(displayWidth, displayHeight); // Cria o display em tela cheia.
	// Cria o buffer de desenho da tela. Todas as outras imagens são criadas dentro dele, assim basta mudar a escala dele.
	// e todo o resto é ajustado automaticamente.
	displayBuffer = al_create_bitmap(gameScreenWidth, gameScreenHeight);
	
	if (!display){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao inicializar o display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	if (!displayBuffer){
		al_show_native_message_box(display, "Erro", "Erro", "Falha ao inicializar o displayBuffer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	setDisplayScale(&gameScreenWidth, &gameScreenWidth, &displayWidth, &displayHeight, &displayScale);
	
	/* Calcula a proporção da escala 
	float sx 	= (float)displayWidth / gameScreenWidth;
	float sy	= (float)displayHeight / gameScreenHeight;
	
	/* Acha qual é o menor entre sx e sy e calcula a escala.
	   O cálculo é feito pelo menor valor para evitar que a imagem não ultrapasse os limites do monitor.
	if (sx > sy){
		displayScale = sx;
	}
	else{
		displayScale = sy;
	}
	
	/* Calcula as escalas a serem utilizadas 
	scaleW	= gameScreenWidth * displayScale;
	scaleH	= gameScreenHeight * displayScale;
	
	printf("\ndebug:scale:%f", displayScale);
	printf("\ndebug:ScaleW:%f", scaleW);
	printf("\ndebug:ScaleH:%f", scaleH);
	printf("\ndebug:displayWidth:%d", displayWidth);
	printf("\ndebug:displayHeight:%d", displayHeight);
	printf("\ndebug:gameScreenWidth:%d", gameScreenWidth);
	printf("\ndebug:gameScreenHeight:%d\n", gameScreenHeight);
	*/
	return 0;
}
