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

void constroiHashETrie(vector<Jogador *> &hash_jogadores, TrieST<Jogador *> &trie)
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

void ordenaJogadores(std::vector<std::shared_ptr<Jogador *>> &jogadores)
{
    radix_sort_shared(jogadores, 10);

    inverteVetor(jogadores);
}

std::vector<Jogador *> filtroPosicao(vector<Jogador *> &hash, std::string posicao)
{
    std::vector<Jogador *> jogadores_filtrados;

    for (int i = 0; i < hash.size(); i++)
    {
        if (hash[i] == nullptr)
            continue;
        Jogador *jog_aux = hash[i];

        int conta = jog_aux->count;
        if (jog_aux->count >= 1000 && jog_aux->temPosicao(posicao))
        {
            jogadores_filtrados.push_back(jog_aux);
        }
    }

    return jogadores_filtrados;
}

std::vector<Jogador *> ordenaPosicao(vector<Jogador *> hash, std::string posicao, int qtd)
{
    auto jogadores_filtrados = filtroPosicao(hash, posicao);

    radix_sort(jogadores_filtrados, 10);

    inverteVetor(jogadores_filtrados);

    std::vector<Jogador *> jogadores_ordenados;

    for (int i = 0; i < qtd; i++)
    {
        jogadores_ordenados.push_back(jogadores_filtrados[i]);
    }

    return jogadores_ordenados;
}

int main()
{
    try
    {
        vector<Jogador *> hash_jogadores(TAM_HASH, nullptr);
        TrieST<Jogador *> trie;
        constroiHashETrie(hash_jogadores, trie);

        auto jogadores_encontrados = trie.ids();

        ordenaJogadores(jogadores_encontrados);

        int qtd = 20;
        std::string posicao = "RWB";

        auto jogadores_filtrados_ordenados = ordenaPosicao(hash_jogadores, posicao, qtd);

        for (int i = 0; i < jogadores_filtrados_ordenados.size(); i++)
        {
            int tam = jogadores_filtrados_ordenados.size();

            (*jogadores_filtrados_ordenados[i]).imprimeJogador();
        }

        // imprimeHashJ(hash_jogadores);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
