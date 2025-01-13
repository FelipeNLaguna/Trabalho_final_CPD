#ifndef HASH_USER_HPP
#define HASH_USER_HPP

#include<string>
#include<vector>
#include<list>

// struct para guardar informações de cada usuario
struct User{
    int id_user;
    std::vector<int> id_player;
    std::vector<float> notas; // uma nota para cada jogador
    // cuidar para o id e a nota estarem no mesmo indice
};

struct Hash_user{
    int size;
    // a hash é um vetor de listas do tipo user
    std::vector<std::list<User>> table;
    // construtor da hash
    Hash_user(int tam) : size(tam) , table(tam) {}

};
std::vector<User> le_users(const std::string nome_arq); // se o csv e retorna um vetor de user
int fun_hash(int id_user , int size);
void insere_user(Hash_user& hash , const User& user);
User* busca_user(Hash_user& hash , int id_user);
Hash_user* monta_hash(); //Usa as outras funcoes para monstar a hash


#endif
