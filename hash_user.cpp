#include "hash_user.hpp"
#include "parser.hpp"
#include<fstream>
#include<iostream>
#include<algorithm>
#include <chrono>
#include <unordered_map>
#include <omp.h>
#define TAM_HASH 9473
// tem que ser testado
std::vector<User> le_users(const std::string nome_arq) {
    std::unordered_map<int, User> usuarios_map;
    std::ifstream file(nome_arq);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo" << std::endl;
        return {};
    }

    int id_player;
    int id_user;
    float rate;

    aria::csv::CsvParser parser(file);
    bool first_line = true;
    for (const auto& row : parser) {
        try {
            if (first_line) {
                first_line = false;
                continue; // Ignora a primeira linha (cabeçalhos)
            }

            id_user = std::stoi(row[0]);
            id_player = std::stoi(row[1]);
            rate = std::stof(row[2]); // Transformando string em double

            // Verifica se o usuário já existe no mapa
            auto it = usuarios_map.find(id_user);
            if (it != usuarios_map.end()) {
                // Usuário já existe, adiciona id_player e rate aos vetores correspondentes
                it->second.id_player.push_back(id_player);
                it->second.notas.push_back(rate);
            } else {
                // Usuário não existe, cria um novo User e adiciona ao mapa
                User new_user;
                new_user.id_user = id_user;
                new_user.id_player.push_back(id_player);
                new_user.notas.push_back(rate);
                usuarios_map[id_user] = new_user;
            }

        } catch (const std::exception& e) {
            std::cerr << "Erro ao processar linha: " << e.what() << std::endl;
            for (const auto& field : row) {
                std::cerr << field << " ";
            }
            std::cerr << std::endl;
        }
    }

    // Converte o mapa para um vetor
    std::vector<User> usuarios;
    for (const auto& pair : usuarios_map) {
        usuarios.push_back(pair.second);
    }

    return usuarios;
}
// feito
int fun_hash(int id_user,int size){
    return id_user % size;
}
void insere_user(Hash_user& hash, const User& user) {
    int indice_hash = fun_hash(user.id_user, hash.size);
    // se nao tiver colisao adiciona user
    if (hash.table[indice_hash].empty()) {
        hash.table[indice_hash].push_back(user); // push_back pq é uma lista
    } else {
        bool user_exists = false;
        for (auto& existing_user : hash.table[indice_hash]) {
            // testa se o user ja foi colocada na hash
            if (existing_user.id_user == user.id_user) {
                // na teoria só o primeiro id_user adicionado vai possuir mais de um elemento
                // no vetor id_player
                existing_user.id_player.insert(existing_user.id_player.end(), user.id_player.begin(), user.id_player.end());
                existing_user.notas.insert(existing_user.notas.end(), user.notas.begin(), user.notas.end());
                user_exists = true;
                break;
            }
        }
        if (!user_exists) {
            hash.table[indice_hash].push_back(user);
        }
    }
}

User* busca_user(Hash_user& hash , int id_user){
    int indice_hash = fun_hash(id_user, hash.size);
    
    // Percorre a lista na posição do índice de hash
    for (auto& user : hash.table[indice_hash]) {
        if (user.id_user == id_user) {
            return &user; // Retorna um ponteiro para o usuário encontrado
        }
    }
    
    return nullptr; // Retorna nullptr se o usuário não for encontrado 
    // na pesquisa testa se o resultado é nullptr se for retorna a string "Nao encontrado"
}

Hash_user* monta_hash() {
    Hash_user* hash_users = new Hash_user(TAM_HASH);
    std::vector<User> usuarios = le_users("rating.csv");

    for (const User& user : usuarios) {
        insere_user(*hash_users, user);
    }

    return hash_users;
}

/*
int main() {
    auto inicio = std::chrono::high_resolution_clock::now();
    Hash_user* hash = monta_hash();

    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracao = fim - inicio;

    std::cout << "Tempo para montar a hash: " << duracao.count() << " segundos" << std::endl;
    // Use a hash...
    
    // Exemplo de busca de usuário
    int id_user = 54766 ; // ID do usuário a ser buscado
    User* user = busca_user(*hash, id_user);
    if (user != nullptr) {
        std::cout << "Usuario encontrado: " << user->id_user << std::endl;
    } else {
        std::cout << "Usuario nao encontrado" << std::endl;
    }

   std::cout<< "Hash Montada" << std::endl;

    //delete hash; // Desaloca a memória
    return 0;
}
*/
// Fazer a pesquisa (3.2)
