#include <iostream>
#include <sstream>
#include <string.h>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cctype>
#include "Jogador.hpp"

bool Jogador::temPosicao(std::string posicao_procurada)
{
    std::stringstream ss(player_position);
    std::string item;

    while (std::getline(ss, item, ','))
    {
        // Remover espaços antes e depois da posição
        item.erase(item.begin(), std::find_if(item.begin(), item.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        item.erase(std::find_if(item.rbegin(), item.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), item.end());

        if (item == posicao_procurada)
        {
            return true;
        }
    }
    return false;
}

void Jogador::imprimeJogador()
{
    float rating_arredondado = avaliacao_arredondada(7);
    std::cout << std::to_string(sofifa_id) + " " + short_name + " " + long_name + " " + player_position + " " + nationality + " " + std::to_string(rating_arredondado) + " " + std::to_string(count) << std::endl;
}

double Jogador::avaliacao_arredondada(int casas)
{
    const double multiplier = std::pow(10.0, casas);
    if (count == 0)
        return 0;
    return std::ceil(rating / count * multiplier) / multiplier;
}

Jogador::operator std::string()
{
    float rating_arredondado = avaliacao_arredondada(7);
    return std::to_string(sofifa_id) + " " + short_name + " " + long_name + " " + player_position + " " + nationality + " " + std::to_string(rating_arredondado) + " " + std::to_string(count);
}

void Jogador::add_avaliacao(float avaliacao)
{
    count++;
    rating += avaliacao;
}

std::string Jogador::atributoNumerado(int n)
{
    switch (n)
    {
    case 0:
        return std::to_string(sofifa_id);
        break;
    case 1:
        return short_name;
        break;
    case 2:
        return long_name;
        break;
    case 3:
        return player_position;
        break;
    case 4:
        return nationality;
        break;
    case 5:
    {
        float rating_arredondado = avaliacao_arredondada(7);
        return std::to_string(rating_arredondado);
        break;
    }
    case 6:
        return std::to_string(count);
        break;
    }
}

void imprimir_jogadores(const std::vector<Jogador *> &tabela)
{
    if (tabela.size() == 0)
        return;
    std::vector<std::string> cabecalhos = {"sofifa_id", "short_name", "long_name", "player_positions", "nationality", "rating", "count"};
    // Calcular a largura de cada coluna
    std::vector<size_t> larguras_colunas;
    for (const auto &linha : tabela)
    {
        for (size_t coluna = 0; coluna < 7; ++coluna)
        {
            if (coluna >= larguras_colunas.size())
                larguras_colunas.push_back(0);
            larguras_colunas[coluna] = std::max(std::max(larguras_colunas[coluna], linha->atributoNumerado(coluna).size()), cabecalhos[coluna].size());
        }
    }

    // Imprimir separador horizontal
    auto imprimir_separador = [&larguras_colunas]()
    {
        std::cout << "+";
        for (size_t largura : larguras_colunas)
            std::cout << std::string(largura + 2, '-') << "+";
        std::cout << "\n";
    };

    // Imprimir linhas
    imprimir_separador();
    // Imprimir cabecalho
    for (int c = 0; c < 7; c++)
    {
        std::cout << "| " << std::setw(larguras_colunas[c]) << std::left << cabecalhos[c] << " ";
    }
    std::cout << "|\n";
    imprimir_separador();

    for (size_t i = 0; i < tabela.size(); ++i)
    {
        for (size_t coluna = 0; coluna < 7; ++coluna)
        {
            std::cout << "| " << std::setw(larguras_colunas[coluna]) << std::left << (*tabela[i]).atributoNumerado(coluna) << " ";
        }
        std::cout << "|\n";
    }
    imprimir_separador();
}