#ifndef RADIX_HPP
#define RADIX_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "Jogador.hpp"
#define A 256

using namespace std;

int charAt(string S, int d);

int digitoMaisSignificativo(int n);

void radix_sort(vector<Jogador *> &C, int modulo, int tam_mais_longo = 0);

void radix_sort_msd(vector<string> &C, int piso, int teto, int n);

int getNotaKey(const Jogador_nota& jogador_nota);

int getRatingKey(const Jogador_nota& jogador_nota);

void radix_sort_jogadores(std::vector<Jogador_nota>& jogadores, bool ordenarPorNota);

#endif
