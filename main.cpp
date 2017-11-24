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
  
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  // Cria a tela
  SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

  // Desenha arvore
  vector<string> regras;
  regras.push_back("F=F[+F][-F][>F]");

  LSystem *arvore = new LSystem(5, 20, 23.0, "F", regras);

  vector<struct linha> linhas = arvore->gera_linhas();

  // Gira
  double ang = M_PI/180.0;
  double rad = 30.0 * ang;
  double sinx = sin(rad);
  double cosx = cos(rad);

  for(int k = 1; k < 50; k++) {
    double x0, y0, x1, y1;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for(int i = 0; i < linhas.size(); i++) {
      //x0 = linhas[i].x0;
      linhas[i].x0 = (linhas[i].x0*cosx + linhas[i].z0*sinx);
      linhas[i].y0 = linhas[i].y0;
      
      //x1 = linhas[i].x1;
      linhas[i].x1 = (linhas[i].x1*cosx + linhas[i].z1*sinx);
      linhas[i].y1 = linhas[i].y1;

      SDL_RenderDrawLine(renderer, int(linhas[i].x0)+300, -int(linhas[i].y0)+200, int(linhas[i].x1)+300, -int(linhas[i].y1)+200);
    }
    
    SDL_RenderPresent(renderer);
    SDL_Delay(50);  
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
