#include <iostream>
#include <sstream>
#include <string.h>
#include <cmath>
#include <iomanip>
#include <vector>
#include "Jogador.hpp"

bool Jogador::temPosicao(std::string posicao_procurada)
{
    std::stringstream ss(player_position);
    std::string item;

    while (std::getline(ss, item, ','))
    {
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

void imprime_users(const std::vector<Jogador_nota>& tabela) {
    if (tabela.empty()) {
        std::cout << "Nenhum jogador encontrado.\n";
        return;
    }

    // Definição dos cabeçalhos
    std::vector<std::string> cabecalhos = {"ID", "Short Name", "Long Name", "Rating Global", "Count", "Nota"};
    std::vector<size_t> larguras_colunas(cabecalhos.size(), 0);

    // Calcular larguras das colunas
    for (auto& jogador_nota : tabela) {
        Jogador* jogador = jogador_nota.jog;
        float nota = jogador_nota.nota;

        larguras_colunas[0] = std::max(larguras_colunas[0], std::to_string(jogador->sofifa_id).size());
        larguras_colunas[1] = std::max(larguras_colunas[1], jogador->short_name.size());
        larguras_colunas[2] = std::max(larguras_colunas[2], jogador->long_name.size());
        larguras_colunas[3] = std::max(larguras_colunas[3], std::to_string(jogador->avaliacao_arredondada(7)).size());
        larguras_colunas[4] = std::max(larguras_colunas[4], std::to_string(jogador->count).size());
        larguras_colunas[5] = std::max(larguras_colunas[5], std::to_string(nota).size());
    }

    // Ajustar larguras para os cabeçalhos
    for (size_t i = 0; i < cabecalhos.size(); ++i) {
        larguras_colunas[i] = std::max(larguras_colunas[i], cabecalhos[i].size());
    }

    // Função auxiliar para imprimir separador
    auto imprimir_separador = [&larguras_colunas]() {
        std::cout << "+";
        for (size_t largura : larguras_colunas) {
            std::cout << std::string(largura + 2, '-') << "+";
        }
        std::cout << "\n";
    };

    // Imprimir tabela
    imprimir_separador();

    // Imprimir cabeçalhos
    std::cout << "|";
    for (size_t i = 0; i < cabecalhos.size(); ++i) {
        std::cout << " " << std::setw(larguras_colunas[i]) << std::left << cabecalhos[i] << " |";
    }
    std::cout << "\n";

    imprimir_separador();

    // Imprimir dados dos jogadores
    for (auto& jogador_nota : tabela) {
        Jogador* jogador = jogador_nota.jog;
        float nota = jogador_nota.nota;

        std::cout << "| " << std::setw(larguras_colunas[0]) << std::left << jogador->sofifa_id << " ";
        std::cout << "| " << std::setw(larguras_colunas[1]) << std::left << jogador->short_name << " ";
        std::cout << "| " << std::setw(larguras_colunas[2]) << std::left << jogador->long_name << " ";
        std::cout << "| " << std::setw(larguras_colunas[3]) << std::left << jogador->avaliacao_arredondada(7) << " ";
        std::cout << "| " << std::setw(larguras_colunas[4]) << std::left << jogador->count << " ";
        std::cout << "| " << std::setw(larguras_colunas[5]) << std::left << nota << " |\n";
    }

    imprimir_separador();
}