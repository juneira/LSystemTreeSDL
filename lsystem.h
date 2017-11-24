#include <string.h>
#include <stack>
#include <cmath> 

using namespace std;

struct tupla {
    double x;
    double y;
    double ang;
};

struct linha {
    double x0;
    double y0;
    double x1;
    double y1;
};

class LSystem {
    private:
        int iteracoes;
        int distancia;
        double angulo;
        string axioma;
        vector<string> regras;

        /*
            Função string gera_cadeia()
            Com base no axioma, iterações e regras, realiza calculos e retorna cadeia resultante
        */
        string gera_cadeia() {
            int it = iteracoes;
            string nova_cadeia = axioma;
            while(it--) {
                for(int i = 0 ; i < regras.size(); i++) {
                    char alvo = regras[i][0];

                    int inicio_cadeia = 2;
                    int final_cadeia = regras[i].size();

                    string cadeia = regras[i].substr(inicio_cadeia, final_cadeia);

                    string cadeia_modificada;

                    for(int j = 0; j < nova_cadeia.size(); j++) {
                        if(nova_cadeia[j] == alvo)
                            cadeia_modificada += cadeia;
                        else
                            cadeia_modificada += nova_cadeia[j];
                    }

                    nova_cadeia = cadeia_modificada;
                }
            }

            return nova_cadeia;
        }

    public:
        LSystem(int _iteracoes, int _distancia, double _angulo, string _axioma, vector<string> _regras) {
            iteracoes = _iteracoes;
            angulo = _angulo;
            axioma = _axioma;
            regras = _regras;
            distancia = _distancia;
        }

        /*
            Função vector<struct linha> gera_linhas()
            Usa a cadeia resultante para gerar linhas com origem de (x, y) em (0, 0) 
        */
        vector<struct linha> gera_linhas() {
            vector< struct linha > linhas;
            stack< struct tupla > pilha_tupla;
            
            struct tupla tupla_atual;
            
            tupla_atual.x = 0.0;
            tupla_atual.y = 0.0;
            tupla_atual.ang = 90.0;
            
            string cadeia = gera_cadeia();

            for(int i = 0; i < cadeia.size(); i++) {
                switch(cadeia[i]) {
                    case 'F':
                        struct linha linha;
            
                        linha.x0 = tupla_atual.x;
                        linha.y0 = tupla_atual.y;

                        double cosx, sinx;
                        cosx = cos(tupla_atual.ang*M_PI/180.0);
                        sinx = sin(tupla_atual.ang*M_PI/180.0);

                        tupla_atual.x += distancia*cosx;
                        tupla_atual.y += distancia*sinx;

                        linha.x1 = tupla_atual.x;
                        linha.y1 = tupla_atual.y;
                        
                        linhas.push_back(linha);
                    break;

                    case '+':
                        tupla_atual.ang += angulo;
                    break;

                    case '-':
                        tupla_atual.ang -= angulo;
                    break;

                    case '[':
                        pilha_tupla.push(tupla_atual);
                    break;

                    case ']':
                        tupla_atual = pilha_tupla.top();
                        pilha_tupla.pop();
                    break;
                }
            }

            return linhas;
        }
};