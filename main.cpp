#include <iostream>
#include "universo.h"
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
  centro_universo.y = 0;
  centro_universo.z = 0;

  struct ponto posicao_objeto;

  posicao_objeto.x = 200;
  posicao_objeto.y = 0;
  posicao_objeto.z = 0;

  Planta* p1 = new Planta(4, 5, 22.0, "F[+F][-F]", regras, centro_universo, posicao_objeto);
  posicao_objeto.x = 250;
  posicao_objeto.z = 50;
  Planta* p2 = new Planta(4, 3, 22.0, "F[+F][-F]", regras, centro_universo, posicao_objeto);
  posicao_objeto.x = 300;
  posicao_objeto.z = 50;
  Planta* p3 = new Planta(4, 2, 22.0, "F[+F][-F]", regras, centro_universo, posicao_objeto);

  vector< Planta* > plantas;
  plantas.push_back(p1);
  plantas.push_back(p2);
  plantas.push_back(p3);

  // Cria o Universo
  Universo* universo = new Universo(centro_universo, plantas, renderer);
  
  for(int i = 0; i < 200; i++) {
    universo->desenha_rotaciona('y', 10.0);
    SDL_Delay(100);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
