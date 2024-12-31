#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "Jogador.hpp"
#define R 256

using namespace std;

int charAt(string S, int d)
{
    if (d < S.length())
    {
        return S.at(d);
    }
    return -1;
}

int digitoMaisSignificativo(int n)
{
    std::string str = std::to_string(n);
    return str[0] - '0';
}

void radix_sort(vector<shared_ptr<Jogador *>> &C, int modulo)
{
    vector<shared_ptr<Jogador *>> aux;
    aux.resize(C.size());
    vector<int> indices(10, 0);
    float posicao, haValor = 0;

    // Zera os indices
    fill(indices.begin(), indices.end(), 0);

    int tam_mais_longo = 0;

    // Passa contando cada casa (LSD)
    for (int i = 0; i < C.size(); i++)
    {

        int dado_ordenado = (*C[i])->sofifa_id;
        // int avaliacao_inteira = (int)((**C[i]).avaliacao_arredondada(7) * pow(10, 7));

        if (modulo == 10 && std::to_string(dado_ordenado).length() > tam_mais_longo)
        {
            tam_mais_longo = std::to_string(dado_ordenado).length();
        }

        posicao = (dado_ordenado % modulo) / (modulo / 10);
        // cout << (**C[i]).avaliacao_arredondada(7) * pow(10, 7) << " = ";
        // cout << posicao << endl;
        indices[posicao]++;
        haValor = haValor || posicao;
    }

    // Se nenhuma posicao teve valor, o modulo ultrapassou o maior valor
    if (!haValor)
    {
        return;
    }

    // Transforma em indice
    for (int i = 1; i < 10; i++)
    {
        indices[i] += indices[i - 1];
    }

    // Percorre o vetor das palavras, consulta o indices e coloca na posicao correta
    for (int i = C.size() - 1; i >= 0; i--)
    {
        // int avaliacao_inteira = (int)((**C[i]).avaliacao_arredondada(7) * pow(10, 7));
        aux[--indices[((*C[i])->sofifa_id % modulo) / (modulo / 10)]] = C[i];
    }

    for (int i = 0; i < C.size(); i++)
    {
        C[i] = aux[i];
    }

    if (std::to_string(modulo).length() - 1 <= tam_mais_longo)
        {

            radix_sort(C, modulo * 10);
        }

    return;
}

void radix_sort_msd(vector<string> &C, int piso, int teto, int n)
{
    if (teto <= piso)
    {
        return;
    }

    vector<int> conta(R + 2, 0);
    vector<string> aux(teto - piso + 1);

    // Preenchendo o vetor das letras com as frequencias
    for (int i = piso; i <= teto; i++)
    {
        conta[charAt(C[i], n) + 2]++;
    }

    // Transforma a contagem em indices
    for (int r = 0; r < R + 1; r++)
    {
        conta[r + 1] += conta[r];
    }

    // Distribui no auxiliar de acordo com os indices encontrados
    for (int i = piso; i <= teto; i++)
    {
        aux[conta[charAt(C[i], n) + 1]++] = C[i];
    }

    // Copia do aux para o original
    for (int i = piso; i <= teto; i++)
    {
        C[i] = aux[i - piso];
    }

    // Chama recursivamente para cada caracter
    for (int r = 0; r < R; r++)
    {
        radix_sort_msd(C, piso + conta[r], piso + conta[r + 1] - 1, n + 1);
    }
};
