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
  regras.push_back("F=FF[+VFF][-CF][>>VF][<XF]");

  LSystem *arvore = new LSystem(5, 5, 22.0, "F[+F][-F]", regras);

  vector<struct linha> linhas = arvore->gera_linhas();

  // Gira
  double rad = 10.0 * M_PI/180.0;
  double sinx = sin(rad);
  double cosx = cos(rad);

  double x, y, z;

  for(int k = 1; k < 200; k++) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for(int i = 0; i < linhas.size(); i++) {
      // Pinta com a cor correta
      if(linhas[i].cor == 1)
        SDL_SetRenderDrawColor(renderer, 58, 28, 2, SDL_ALPHA_OPAQUE);
      if(linhas[i].cor == 2)
        SDL_SetRenderDrawColor(renderer, 37, 147, 7, SDL_ALPHA_OPAQUE);
      if(linhas[i].cor == 3)
        SDL_SetRenderDrawColor(renderer, 37, 181, 5, SDL_ALPHA_OPAQUE);
      if(linhas[i].cor == 4)
        SDL_SetRenderDrawColor(renderer, 45, 252, 0, SDL_ALPHA_OPAQUE);

      // Desenha a linha
      SDL_RenderDrawLine(renderer, int(linhas[i].x0)+400, -int(linhas[i].y0)+600, int(linhas[i].x1)+400, -int(linhas[i].y1)+600);

      // Faz a rotação no eixo Y - Usei para teste
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