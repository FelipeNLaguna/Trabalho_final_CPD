#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <iostream>
#include <sstream>
#include <string.h>
#include <cmath>
#include <iomanip>

class Jogador
{
public:
    bool temPosicao(std::string posicao_procurada);

    void imprimeJogador();

    double avaliacao_arredondada(int casas);

    int sofifa_id;
    std::string short_name;
    std::string long_name;
    std::string player_position;
    std::string nationality;
    int count = 0;
    float rating = 0;

    explicit operator std::string();

    void add_avaliacao(float avaliacao);

    Jogador(int s, std::string sn, std::string ln, std::string pp, std::string n) : sofifa_id(s), short_name(sn), long_name(ln), player_position(pp), nationality(n) {}

    std::string atributoNumerado(int n);
};

void imprimir_jogadores(const std::vector<Jogador *> &tabela);

struct pJogador
{
    Jogador jogador;
    pJogador *next;
    pJogador(Jogador j) : jogador(j), next(nullptr) {}
};
//struct para a 3.2 com jogador e nota como parametros
struct Jogador_nota{
    Jogador* jog;
    float nota;
};

#endif
