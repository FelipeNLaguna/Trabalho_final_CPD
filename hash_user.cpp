#include "hash_user.hpp"
#include "parser.hpp"
#include<fstream>
#include<iostream>
#include<algorithm>
#include <chrono>
#define TAM_HASH 9473
// tem que ser testado
std::vector<User> le_users(const std::string nome_arq) {
    std::vector<User> usuarios;
    std::ifstream file(nome_arq);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo" << std::endl;
        return usuarios;
    }

    int id_player;
    int id_user;
    double rate;

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
            rate = std::stod(row[2]); // Transformando string em double

            /* Descricao do que as proximas linha fazem
                1.find_if é uma funcao que procura um elemento em uma lista que cumpre
                uma condicao especifica
                2.usuario.begin() primeiro elemento da lista usuario.end() é um dps do ultimo
                3.[id_user](const User& u) verifica se o id_user tá na lista
                4. expressao lambda
            */
            // Verifica se o usuário já existe no vetor
            auto it = std::find_if(usuarios.begin(), usuarios.end(), [id_user](const User& u) {
                return u.id_user == id_user;
            });

            /*
                1.it é a posicao do usuario na lista
                2.it->id_player acessa o vetor de id_player 
                3.it->notas acessa o vetor de notas           
            */
            if (it != usuarios.end()) {
                // Usuário já existe, adiciona id_player e rate aos vetores correspondentes
                it->id_player.push_back(id_player);
                it->notas.push_back(rate);
            } else {
                // Usuário não existe, cria um novo User e adiciona ao vetor
                User new_user;
                new_user.id_user = id_user;
                new_user.id_player.push_back(id_player);
                new_user.notas.push_back(rate);
                usuarios.push_back(new_user);
            }
        } catch (const std::exception& e) {
            std::cerr << "Erro ao processar linha: " << e.what() << std::endl;
            for (const auto& field : row) {
                std::cerr << field << " ";
            }
            std::cerr << std::endl;
        }
    }

    return usuarios;
}
// feito
int fun_hash(int id_user,int size){
    return id_user % size;
}
// tem que ser testado
void insere_user(Hash_user& hash , const User& user){
    int indice_hash;
    indice_hash = fun_hash(user.id_user,hash.size);
    // se nao tiver colisao adiciona user
    if(hash.table[indice_hash].empty()){
        hash.table[indice_hash].push_back(user); // push_back pq é uma lista
    }
    else{
        for(auto& existing_user : hash.table[indice_hash]){
            // testa se o user ja foi colocada na hash
            if(existing_user.id_user == user.id_user){
                // na teoria só o primeiro id_user adicionado vai possuir mais de um elemento
                // no vetor id_player
                existing_user.id_player.push_back(user.id_player[0]);
                existing_user.notas.push_back(user.notas[0]);
            }
        }
        hash.table[indice_hash].push_back(user);
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
    
    Hash_user* ht = new Hash_user(TAM_HASH); // Aloca dinamicamente
    std::vector<User> users = le_users("minirating.csv");
    for (const auto& user : users) {
        insere_user(*ht, user);
    }
    return ht; // Retorna o ponteiro para a hash alocada
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
    //int id_user = 123; // ID do usuário a ser buscado
    //User* user = busca_user(*hash, id_user);
   // if (user != nullptr) {
   //     std::cout << "Usuário encontrado: " << user->id_user << std::endl;
   // } else {
    //    std::cout << "Usuário não encontrado" << std::endl;
   // }

   std::cout<< "Hash Montada" << std::endl;

    //delete hash; // Desaloca a memória
    return 0;
}
*/
// Fazer a pesquisa (3.2)