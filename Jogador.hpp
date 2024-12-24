#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <iostream>
#include <string.h>

class Jogador
{
public:
    int sofifa_id;
    std::string short_name;
    std::string long_name;
    std::string player_position;
    std::string nationality;

    explicit operator std::string() const
    {
        return std::to_string(sofifa_id) + " " + short_name + " " + long_name + " " + player_position + " " + nationality;
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