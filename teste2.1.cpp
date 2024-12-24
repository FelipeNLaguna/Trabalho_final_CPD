#include <iostream>
#include <fstream> // Para std::ifstream
#include "parser.hpp" // Inclua o arquivo parser.hpp
#include "Jogador.hpp"
#include "hash.hpp"
#define TAM_HASH 10000

int main() {
    try {
        vector<pJogador*> hash_jogadores(TAM_HASH, nullptr);
        
        // Abra o arquivo CSV usando std::ifstream
        std::ifstream file("players.csv");

        // Verifique se o arquivo foi aberto corretamente
        if (!file.is_open()) {
            throw std::runtime_error("Não foi possível abrir o arquivo CSV.");
        }

        // Inicialize o CsvParser com o arquivo
        aria::csv::CsvParser parser(file);
                
        bool cabecalho = true;
        // Itere sobre o conteúdo do CSV
        for (const auto& row : parser) {
            if(cabecalho){
                cabecalho = false;
                continue;
            }
            Jogador *j = new Jogador(stoi(row[0]), row[1], row[2], row[3], row[4]);
            // std::shared_ptr<Jogador> j = std::make_shared<Jogador>(stoi(row[0]), row[1], row[2], row[3], row[4]);
            hashing(*j, hash_jogadores, TAM_HASH);
            
            // std::cout << row[0] << " "; // Imprime os campos do CSV
            std::cout << std::endl;
        }
        Jogador jaux = buscaHash(258003, hash_jogadores);
        std::cout << static_cast<std::string>(jaux) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
