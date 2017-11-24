#include <iostream>
#include <string>
#include <vector>
#include "lsystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = NULL;

Uint32* getPixel(SDL_Surface* surface, int x, int y) {
  return ((Uint32 *) surface->pixels + y * surface->w + x);
}

void linhaDDA(SDL_Surface* surface, int xi, int yi, int xf, int yf, int corR, int corG, int corB) {
  int dx = xf - xi, dy = yf - yi, etapas;
  float incX, incY, x = xi, y = yi;

  etapas = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

  incX = dx/(float) etapas;
  incY = dy/(float) etapas;

  Uint32* pixel = NULL;

  if(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
    pixel = getPixel(surface, x, y);
    *(pixel) = SDL_MapRGB(surface->format, corR, corG, corB);
  }

  for(int i = 0; i < etapas; i++) {
    x += incX;
    y += incY;

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

  SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);

  // Desenha arvore
  vector<string> regras;
  regras.push_back("F=FF-[-F+F]+[+F-F]");
  LSystem *arvore = new LSystem(6, 2, 22.0, "F", regras);

  vector<struct linha> linhas = arvore->gera_linhas();

  for(int i = 0; i < linhas.size(); i++) {
    cout << linhas[i].x0 << ' ' << linhas[i].y0 << ' ' << linhas[i].x1 << ' ' << linhas[i].y1 << '\n';
    linhaDDA(windowSurface, int(linhas[i].x0)+300, -int(linhas[i].y0)+600, int(linhas[i].x1)+300, -int(linhas[i].y1)+600, 0, 50, 0);
  }

  SDL_UpdateWindowSurface(window);

  SDL_Delay(3000);  

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
