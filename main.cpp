#include <iostream>
#include <string>
#include <vector>
#include "lsystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[]) {
  SDL_Surface* windowSurface = NULL;
  
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  // Cria a tela
  SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

  // Desenha arvore
  vector<string> regras;
  regras.push_back("F=FF[+F][-F][>F][<F]");

  LSystem *arvore = new LSystem(4, 5, 40.0, "F", regras);

  vector<struct linha> linhas = arvore->gera_linhas();

  // Gira
  double rad = 5.0 * M_PI/180.0;
  double sinx = sin(rad);
  double cosx = cos(rad);

  for(int k = 1; k < 50; k++) {
    double x0, y0, x1, y1;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for(int i = 0; i < linhas.size(); i++) {
      SDL_RenderDrawLine(renderer, int(linhas[i].x0)+300, -int(linhas[i].y0)+200, int(linhas[i].x1)+300, -int(linhas[i].y1)+200);
      
      double x, y, z;

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
    
    SDL_RenderPresent(renderer);
    SDL_Delay(50);  
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
