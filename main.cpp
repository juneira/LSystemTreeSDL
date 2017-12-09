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

  for(int i = 0; i < 200; i++) {
    posicao_objeto.x = 400 + (400 - rand()%800);
    posicao_objeto.z = 400 - rand()%800;

    plantas.push_back(new Planta(rand()%3+1, 3, 22.0, axiomas[rand()%3], regras, centro_universo, posicao_objeto));
  }

  // Cria o Universo
  Universo* universo = new Universo(centro_universo, plantas, renderer);

  // Printa o Universo
  universo->desenha();

	//Pressiona ESC para sair
  SDL_Event event;
	bool flag_exit = false;
	while(true) {
		while(SDL_PollEvent(&event)) { //Escuta um evento
		  switch(event.type){ //Eventos do teclado
		    case SDL_KEYDOWN:
		    	switch( event.key.keysym.sym ){
					
          case SDLK_LEFT:
            universo->rotaciona('y', -10.0);
            universo->desenha();
            break;

          case SDLK_RIGHT:
            universo->rotaciona('y', 10.0);
            universo->desenha();
            break;
          
          case SDLK_UP:          
            centro_universo.x = 0;
            centro_universo.y = 0;
            centro_universo.z = 10;

            universo->translada(centro_universo);
            universo->desenha();
            break;

          case SDLK_DOWN:          
            centro_universo.x = 0;
            centro_universo.y = 0;
            centro_universo.z = -10;

            universo->translada(centro_universo);
            universo->desenha();
            break;

          case SDLK_ESCAPE:
						flag_exit = true;			      
		    	}
		  	}
		}
	  if (flag_exit) 
	  	break;
	}

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
