#include <iostream>
#include <time.h>
#include "universo.h"
#include <SDL2/SDL_keyboard.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[]) {
  srand (time(NULL));
  
  SDL_Surface* windowSurface = NULL;
  
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  // Cria a tela
  SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

  // Desenha arvore
  vector<string> regras;
  regras.push_back("F=FF[+VFF][-CF][>>VF][<XF]");
  

  vector<string> axiomas;
  axiomas.push_back("F[+F][-F]");
  axiomas.push_back("F[>F][<F][+F+F]");
  axiomas.push_back("F[+F<F][-F>F]");

  struct ponto centro_universo;

  centro_universo.x = 400;
  centro_universo.y = 0;
  centro_universo.z = 0;

  vector< Planta* > plantas;  
  
  struct ponto posicao_objeto;

  // Adicionando plantas
  posicao_objeto.x = 250;
  posicao_objeto.y = 20;
  posicao_objeto.z = 0;
  plantas.push_back(new Planta(3, 3, 22.0, "F[+F][-F][<F][>F]", regras, centro_universo, posicao_objeto));
  posicao_objeto.x = 250;
  posicao_objeto.z = -50;
  plantas.push_back(new Planta(2, 3, 22.0, "F[+F][-F][<F][>F]", regras, centro_universo, posicao_objeto));
  posicao_objeto.x = 400;
  posicao_objeto.z = 0;
  plantas.push_back(new Planta(4, 6, 22.0, "F[+F][-F][<F][>F]", regras, centro_universo, posicao_objeto));

  for(int i = 0; i < 100; i++) {
    posicao_objeto.x = 400 + (200 - rand()%400);
    posicao_objeto.z = 200 - rand()%400;

    plantas.push_back(new Planta(rand()%3+1, 3, 22.0, axiomas[rand()%3], regras, centro_universo, posicao_objeto));
  }
  

  // Cria o Universo
  Universo* universo = new Universo(centro_universo, plantas, renderer);
  
  for(int i = 0; i < 50; i++) {
    universo->desenha_rotaciona('y', 10.0);
    SDL_Delay(100);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
