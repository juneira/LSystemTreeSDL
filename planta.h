#include "lsystem.h"

#define G_45 0.3535533905932738

struct ponto {
    double x;
    double y;
    double z;
};

class Planta: public LSystem {
    private:
        struct ponto posicao_objeto;
        struct ponto centro_universo;

        vector<struct linha> translada(struct ponto ponto_trans, vector<struct linha> _linhas) {
            vector<struct linha> linhas_trans = _linhas;

            for(int i = 0; i < linhas_trans.size(); i++) {
                linhas_trans[i].x0 += ponto_trans.x;
                linhas_trans[i].x1 += ponto_trans.x;

                linhas_trans[i].y0 += ponto_trans.y;
                linhas_trans[i].y1 += ponto_trans.y;

                linhas_trans[i].z0 += ponto_trans.z;
                linhas_trans[i].z1 += ponto_trans.z;
            }

            return linhas_trans;
        }
            
        vector<struct linha> rotaciona(char op, double angulo) {
            vector<struct linha> linhas_rot = linhas;

            double rad = angulo*M_PI/180.0;
            double sinx = sin(rad);
            double cosx = cos(rad);

            // Atualiza as linhas da planta
            for(int i = 0; i < linhas_rot.size(); i++) {
                switch(op) {
                    case 'x':
                        linhas_rot[i].y0 = linhas[i].y0*cosx + linhas[i].z0*(-sinx);
                        linhas_rot[i].y1 = linhas[i].y1*cosx + linhas[i].z1*(-sinx);

                        linhas_rot[i].z0 = linhas[i].y0*sinx + linhas[i].z0*(cosx);
                        linhas_rot[i].z1 = linhas[i].y1*sinx + linhas[i].z1*(cosx);
                    break;

                    case 'y':
                        linhas_rot[i].x0 = linhas[i].x0*cosx + linhas[i].z0*sinx;
                        linhas_rot[i].x1 = linhas[i].x1*cosx + linhas[i].z1*sinx;
                        
                        linhas_rot[i].z0 = linhas[i].x0*(-sinx) + linhas[i].z0*cosx;
                        linhas_rot[i].z1 = linhas[i].x1*(-sinx) + linhas[i].z1*cosx;
                    break;

                    case 'z':
                        linhas_rot[i].x0 = linhas[i].x0*cosx + linhas[i].y0*(-sinx);
                        linhas_rot[i].x1 = linhas[i].x1*cosx + linhas[i].y1*(-sinx);

                        linhas_rot[i].y0 = linhas[i].x0*sinx + linhas[i].y0*cosx;
                        linhas_rot[i].y1 = linhas[i].x1*sinx + linhas[i].y1*cosx;
                    break;
                }
            }

            // Atualiza posição da planta
            double x, y, z;
            
            x = posicao_objeto.x;
            y = posicao_objeto.y;
            z = posicao_objeto.z;

            switch(op) {
                case 'x':
                    y = posicao_objeto.y*cosx + posicao_objeto.z*(-sinx);
                    z = posicao_objeto.y*sinx + posicao_objeto.z*(cosx);
                break;

                case 'y':
                    x = posicao_objeto.x*cosx + posicao_objeto.z*sinx;
                    z = posicao_objeto.x*(-sinx) + posicao_objeto.z*cosx;
                break;

                case 'z':
                    x = posicao_objeto.x*cosx + posicao_objeto.y*(-sinx);
                    y = posicao_objeto.x*sinx + posicao_objeto.y*cosx;
                break;
            }

            posicao_objeto.x = x;
            posicao_objeto.y = y;
            posicao_objeto.z = z;
            
            return linhas_rot;
        }

    public:
        Planta(int _iteracoes, int _distancia, double _angulo, string _axioma, 
            vector<string> _regras, struct ponto _centro_universo, struct ponto _posicao_objeto)
            :LSystem(_iteracoes, _distancia, _angulo, _axioma, _regras)
            {
                
                centro_universo = _centro_universo;
                posicao_objeto = _posicao_objeto;

                struct ponto novo_ponto;
                
                novo_ponto.x = (posicao_objeto.x - centro_universo.x); 
                novo_ponto.y = (posicao_objeto.y - centro_universo.y);
                novo_ponto.z = (posicao_objeto.z - centro_universo.z);
                
                linhas = translada(novo_ponto, linhas);
            }

        vector<struct linha> projeta() {
            vector<struct linha> linhas_proj = linhas;

            for(int i = 0; i < linhas_proj.size(); i++) {
                linhas_proj[i].x0 = linhas_proj[i].x0 + linhas_proj[i].z0*G_45;
                linhas_proj[i].y0 = linhas_proj[i].y0 + linhas_proj[i].z0*G_45;
                linhas_proj[i].z0 = linhas_proj[i].z0;

                linhas_proj[i].x1 = linhas_proj[i].x1 + linhas_proj[i].z1*G_45;
                linhas_proj[i].y1 = linhas_proj[i].y1 + linhas_proj[i].z1*G_45;
                linhas_proj[i].z1 = linhas_proj[i].z0;
            }

            linhas_proj = translada(centro_universo, linhas_proj);            

            return linhas_proj;
        }

        vector<struct linha> projeta_rotaciona(char op, double angulo) {
            linhas = rotaciona(op, angulo);
            return projeta();
        }

        vector<struct linha> projeta_translada(struct ponto novo_ponto) {
            posicao_objeto.x += novo_ponto.x;
            posicao_objeto.y += novo_ponto.y;
            posicao_objeto.z += novo_ponto.z;
            
            linhas = translada(novo_ponto, linhas);
            return projeta();
        }

        struct ponto get_posicao_objeto() {
            return posicao_objeto;
        }
};