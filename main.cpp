#include <iostream>
#include "planta.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>

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

  struct ponto centro_universo;

  centro_universo.x = 400;
  centro_universo.y = 300;
  centro_universo.z = 0;

  struct ponto posicao_objeto;

  posicao_objeto.x = 600;
  posicao_objeto.y = 300;
  posicao_objeto.z = 0;

  Planta *p = new Planta(4, 5, 22.0, "F[+F][-F]", regras, centro_universo, posicao_objeto);

  vector<struct linha> linhas;

  // Gira
  double rad = 10.0 * M_PI/180.0;
  double sinx = sin(rad);
  double cosx = cos(rad);

  for(int j = 0; j < 300; j++) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    linhas = p->projeta_rotaciona('y', 2);

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
      //cout << int(linhas[i].x0) << ' ' << int(linhas[i].y0) << ' ' << int(linhas[i].x1) << ' ' << int(linhas[i].y1) << '\n';
      SDL_RenderDrawLine(renderer, int(linhas[i].x0), 600-int(linhas[i].y0), int(linhas[i].x1), 600-int(linhas[i].y1));
    }
    SDL_Delay(20);
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}