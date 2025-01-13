#include "radix.hpp"

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


void radix_sort(vector<Jogador *> &C, int modulo, int tam_mais_longo)
{
    vector<Jogador *> aux;
    aux.resize(C.size());
    vector<int> indices(10, 0);
    float posicao, haValor = 0;

    // Zera os indices
    fill(indices.begin(), indices.end(), 0);

    // Passa contando cada casa (LSD)
    for (int i = 0; i < C.size(); i++)
    {

        // int dado_ordenado = (*C[i])->sofifa_id;
        int dado_ordenado = (int)((*C[i]).avaliacao_arredondada(7) * pow(10, 7));

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
        aux[--indices[((int)((*C[i]).avaliacao_arredondada(7) * pow(10, 7)) % modulo) / (modulo / 10)]] = C[i];
    }

    for (int i = 0; i < C.size(); i++)
    {
        C[i] = aux[i];
    }

    int tam = std::to_string(modulo).length();
    if (tam <= tam_mais_longo)
    {
        radix_sort(C, modulo * 10, tam_mais_longo);
    }

    return;
}

void radix_sort_msd(vector<string> &C, int piso, int teto, int n)
{
    if (teto <= piso)
    {
        return;
    }

    vector<int> conta(A + 2, 0);
    vector<string> aux(teto - piso + 1);

    // Preenchendo o vetor das letras com as frequencias
    for (int i = piso; i <= teto; i++)
    {
        conta[charAt(C[i], n) + 2]++;
    }

    // Transforma a contagem em indices
    for (int r = 0; r < A + 1; r++)
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
    for (int r = 0; r < A; r++)
    {
        radix_sort_msd(C, piso + conta[r], piso + conta[r + 1] - 1, n + 1);
    }
};
// Função para extrair o valor do critério principal (nota arredondada para 7 casas decimais)
int getNotaKey(const Jogador_nota& jogador_nota) {
    return static_cast<int>(std::ceil(jogador_nota.nota * std::pow(10, 7)));
}

int getRatingKey(const Jogador_nota& jogador_nota) {
    // Calcula o rating global arredondado para 7 casas decimais
    return static_cast<int>((jogador_nota.jog->avaliacao_arredondada(7)) * std::pow(10, 7));
}

void radix_sort_jogadores(std::vector<Jogador_nota>& jogadores, bool ordenarPorNota) {
    const int RADIX = 10; // Base decimal
    int maxValue = 0;

    // Determina qual chave será usada (nota ou rating arredondado)
    auto getKey = ordenarPorNota ? getNotaKey : getRatingKey;

    // Encontra o maior valor da chave para calcular o número de dígitos
    for (const auto& jogador_nota : jogadores) {
        maxValue = std::max(maxValue, getKey(jogador_nota));
    }

    int exp = 1; // Começa pelo dígito menos significativo (LSD)

    // Vetores auxiliares
    std::vector<Jogador_nota> aux(jogadores.size());
    std::vector<int> count(RADIX);

    while (maxValue / exp > 0) {
        // Zera o vetor de contagem
        std::fill(count.begin(), count.end(), 0);

        // Conta a frequência de cada dígito na posição atual
        for (const auto& jogador_nota : jogadores) {
            int digit = (getKey(jogador_nota) / exp) % RADIX;
            count[digit]++;
        }

        // Acumula os índices de trás para frente (ordem decrescente)
        for (int i = RADIX - 2; i >= 0; i--) {
            count[i] += count[i + 1];
        }

        // Distribui os elementos no vetor auxiliar em ordem decrescente
        for (int i = jogadores.size() - 1; i >= 0; i--) {
            int digit = (getKey(jogadores[i]) / exp) % RADIX;
            aux[--count[digit]] = jogadores[i];
        }

        // Copia o vetor auxiliar de volta para o vetor original
        jogadores = aux;

        // Passa para o próximo dígito mais significativo
        exp *= RADIX;
    }
}
