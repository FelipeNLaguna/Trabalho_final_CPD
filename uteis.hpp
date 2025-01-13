#include "TrieST.hpp"
#include "Jogador.hpp"
#define TAM_HASH 19001

template <typename Value>
void inverteVetor(std::vector<Value> &vetor);

void constroiHashETrie(std::vector<Jogador *> &hash_jogadores, TrieST<int> &trie);

std::vector<Jogador *> buscaIdsHash(std::vector<int> ids_jogadores, std::vector<Jogador *> hash);

void ordenaJogadores(std::vector<Jogador *> &jogadores);

std::vector<Jogador *> filtroPosicao(std::vector<Jogador *> &hash, std::string posicao);

std::vector<Jogador *> ordenaPosicao(std::vector<Jogador *> hash, std::string posicao, int qtd);