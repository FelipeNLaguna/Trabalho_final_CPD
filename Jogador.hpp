#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>

// Definição da struct para jogador e nota (vem antes da classe Jogador)
struct Jogador_nota {
    class Jogador* jog; // Declarar como classe para resolver dependência
    float nota;
};

// Declaração da classe Jogador
class Jogador {
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

    Jogador(int s, std::string sn, std::string ln, std::string pp, std::string n)
        : sofifa_id(s), short_name(sn), long_name(ln), player_position(pp), nationality(n) {}

    std::string atributoNumerado(int n);
};

// Função para imprimir jogadores formatados
void imprimir_jogadores(const std::vector<Jogador*>& tabela);
void imprime_users(const std::vector<Jogador_nota>& tabela);

#endif
