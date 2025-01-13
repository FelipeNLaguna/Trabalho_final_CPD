#include <iostream>
#include <vector>
#include <iomanip>

void imprimir_tabela(const std::vector<std::vector<std::string>> &tabela) {
    // Calcular a largura de cada coluna
    std::vector<size_t> larguras_colunas;
    for (const auto &linha : tabela) {
        for (size_t coluna = 0; coluna < linha.size(); ++coluna) {
            if (coluna >= larguras_colunas.size()) larguras_colunas.push_back(0);
            larguras_colunas[coluna] = std::max(larguras_colunas[coluna], linha[coluna].size());
        }
    }

    // Imprimir separador horizontal
    auto imprimir_separador = [&larguras_colunas]() {
        std::cout << "+";
        for (size_t largura : larguras_colunas)
            std::cout << std::string(largura + 2, '-') << "+";
        std::cout << "\n";
    };

    // Imprimir linhas
    imprimir_separador();
    for (size_t i = 0; i < tabela.size(); ++i) {
        for (size_t coluna = 0; coluna < tabela[i].size(); ++coluna) {
            std::cout << "| " << std::setw(larguras_colunas[coluna]) << std::left << tabela[i][coluna] << " ";
        }
        std::cout << "|\n";
        if (i == 0) imprimir_separador(); // Separar cabeçalhos das linhas
    }
    imprimir_separador();
}

int main() {
    std::vector<std::vector<std::string>> tabela = {
        {"Nome", "Idade", "País"},
        {"Alice", "30", "EUA"},
        {"Bob", "25", "Reino Testnado uma palavra extermemente grant3e"},
        {"Carlos", "28", "Canadá"},
    };

    imprimir_tabela(tabela);

    return 0;
}
