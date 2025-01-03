#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <iostream>
#include <sstream>
#include <string.h>
#include <cmath>

class Jogador
{
public:
    bool temPosicao(std::string posicao_procurada) {
    std::stringstream ss(player_position);
    std::string item;
    
    while (std::getline(ss, item, ',')) {
        if(item == posicao_procurada){
            return true;
        }
    }
    return false;
}

    void imprimeJogador()
    {
        float rating_arredondado = avaliacao_arredondada(7);
        std::cout << std::to_string(sofifa_id) + " " + short_name + " " + long_name + " " + player_position + " " + nationality + " " + std::to_string(rating_arredondado) + " " + std::to_string(count) << std::endl;
    }
    
    double avaliacao_arredondada(int casas)
    {
        const double multiplier = std::pow(10.0, casas);
        if (count == 0)
            return 0;
        return std::ceil(rating / count * multiplier) / multiplier;
    }

    int sofifa_id;
    std::string short_name;
    std::string long_name;
    std::string player_position;
    std::string nationality;
    int count = 0;
    float rating = 0;

    explicit operator std::string()
    {
        float rating_arredondado = avaliacao_arredondada(7);
        return std::to_string(sofifa_id) + " " + short_name + " " + long_name + " " + player_position + " " + nationality + " " + std::to_string(rating_arredondado) + " " + std::to_string(count);
    }

    void add_avaliacao(float avaliacao)
    {
        count++;
        rating += avaliacao;
    }

    Jogador(int s, std::string sn, std::string ln, std::string pp, std::string n) : sofifa_id(s), short_name(sn), long_name(ln), player_position(pp), nationality(n) {}
};

struct pJogador
{
    Jogador jogador;
    pJogador *next;
    pJogador(Jogador j) : jogador(j), next(nullptr) {}
};

#endif