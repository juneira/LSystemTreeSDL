#include <iostream>
#include <string>
#include <vector>
#include "lsystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>

/* DEFINES */

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;

/* Funções utilitárias */

int aplicaLuz(int cor, double luz) {
  cor = int(cor*-luz)*2;
  if(cor < 0) cor = 0;

  return min(255, cor);
}


Uint32* getPixel(SDL_Surface* surface, int x, int y) {
  return ((Uint32 *) surface->pixels + y * surface->w + x);
}

void linhaDDA(SDL_Surface* surface, int xi, int yi, int zi, int xf, int yf, int zf, int corR, int corG, int corB) {
  int dx = xf - xi, dy = yf - yi, etapas;
  float incX, incY, x = xi, y = yi;

  etapas = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

  incX = dx/(float) etapas;
  incY = dy/(float) etapas;

  Uint32* pixel = NULL;

  if(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
    pixel = getPixel(surface, x, y);
    *(pixel) = SDL_MapRGB(surface->format, corR, aplicaLuz(50, zf/20.0), corB);
  }

  for(int i = 0; i < etapas; i++) {
    x += incX;
    y += incY;

    if(x < 0 || y < 0)
      continue;

    pixel = getPixel(surface, x, y);
    *(pixel) = SDL_MapRGB(surface->format, corR, corG, corB);
  }
}


int main(int argc, char* args[]) {
  SDL_Surface* windowSurface = NULL;

  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL não pode iniciar! Error: %s\n", SDL_GetError());
  }

	window = SDL_CreateWindow
	(
		"SDL Tutorial",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
		
	if(window == NULL) {
		printf("A janela não pode ser criada! Error: %s\n", SDL_GetError());
		return -1;
  }
  
  windowSurface = SDL_GetWindowSurface(window);
  
  
  // -----

  // Desenha arvore
  vector<string> regras;
  regras.push_back("F=FF[+F][-F][>>F]");

  LSystem *arvore = new LSystem(5, 5, 40.0, "F", regras);

  vector<struct linha> linhas = arvore->gera_linhas();

  // Gira
  double rad = 10.0 * M_PI/180.0;
  double sinx = sin(rad);
  double cosx = cos(rad);

  double x, y, z;

  for(int k = 1; k < 200; k++) {
    SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);

    for(int i = 0; i < linhas.size(); i++) {
      int R, G, B;

      linhaDDA(windowSurface, int(linhas[i].x0)+300, -int(linhas[i].y0)+400, linhas[i].z0, int(linhas[i].x1)+300, -int(linhas[i].y1)+400, linhas[i].z1,
        0, 50, 0);

      x = (linhas[i].x0*cosx + linhas[i].z0*sinx);
      y = linhas[i].y0;
      z = (linhas[i].x0*(-sinx) + linhas[i].z0*cosx);

      linhas[i].x0 = x;
      linhas[i].y0 = y;
      linhas[i].z0 = z;
      
      x = (linhas[i].x1*cosx + linhas[i].z1*sinx);
      y = linhas[i].y1;
      z = (linhas[i].x1*(-sinx) + linhas[i].z1*cosx);

      linhas[i].x1 = x;
      linhas[i].y1 = y;
      linhas[i].z1 = z;
    }
    
    SDL_UpdateWindowSurface(window);
    SDL_Delay(50);  
  }

  // ----

  SDL_DestroyWindow(window);
  SDL_Quit();
  exit(0);

  return 0;
}
