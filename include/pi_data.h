#ifndef H_PI_DATA
	#define H_PI_DATA
	#include <allegro5/allegro.h>

	#define MAX_FILE_PATH_SIZE 30
	#define MAX_TAG_NAME_SIZE 20
	#define MAX_ARRAY_SIZE_SPRITEGROUP 40

	#define TELA_AVENTURA 1
	#define TELA_PODERES  2
	#define NATIVE_SCREEN 3
	#define REFRESH 4
	#define YES 5
	#define	NO 6
	#define DIR_OPPOSITE -1 // inverte a direção do movimento
	#define DIR_KEEP 1 // mantém o moviment na direção atual

	#define FPS 24

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
		int 	width;
		int 	height;
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
		int 	width;
		int 	height;
		int 	mode;
		float 	scale;
} GameDisplay;

// Estrutura base para armazenar imagens
typedef struct {
		ALLEGRO_BITMAP *canvas;
		int 	rest; // para usar no cálculo de velocidade do objeto
		int 	rest_countdown; // quando chegar a zero, o objeto é deslocado.
		int 	looping;
		float 	x1;
		float 	y1;
		float	startX; // posição X inicial, utilizada para looping
		float	startY;	// posição Y inicial, utilizada para looping
		float	endX; 	// posição X final, utilizada para looping
		float	endY;	// posição Y final, utilizada para looping
		float 	speedX;	// quantidade de pixels deslocados a cada iteração na animação
		float 	speedY; // quantidade de pixels deslocados a cada iteração na animação
		int 	directionX;	// direção do deslocamento 1 (acompanha o movimento), -1 (movimento contrário)
		int 	directionY;	// direção do deslocamento 1 (acompanha o movimento), -1 (movimento contrário)
		float 	depth; // profundidade no eixo Z.
		float 	width;
		float 	height;
		int 	reload; // 0 ou 1 para definir se a imagem precisa ser recarregada
} ImageTile;

// Estrutura para carregar em pedaços pequenos as imagens de background
typedef struct {
	ALLEGRO_BITMAP *buffer;
	int 	rest; // para usar no cálculo de velocidade do objeto
	int 	rest_countdown; // quando chegar a zero, o objeto é deslocado.
	int 	tileCount;
	int 	id;
	int 	layer;
	int 	width;
	int 	height;
	int 	currentIndex;
	int 	totalNumImgs;
	float 	depth;
	float 	x1;
	float 	y1;
	char 	*fileNamePrefix;
	char 	*dirPath;
	ImageTile tileSequence[59];
} BGImageStream;

typedef struct {
		ALLEGRO_BITMAP *canvas;
		int 	id;
		int 	rest; // para usar no cálculo de velocidade do objeto
		int 	rest_countdown; // quando chegar a zero, o objeto é deslocado.
		int		loop;
		float	startX;
		float	startY;
		float	endX;
		float	endY;
		float 	x1;
		float 	y1;
		float 	speedX;	// quantidade de pixels deslocados a cada iteração na animação
		float 	speedY; // quantidade de pixels deslocados a cada iteração na animação
		int 	directionX;	// direção do deslocamento 1 (acompanha o movimento), -1 (movimento contrário)
		int 	directionY;	// direção do deslocamento 1 (acompanha o movimento), -1 (movimento contrário)
		float 	depth; // profundidade no eixo Z.
		float 	width;
		float 	height;
		int 	reload; // 0 ou 1 para definir se a imagem precisa ser recarregada
		char	*tagName;
		char 	*dirPath;
		float  randVar;
		float  randVar2;
} StillSprite;

typedef struct {
		ALLEGRO_BITMAP *buffer;
		int 	id;
		float 	x1;
		float 	y1;
		float 	arraySize;
		float 	speedX;	// quantidade de pixels deslocados a cada iteração na animação
		float 	speedY; // quantidade de pixels deslocados a cada iteração na animação
		int 	directionX;	// direção do deslocamento 1 (acompanha o movimento), -1 (movimento contrário)
		int 	directionY;	// direção do deslocamento 1 (acompanha o movimento), -1 (movimento contrário)
		float 	depth; // profundidade no eixo Z.
		int 	reload; // 0 ou 1 para definir se a imagem precisa ser recarregada
		char 	*dirPath;
		StillSprite spriteArray[MAX_ARRAY_SIZE_SPRITEGROUP];
} SpriteGroup;


#endif
