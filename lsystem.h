#include <string.h>
#include <stack>
#include <cmath> 

using namespace std;

struct tupla {
    double x;
    double y;
    double z;

    double angA;
    double angB;
};

struct linha {
    double x0;
    double y0;
    double z0;

    double x1;
    double y1;
    double z1;
};

class LSystem {
    private:
        int iteracoes;
        double distancia;
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

            // Tupla inicial
            tupla_atual.x = 0.0;
            tupla_atual.y = 0.0;
            tupla_atual.z = 1.0;

            tupla_atual.angB = 90.0;
            tupla_atual.angA = 90.0;
            
            string cadeia = gera_cadeia();

            for(int i = 0; i < cadeia.size(); i++) {
                switch(cadeia[i]) {
                    case 'F':
                        //cout << tupla_atual.angA*(M_PI/180) << ' ' << tupla_atual.angB*(M_PI/180) << '\n';

                        struct linha linha;
            
                        linha.x0 = tupla_atual.x;
                        linha.y0 = tupla_atual.y;
                        linha.z0 = tupla_atual.z;

                        double cosa, sina, cosb, sinb;
                        
                        cosa = cos(tupla_atual.angA*(M_PI/180.0));
                        sina = sin(tupla_atual.angA*(M_PI/180.0));

                        cosb = cos(tupla_atual.angB*(M_PI/180.0));
                        sinb = sin(tupla_atual.angB*(M_PI/180.0));

                        if(tupla_atual.angA == 90)
                            cosa = 0;
                        if(tupla_atual.angB == 90)
                            cosb = 0;

                        tupla_atual.x += distancia*sinb*cosa;
                        tupla_atual.y += distancia*sinb*sina;
                        tupla_atual.z += distancia*cosb;

                        linha.x1 = tupla_atual.x;
                        linha.y1 = tupla_atual.y;
                        linha.z1 = tupla_atual.z;

                        cout << linha.x0 << ' ' << linha.y0 << ' ' << linha.z0 << '\n';
                        cout << linha.x1 << ' ' << linha.y1 << ' ' << linha.z1 << '\n';

                        cout << '\n';
                        
                        linhas.push_back(linha);
                    break;

                    case '+':
                        tupla_atual.angA += angulo;
                    break;

                    case '-':
                        tupla_atual.angA -= angulo;
                    break;

                    case '>':
                        tupla_atual.angB += angulo;
                    break;

                    case '<':
                        tupla_atual.angB -= angulo;
                    break;

                    case '[':
                        pilha_tupla.push(tupla_atual);
                    break;

                    case ']':
                        tupla_atual = pilha_tupla.top();
                        pilha_tupla.pop();
                    break;

                    default:
                    break;
                }
            }

            return linhas;
        }
};