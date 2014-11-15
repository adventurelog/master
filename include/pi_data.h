#ifndef H_PI_DATA
	#define H_PI_DATA
	#include <allegro5/allegro.h>

	#define MAX_FILE_PATH_SIZE 30
	#define MAX_TAG_NAME_SIZE 20
	#define MAX_ARRAY_SIZE_SPRITEGROUP 40
	#define MAX_ARRAY_SIZE_SPRITESHEET 40

	#define TELA_AVENTURA 1
	#define TELA_PODERES  2
	#define NATIVE_SCREEN 3
	#define REFRESH 4
	#define YES 5
	#define	NO 6
	#define DIR_OPPOSITE -1 // inverte a direção do movimento
	#define DIR_KEEP 1 // mantém o moviment na direção atual

	//#define FPS 24

	#define LAYER_BG_FULL 2
	#define LAYER_SCENE_GRASS 3
	#define LAYER_SCENE_GRASS_2 4
	#define LAYER_SCENE_TREELINE_1 5
	#define BG_TILE_WIDTH 100 // largura de cada pedaço do fundo a ser carregado
	#define BG_TILE_HEIGHT 1022 // largura de cada pedaço do fundo a ser carregado

	#define ID_GROUP_SPRITES 110
	#define ID_GROUP_SPRITES_SKY 111
	#define ID_GROUP_SPRITES_TREES 112
	#define ID_GROUP_SPRITES_GRASS 113
	#define ID_GROUP_SPRITES_TOMBS 114
	#define ID_GROUP_SPRITES_FOG 115
	#define ID_GROUP_SPRITES_GROUND 116
	#define ID_GROUP_SPRITES_GHOST 117
	
	#define ID_GHOST 118
	#define ID_LAPIDE_CRUZ 119
	#define ID_GRAMA 120
	#define ID_NEVOA 121
	#define ID_ARVORE 122

	#define ID_STILL_SPRITE 100

	#define LOOP_INFINITE -1

	#define PI 3.14159265

/*
  	enum KEYS {
		KEY_DOWN
	};
*/

typedef struct{
		ALLEGRO_BITMAP *canvas;
		int 	id;
		float 	x1;
		float 	x2;
		float 	y1;
		float 	y2;
		int 	largura;
		int 	altura;
		float 	scaledX;
		float 	scaledY;
		float 	scaledW;
		float 	scaledH;
} GameScreen;

// Display onde é armazenado todo o conteúdo atual do jogo, ou seja,
// é criado um display para cada parte do jogo: menu principal, jogo, pontuação
typedef struct{
		ALLEGRO_DISPLAY *backbuffer;
		ALLEGRO_TIMER	*timer;
		int 	largura;
		int 	altura;
		int 	mode;
		float 	scale;
} GameDisplay;

// Estrutura base para armazenar imagens
typedef struct {
		ALLEGRO_BITMAP *bitmap;
		int 	id;
		int 	spriteId[MAX_ARRAY_SIZE_SPRITESHEET];
		int 	rest; 									// para usar no cálculo de velocidade do objeto
		int 	rest_countdown; 						// quando chegar a zero, o objeto é deslocado.
		int		loop[MAX_ARRAY_SIZE_SPRITESHEET];
		float	inicioX[MAX_ARRAY_SIZE_SPRITESHEET];
		float	inicioY[MAX_ARRAY_SIZE_SPRITESHEET];
		float	fimX[MAX_ARRAY_SIZE_SPRITESHEET];
		float	fimY[MAX_ARRAY_SIZE_SPRITESHEET];		
		float 	posX[MAX_ARRAY_SIZE_SPRITESHEET];		// posicao atual do sprite
		float 	posY[MAX_ARRAY_SIZE_SPRITESHEET];		// posicao atual do sprite
		float	offsetX[MAX_ARRAY_SIZE_SPRITESHEET]; 	// deslocamento relativo ao x1, garantindo que o objeto fique no mesmo lugar quando reiniciar o looping  
		float	offsetY[MAX_ARRAY_SIZE_SPRITESHEET]; 	// deslocamento relativo ao y1, garantindo que o objeto fique no mesmo lugar quando reiniciar o looping  
		float 	velX[MAX_ARRAY_SIZE_SPRITESHEET];		// quantidade de pixels deslocados a cada iteração na animação
		float 	velY[MAX_ARRAY_SIZE_SPRITESHEET]; 	// quantidade de pixels deslocados a cada iteração na animação
		int 	dirX[MAX_ARRAY_SIZE_SPRITESHEET];	// direção do deslocamento 1 (acompanha o movimento), -1 (movimento contrário)
		int 	dirY[MAX_ARRAY_SIZE_SPRITESHEET];	// direção do deslocamento 1 (acompanha o movimento), -1 (movimento contrário)
		float 	profundidade[MAX_ARRAY_SIZE_SPRITESHEET];		// profundidade no eixo Z.
		float 	x1;
		float 	y1;
		float 	largura;
		float 	altura;
		float	novaLargura;
		float	novaAltura;
		int		sheetSizeX;
		int		sheetSizeY;
		int		repetirElementosX; // repetir os sprites no eixo X pelo número de vezes indicado
		int		repetirElementosY; // repetir os sprites no eixo Y  pelo número de vezes indicado
		int 	reload; // 0 ou 1 para definir se a imagem precisa ser recarregada
} SpriteSheet;

#endif
