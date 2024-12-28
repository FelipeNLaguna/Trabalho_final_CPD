#ifndef HASH_JOG_HPP
#define HASH_JOG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Jogador.hpp"

using namespace std;

Jogador *buscaHashJ(int sofifa_id, vector<pJogador *> jogadores)
{
    for (int i = 0; i < jogadores.size(); i++)
    {
        pJogador *jog_aux = jogadores[i];
        while (jog_aux != nullptr)
        {
            if (jog_aux->jogador.sofifa_id == sofifa_id)
                return &(jog_aux->jogador);
            jog_aux = jog_aux->next;
        }
    }
    return {nullptr};
}

Jogador *buscaHashJ2(int sofifa_id, const std::vector<Jogador *> &jogadores)
{
    int index = sofifa_id % jogadores.size();
    for (int i = 0; i < jogadores.size(); ++i)
    {
        int probe_index = (index + i * i) % jogadores.size();
        if (!jogadores[probe_index])
            return nullptr; // Slot vazio, jogador não encontrado
        if (jogadores[probe_index]->sofifa_id == sofifa_id)
            return jogadores[probe_index]; // Jogador encontrado
    }
    return nullptr; // Jogador não encontrado após tentar todos os índices
}

void percorreExecuta(vector<pJogador *> jogadores, void (*f)(Jogador))
{
    for (int i = 0; i < jogadores.size(); i++)
    {
        pJogador *jog_aux = jogadores[i];
        while (jog_aux != nullptr)
        {
            f(jog_aux->jogador);
            jog_aux = jog_aux->next;
        }
    }
}

void imprimeHashJ(vector<pJogador *> jogadores)
{
    for (int i = 0; i < jogadores.size(); i++)
    {
        pJogador *jog_aux = jogadores[i];
        while (jog_aux != nullptr)
        {
            std::cout << static_cast<std::string>(jog_aux->jogador) << std::endl;
            jog_aux = jog_aux->next;
        }
    }
}

void imprimeHashJ2(vector<Jogador *> jogadores)
{
    for (int i = 0; i < jogadores.size(); ++i)
    {
        if (jogadores[i])
        {
            std::cout << static_cast<std::string>(*jogadores[i]) << std::endl;
        }
        else
        {
            std::cout << i << ": \n";
        }
    }
}

int hashingJ(Jogador jogador, vector<pJogador *> &jogadores, int modulo)
{
    int index = jogador.sofifa_id % modulo;
    if (jogadores[index] == nullptr)
    {
        jogadores[index] = new pJogador(jogador);
    }
    else
    {
        pJogador *atual = jogadores[index];
        while (atual->next != nullptr)
        {
            atual = atual->next;
        }

        atual->next = new pJogador(jogador);
    }
    return 1;
}

int hashingJ2(Jogador *jogador, std::vector<Jogador *> &jogadores, int modulo)
{
    int index = jogador->sofifa_id % modulo;
    for (int i = 0; i < modulo; ++i)
    {
        int probe_index = (index + i * i) % modulo; // Quadratic probing
        if (!jogadores[probe_index])                // Encontra slot vazio
        {
            jogadores[probe_index] = jogador;
            return probe_index; // Retorna o índice onde foi inserido
        }
    }
    throw std::runtime_error("Tabela hash cheia!"); // Caso a tabela esteja cheia
}

#endif