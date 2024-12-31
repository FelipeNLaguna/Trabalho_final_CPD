#include <iostream>
#include <fstream> // Para std::ifstream
#include <chrono>
#include "parser.hpp" // Inclua o arquivo parser.hpp
#include "Jogador.hpp"
#include "hash_jog.hpp"
#include "hash_user.hpp"
#include "TrieST.hpp"
#define TAM_HASH 19001

int main()
{
    try
    {

        // for (int i = 0; i < TAM_HASH * 10; i += 1000)
        // {
        vector<Jogador *> hash_jogadores(TAM_HASH, nullptr);

        // Abra o arquivo CSV usando std::ifstream
        std::ifstream players("players.csv");

        std::ifstream rating("rating.csv");

        std::ifstream tags("tags.csv");

        // Verifique se o arquivo foi aberto corretamente
        if (!players.is_open())
        {
            throw std::runtime_error("Não foi possível abrir o arquivo CSV.");
        }

        aria::csv::CsvParser players_csv(players);
        aria::csv::CsvParser rating_csv(rating);
        aria::csv::CsvParser tags_csv(tags);

        TrieST<Jogador> trie;
        TrieST_tags trie_tags;

        bool cabecalho = true;
        // Itere sobre o conteúdo do CSV

        auto inicio = chrono::high_resolution_clock::now();

        for (const auto &row : players_csv)
        {
            if (cabecalho)
            {
                cabecalho = false;
                continue;
            }
            Jogador *j = new Jogador(stoi(row[0]), row[1], row[2], row[3], row[4]);
            // hashingJ(*j, hash_jogadores, TAM_HASH);
            hashingJ(j, hash_jogadores, TAM_HASH);
            trie.put(j->short_name, *j);
        }

        cabecalho = true;

        for (const auto &row : rating_csv)
        {
            if (cabecalho)
            {
                cabecalho = false;
                continue;
            }

            // Jogador *jog_aux = (buscaHashJ(stoi(row[1]), hash_jogadores));
            Jogador *jog_aux = (buscaHashJ(stoi(row[1]), hash_jogadores));
            if (jog_aux != nullptr)
                (*jog_aux).add_avaliacao(stof(row[2]));
        }

        cabecalho = true;

        // cria a arvore de tags
        for (const auto &row : tags_csv)
        {
            if (cabecalho)
            {
                cabecalho = false;
                continue;
            }
            // row[2] pq é onde esta contido as tags e row[1] os id_jogadores
            trie_tags.put(row[2], std::stoi(row[1]));
        }

        Hash_user *hash = monta_hash();

        // busca de teste
        int id_user = 123; // ID do usuário a ser buscado
        User *user = busca_user(*hash, id_user);
        if (user != nullptr)
        {
            std::cout << "Usuário encontrado: " << user->id_user << std::endl;
        }
        else
        {
            std::cout << "Usuário não encontrado" << std::endl;
        }

        auto fim = chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duracao = fim - inicio;

        std::cout << "t = " << TAM_HASH << " " << duracao.count() << std::endl;

        // imprimeHashJ(hash_jogadores);
        // imprimeHashJ2(hash_jogadores);

        players.close();
        rating.close();

        aria::csv::CsvParser players_csv(players);
        aria::csv::CsvParser rating_csv(rating);

        TrieST<Jogador *> trie;

        bool cabecalho = true;
        // Itere sobre o conteúdo do CSV

        auto inicio = chrono::high_resolution_clock::now();

        for (const auto &row : players_csv)
        {
            if (cabecalho)
            {
                cabecalho = false;
                continue;
            }
            Jogador *j = new Jogador(stoi(row[0]), row[1], row[2], row[3], row[4]);
            // hashingJ(*j, hash_jogadores, TAM_HASH);
            hashingJ(j, hash_jogadores, TAM_HASH);
            trie.put(j->short_name, *j);
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

        std::vector<std::shared_ptr<Jogador *>> jogadores_encontrados = trie.idsWithPrefix("L. Messi");

        for (int i = 0; i < jogadores_encontrados.size(); i++)
        {
            std::cout << static_cast<std::string>(**jogadores_encontrados[i]) << std::endl;
        }

        // imprimeHashJ(hash_jogadores);

        players.close();
        rating.close();
    }
    // }
    catch (const std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}