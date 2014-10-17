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
#include "pi_data.h"

/* Para ativar/desativar o debug, descomentar/comentar a linha abaixo */
#define _SET_DEBUG_ON
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
			
	BGImageStream bgFull;
	
	/* Inicia todos os addons utilizados no jogo. */
	if (pi_iniAllegroAddons(&gameDisplay) < 0)
		return -1;

	pi_iniScreens(&nativeScreen, &telaAventura, &telaPoderes); // Inicializa as telas do jogo.
	DEBUG_ON("\ndebug:nativeScreen:x2=%d", nativeScreen.x2);
		
	pi_iniBackground(&bgFull, LAYER_BG_FULL);
	pi_loadBackground(&bgFull);
	
	/* Inicializa o jogo em tela cheia */
 	if (pi_setFullScreen(&nativeScreen, &gameDisplay) < 0)
		return -1;
		
	 /* Configura a escala das coordenadas e tamanho da imagem no display */
	pi_setDisplayScale(&nativeScreen, &gameDisplay);
	
	/* Configura as telas de Aventura e Poderes de acordo com a resolução original do jogo
	   configurada em nativeScreen */
	pi_setTelaAventura(&nativeScreen, &telaAventura, &gameDisplay);
	pi_setTelaPoderes(&nativeScreen, &telaPoderes, &gameDisplay);
	
	//***** Inicio do looping principal

	pi_drawGraphics(NULL, 10, 10, REFRESH, &nativeScreen, &nativeScreen, &gameDisplay); // Limpa o backbuffer
	pi_drawGraphics(al_load_bitmap("img/guile.png"), 1300, 100, 0, &telaPoderes, &nativeScreen, &gameDisplay); // Desenha o bitmap na escala correta
	pi_drawGraphics(al_load_bitmap("img/fallout.jpg"), 0, 10, 0, &telaAventura, &nativeScreen, &gameDisplay); // Desenha o bitmap na escala correta
	
	al_flip_display();
	al_rest(1.0);
	pi_animateBackground(&bgFull);
	pi_drawGraphics(bgFull.tileSequence[0].canvas, 0, 0, REFRESH, &telaAventura, &nativeScreen, &gameDisplay);
	al_flip_display();
	al_rest(1.0);
	pi_animateBackground(&bgFull);
	pi_drawGraphics(bgFull.tileSequence[0].canvas, 0, 0, 0, &telaAventura, &nativeScreen, &gameDisplay);
	
	al_flip_display();
	al_rest(3.0);
	
	//**** Fim do programa. Destrói os componentes criados para evitar vazamento de memória.
	al_destroy_display(gameDisplay.display);
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
		al_show_native_message_box(display->display, "Erro", "Erro", "Falha ao carregar a imagem!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
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

	al_set_target_backbuffer(display->display);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	al_draw_bitmap(nativeScreen->canvas, 0, 0, 0);

	DEBUG_ON("\n----debug:drawGraphics():end");	

	return 0;
}
//----------------------------------------------------------------------
