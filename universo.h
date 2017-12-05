#include "planta.h"
#include <SDL2/SDL.h>

class Universo {
    private:
        struct ponto centro_universo;
        vector< Planta* > plantas;
        SDL_Renderer* renderer;

        void rotaciona(char op, double angulo) {
            
        }
            
        void translata(char op, double angulo) {
                        
        }

        void limpa_tela() {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);
        }

    public:
        Universo(struct ponto _centro_universo, vector< Planta* > _plantas, SDL_Renderer* _renderer) {
            centro_universo = _centro_universo;
            plantas = _plantas;
            renderer = _renderer;
        }

        void desenha() {
            limpa_tela();

            vector<linha> linhas;

            for(int i = 0; i < plantas.size(); i++) {
                linhas = plantas[i]->projeta();

                for(int j = 0; j < linhas.size(); j++) {
                    // Pinta com a cor correta
                    if(linhas[j].cor == 1)
                        SDL_SetRenderDrawColor(renderer, 58, 28, 2, SDL_ALPHA_OPAQUE);
                    if(linhas[j].cor == 2)
                        SDL_SetRenderDrawColor(renderer, 37, 147, 7, SDL_ALPHA_OPAQUE);
                    if(linhas[j].cor == 3)
                        SDL_SetRenderDrawColor(renderer, 37, 181, 5, SDL_ALPHA_OPAQUE);
                    if(linhas[j].cor == 4)
                        SDL_SetRenderDrawColor(renderer, 45, 252, 0, SDL_ALPHA_OPAQUE);

                    // Desenha a linha
                    SDL_RenderDrawLine(renderer, int(linhas[j].x0), 600-int(linhas[j].y0), int(linhas[j].x1), 600-int(linhas[j].y1));
                }
            }

            SDL_RenderPresent(renderer);
        }

        void desenha_rotaciona(char op, double angulo) {
            for(int i = 0; i < plantas.size(); i++)
                plantas[i]->projeta_rotaciona(op, angulo);
            desenha();
        }

        void desenha_translata() {

        }
};