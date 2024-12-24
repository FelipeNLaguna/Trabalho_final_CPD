#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Jogador.hpp"

using namespace std;

Jogador buscaHash(int sofifa_id, vector<pJogador *> jogadores)
{
    for (int i = 0; i < jogadores.size(); i++)
    {
        pJogador *jog_aux = jogadores[i];
        while (jog_aux != nullptr)
        {
            if (jog_aux->jogador.sofifa_id == sofifa_id)
                return (jog_aux->jogador);
            jog_aux = jog_aux->next;
        }
    }
    return {99999, "NAO_ENCONTRADO", "NAO_ENCONTRADO", "NAO_ENCONTRADO", "NAO_ENCONTRADO"};
}

void imprimeHash(vector<pJogador *> jogadores)
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

int hashing(Jogador jogador, vector<pJogador *> &jogadores, int modulo)
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