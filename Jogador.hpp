#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <iostream>
#include <string.h>
#include <cmath>

class Jogador
{
private:
    double avalicao_arredondada(int casas)
    {
        const double multiplier = std::pow(10.0, casas);
        return std::ceil(rating / count * multiplier) / multiplier;
    }

public:
    int sofifa_id;
    std::string short_name;
    std::string long_name;
    std::string player_position;
    std::string nationality;
    int count;
    float rating;

    explicit operator std::string()
    {
        return std::to_string(sofifa_id) + " " + short_name + " " + long_name + " " + player_position + " " + nationality + " " + std::to_string(avalicao_arredondada(6)) + " " + std::to_string(count);
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