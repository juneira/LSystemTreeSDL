#include "planta.h"
#include <algorithm>
#include <math.h>
#include <SDL2/SDL.h>

struct RGB {
    double R;
    double G;
    double B;
};

struct HSL {
    double H;
    double S;
    double L;
};

bool comp(Planta* a, Planta* b) { return a->get_posicao_objeto().z > b->get_posicao_objeto().z; }

class Universo {
    private:
        struct ponto centro_universo;
        vector< Planta* > plantas;
        SDL_Renderer* renderer;

        struct RGB HSL2RGB(struct HSL hsl) {
            double c = (1.0-fabs(2*hsl.L-1))*hsl.S;
            double x = c*(1-fabs(fmod(hsl.H/60.0, 2.0)-1.0));
            double m = hsl.L-c/2.0;

            struct RGB rgb;

            double r, g, b;

            if(0.0 <= hsl.H && hsl.H < 60.0) {
                r = c;
                g = x;
                b = 0;
            }
            else if(60.0 <= hsl.H && hsl.H < 120.0){
                r = x;
                g = c;
                b = 0;
            }
            else if(120.0 <= hsl.H && hsl.H < 180.0) {
                r = 0;
                g = c;
                b = x;
            }
            else if(180.0 <= hsl.H && hsl.H < 240.0) {
                r = 0;
                g = x;
                b = c;
            }
            else if(240.0 <= hsl.H && hsl.H < 300.0) {
                r = x;
                g = 0;
                b = c;
            }
            else if(hsl.H < 360.0) {
                r = c;
                g = 0;
                b = x;
            }

            rgb.R = (r+m)*255.0; 
            rgb.G = (g+m)*255.0;
            rgb.B = (b+m)*255.0;

            return rgb;
        }

        struct HSL RGB2HSL(struct RGB rgb) {
            double r = double(rgb.R)/255.0;
            double g = double(rgb.G)/255.0;
            double b = double(rgb.B)/255.0;
            
            double cmax = max(max(r, g), b);
            double cmin = min(min(r, g), b);
            double delta = cmax - cmin;

            struct HSL hsl;
            
            // L
            hsl.L = (cmax + cmin)/2.0;            

            // H
            if(delta == 0)     hsl.H = 0.0;
            else if(cmax == r) hsl.H = 60.0*fmod(((g-b)/delta), 6.0);
            else if(cmax == g) hsl.H = 60.0*(((b-r)/delta)+2.0);
            else if(cmax == b) hsl.H = 60.0*(((r-g)/delta)+4.0);

            // S
            if(delta == 0) hsl.S = 0;
            else           hsl.S = (delta/(1.0-fabs(2.0*hsl.L-1.0)));

            return hsl;
        }

        void escolhe_cor(struct RGB rgb, double z) {
            struct HSL hsl = RGB2HSL(rgb);

            double k = hsl.L - (2*z)/2000.0;
            hsl.L = fmax(k, 0);

            rgb = HSL2RGB(hsl);

            SDL_SetRenderDrawColor(renderer, rgb.R, rgb.G, rgb.B, SDL_ALPHA_OPAQUE);
        }

        void limpa_tela() {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
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

            // Ordena pelo eixo Z (Algoritmo do Pintor)
            sort(plantas.begin(), plantas.end(), comp);

            vector<linha> linhas;
            for(int i = 0; i < plantas.size(); i++) {
                linhas = plantas[i]->projeta();

                // Busca o eixo Z da planta
                double z = linhas[0].z0;

                for(int j = 0; j < linhas.size(); j++) {
                    // Pinta com a cor correta
                    struct RGB rgb;

                    if(linhas[j].cor == 2) {
                        rgb.R = 37.0;
                        rgb.G = 147.0;
                        rgb.B = 7.0;
                    }
                    else if(linhas[j].cor == 3) {
                        rgb.R = 37.0;
                        rgb.G = 181.0;
                        rgb.B = 5.0;
                    }
                    else if(linhas[j].cor == 4) {
                        rgb.R = 45.0;
                        rgb.G = 252.0;
                        rgb.B = 0.0;
                    }
                    else {
                        rgb.R = 58.0;
                        rgb.G = 28.0;
                        rgb.B = 2.0;
                    }
                    
                    // Esolhe a cor e aplica iluminação
                    escolhe_cor(rgb, z);
                    
                    // Desenha a linha
                    SDL_RenderDrawLine(renderer, int(linhas[j].x0), 600-int(linhas[j].y0), int(linhas[j].x1), 600-int(linhas[j].y1));
                }
            }

            SDL_RenderPresent(renderer);
        }

        void rotaciona(char op, double angulo) {
            for(int i = 0; i < plantas.size(); i++)
                plantas[i]->projeta_rotaciona(op, angulo);
        }

        void translata(struct ponto centro_universo) {
            for(int i = 0; i < plantas.size(); i++)
                plantas[i]->projeta_translata(centro_universo);  
        }
};