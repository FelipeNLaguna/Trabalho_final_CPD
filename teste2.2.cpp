#include <iostream>
#include <fstream>    // Para std::ifstream
#include "parser.hpp" // Inclua o arquivo parser.hpp
#include "TrieST.hpp"
#include "Jogador.hpp"

int main()
{
    try
    {
        // Abra o arquivo CSV usando std::ifstream
        std::ifstream file("players.csv");

        // Verifique se o arquivo foi aberto corretamente
        if (!file.is_open())
        {
            throw std::runtime_error("Não foi possível abrir o arquivo CSV.");
        }

        // Inicialize o CsvParser com o arquivo
        aria::csv::CsvParser parser(file);

        TrieST<Jogador> trie;

        bool cabecalho = true;
        
        int i = 0;

        // Itere sobre o conteúdo do CSV
        for (const auto &row : parser)
        {
            if (cabecalho)
            {
                cabecalho = false;
                continue;
            }
            Jogador *j = new Jogador(stoi(row[0]), row[1], row[2], row[3], row[4]);
            trie.put(j->short_name, *j);

            if(i > 5) break;
            i++;
        }

        std::vector<std::string> allKeys = trie.keys();
        std::cout << "Chaves armazenadas na Trie:" << std::endl;
        for (const auto &key : allKeys)
        {
            std::cout << static_cast<std::string>(key) << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
