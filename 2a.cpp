#include <iostream>
#include <fstream>    // Para std::ifstream
#include "parser.hpp" // Inclua o arquivo parser.hpp
#include "Jogador.hpp"
#include "hash.hpp"
#include "TrieST.hpp"
#define TAM_HASH 10000

int main()
{
    try
    {
        vector<pJogador *> hash_jogadores(TAM_HASH, nullptr);

        // Abra o arquivo CSV usando std::ifstream
        std::ifstream file("players.csv");

        // Verifique se o arquivo foi aberto corretamente
        if (!file.is_open())
        {
            throw std::runtime_error("Não foi possível abrir o arquivo CSV.");
        }

        aria::csv::CsvParser parser(file);

        TrieST<Jogador> trie;

        bool cabecalho = true;
        // Itere sobre o conteúdo do CSV
        for (const auto &row : parser)
        {
            if (cabecalho)
            {
                cabecalho = false;
                continue;
            }
            Jogador *j = new Jogador(stoi(row[0]), row[1], row[2], row[3], row[4]);
            hashing(*j, hash_jogadores, TAM_HASH);
            trie.put(j->short_name, *j);
        }

        std::vector<std::string> allKeys = trie.keys();
        std::cout << "Chaves armazenadas na Trie:" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
