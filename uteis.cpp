#include <fstream> // Para std::ifstream
#include "parser.hpp"
#include "hash_jog.hpp" // Inclua o arquivo parser.hpp
#include "radix.hpp"
#include "uteis.hpp"

template <typename Value>
void inverteVetor(std::vector<Value> &vetor)
{
    int tam_vetor = vetor.size();
    for (int i = 0; i < tam_vetor / 2; i++)
    {
        std::swap(vetor[i], vetor[tam_vetor - 1 - i]);
    }
}

void constroiHashETrie(std::vector<Jogador *> &hash_jogadores, TrieST<int> &trie)
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

        trie.put(j->short_name, stoi(row[0]));
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

std::vector<Jogador *> buscaIdsHash(std::vector<int> ids_jogadores, std::vector<Jogador *> hash)
{

    std::vector<Jogador *> jogadores_encontrados;
    for (const int id : ids_jogadores)
    {
        Jogador *jogador = buscaHashJ(id, hash);
        jogadores_encontrados.push_back(jogador);
    }
    return jogadores_encontrados;
}

void ordenaJogadores(std::vector<Jogador *> &jogadores)
{
    radix_sort(jogadores, 10);

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

    if (jogadores_filtrados.size() == 0)
        return {};

    radix_sort(jogadores_filtrados, 10);

    inverteVetor(jogadores_filtrados);

    std::vector<Jogador *> jogadores_ordenados;

    for (int i = 0; i < qtd; i++)
    {
        jogadores_ordenados.push_back(jogadores_filtrados[i]);
    }



    return jogadores_ordenados;
}