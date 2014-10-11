/*
 * Código baseado no tutorial disponível em:
 * 		  https://wiki.allegro.cc/index.php?title=Achieving_Resolution_Independence
 */
#include "allegro5/allegro.h"
#include <stdio.h>

/* Para ativar o debug, descomentar a linha abaixo */
#define _SET_DEBUG_ON
#ifdef _SET_DEBUG_ON
	#define DEBUG_ON printf
#endif
#ifndef _SET_DEBUG_ON
	#define DEBUG_ON //
#endif

//----------------------------------------------------------------------
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
