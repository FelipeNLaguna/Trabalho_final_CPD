#include <iostream>
#include <fstream> // Para std::ifstream
#include <chrono>
#include "parser.hpp" // Inclua o arquivo parser.hpp
#include "Jogador.hpp"
#include "hash_jog.hpp"
#include "TrieST.hpp"
#include "radix.cpp"
#define TAM_HASH 19001

template <typename Value>
void inverteVetor(std::vector<Value> &vetor)
{
    int tam_vetor = vetor.size();
    for (int i = 0; i < tam_vetor / 2; i++)
    {
        std::swap(vetor[i], vetor[tam_vetor - 1 - i]);
    }
}

void constroiHashETrie(vector<Jogador *> hash_jogadores, TrieST<Jogador *> &trie)
{
    // Abra o arquivo CSV usando std::ifstream
    std::ifstream players("players.csv");

    std::ifstream rating("rating.csv");

    // Verifique se o arquivo foi aberto corretamente
    if (!players.is_open())
    {
        throw std::runtime_error("Não foi possível abrir o arquivo CSV.");
    }

    aria::csv::CsvParser players_csv(players);
    aria::csv::CsvParser rating_csv(rating);

    // Itere sobre o conteúdo do CSV
    bool cabecalho = true;
    for (const auto &row : players_csv)
    {
        if (cabecalho)
        {
            cabecalho = false;
            continue;
        }
        Jogador *j = new Jogador(stoi(row[0]), row[1], row[2], row[3], row[4]);

        hashingJ(j, hash_jogadores, TAM_HASH);
        trie.put(j->short_name, j);
    }

    cabecalho = true;

    for (const auto &row : rating_csv)
    {
        if (cabecalho)
        {
            cabecalho = false;
            continue;
        }

        Jogador *jog_aux = (buscaHashJ(stoi(row[1]), hash_jogadores));
        if (jog_aux != nullptr)
            (*jog_aux).add_avaliacao(stof(row[2]));
    }

    players.close();
    rating.close();
}

int main()
{
    try
    {

        vector<Jogador *> hash_jogadores(TAM_HASH, nullptr);
        TrieST<Jogador *> trie;
        constroiHashETrie(hash_jogadores, trie);

        auto jogadores_encontrados = trie.idsWithPrefix("Lucas");

        radix_sort(jogadores_encontrados, 10);

        inverteVetor(jogadores_encontrados);

        for (int i = 0; i < jogadores_encontrados.size(); i++)
        {
            (**jogadores_encontrados[i]).imprimeJogador();
        }

        // imprimeHashJ(hash_jogadores);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
