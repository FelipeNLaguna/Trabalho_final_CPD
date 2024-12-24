<<<<<<< HEAD
<<<<<<< HEAD
#include <iostream>
#include <fstream> // Para std::ifstream
#include "parser.hpp" // Inclua o arquivo parser.hpp

int main() {
    try {
        // Abra o arquivo CSV usando std::ifstream
        std::ifstream file("example.csv");

        // Verifique se o arquivo foi aberto corretamente
        if (!file.is_open()) {
            throw std::runtime_error("Não foi possível abrir o arquivo CSV.");
        }

        // Inicialize o CsvParser com o arquivo
        aria::csv::CsvParser parser(file);

        // Itere sobre o conteúdo do CSV
        for (const auto& row : parser) {
            for (const auto& field : row) {
                std::cout << field << " "; // Imprime os campos do CSV
            }
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
=======
#include <iostream>
#include <fstream> // Para std::ifstream
#include "parser.hpp" // Inclua o arquivo parser.hpp

int main() {
    try {
        // Abra o arquivo CSV usando std::ifstream
        std::ifstream file("example.csv");

        // Verifique se o arquivo foi aberto corretamente
        if (!file.is_open()) {
            throw std::runtime_error("Não foi possível abrir o arquivo CSV.");
        }

        // Inicialize o CsvParser com o arquivo
        aria::csv::CsvParser parser(file);

        // Itere sobre o conteúdo do CSV
        for (const auto& row : parser) {
            for (const auto& field : row) {
                std::cout << field << " "; // Imprime os campos do CSV
            }
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
>>>>>>> b323af9c7cb8f5368ab7ff1fe765f1db2b1e8be2
=======
#include <iostream>
#include <fstream> // Para std::ifstream
#include "parser.hpp" // Inclua o arquivo parser.hpp

int main() {
    try {
        // Abra o arquivo CSV usando std::ifstream
        std::ifstream file("example.csv");

        // Verifique se o arquivo foi aberto corretamente
        if (!file.is_open()) {
            throw std::runtime_error("Não foi possível abrir o arquivo CSV.");
        }

        // Inicialize o CsvParser com o arquivo
        aria::csv::CsvParser parser(file);

        // Itere sobre o conteúdo do CSV
        for (const auto& row : parser) {
            for (const auto& field : row) {
                std::cout << field << " "; // Imprime os campos do CSV
            }
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
>>>>>>> b323af9c7cb8f5368ab7ff1fe765f1db2b1e8be2
