#include <iostream>
#include <fstream> // Para std::ifstream
#include <chrono>
#include "uteis.hpp"
#define TAM_HASH 19001

void pesqPrefixos(std::vector<Jogador *> hash_jogadores, TrieST<int> trie, std::string nome)
{
    auto ids_jogadores_encontrados = trie.idsWithPrefix(nome);
    std::vector<Jogador *> jogadores_encontrados = buscaIdsHash(ids_jogadores_encontrados, hash_jogadores);

    ordenaJogadores(jogadores_encontrados);

    imprimir_jogadores(jogadores_encontrados);
}

void melhoresPosicao(int N, std::string posicao, std::vector<Jogador *> hash_jogadores)
{
    auto jogadores_filtrados_ordenados = ordenaPosicao(hash_jogadores, posicao, N);

    if (jogadores_filtrados_ordenados.size() == 0)
        return;
    imprimir_jogadores(jogadores_filtrados_ordenados);
}

void pergunta()
{
    std::cout << "Escolha a pesquisa que queres fazer (numero): " << std::endl
              << "Nao pesquisar (0)" << std::endl
              << "Pesquisa 1: Prefixos" << std::endl
              << "Pesquisa 3: Posicao" << std::endl;
}

int main()
{
    try
    {
        std::vector<Jogador *> hash_jogadores(TAM_HASH, nullptr);
        TrieST<int> trie;
        constroiHashETrie(hash_jogadores, trie);
        int pesquisa_escolhida;

        pergunta();
        std::cin >> pesquisa_escolhida;
        while (pesquisa_escolhida < 5 && pesquisa_escolhida > 0)
        {
            switch (pesquisa_escolhida)
            {
            case 1:
            {
                std::cout << "Digite o prefixo: " << std::endl;
                std::string prefixo;
                std::cin >> prefixo;
                pesqPrefixos(hash_jogadores, trie, prefixo);
                break;
            }

            case 3:
            {
                int n;
                std::string posicao;

                std::cout << "Digite o numero desejado de jogadores: ";
                std::cin >> n;

                std::cout << "\nQual a posicao desejada? ";
                std::cin >> posicao;
                melhoresPosicao(n, posicao, hash_jogadores);
            }

            default:
                break;
            }

            std::cout << "\n";
            pergunta();
            std::cin >> pesquisa_escolhida;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    // Este getchar eh so para que a janela nao feche automatico
    std::getchar();
    return 0;
}
