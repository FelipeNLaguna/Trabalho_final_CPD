#include "hash_jog.hpp"
#include "hash_user.hpp"
#include "hash_user.cpp"
#include "Jogador.hpp"
#include "TrieST.hpp"
#include "parser.hpp"
#include "radix.cpp"
#include <set>
#include <algorithm>
#include <chrono>

template <typename Value>
void inverteVetor(std::vector<Value> &vetor)
{
    int tam_vetor = vetor.size();
    for (int i = 0; i < tam_vetor / 2; i++)
    {
        std::swap(vetor[i], vetor[tam_vetor - 1 - i]);
    }
}

void constroiHashETrie(vector<Jogador *> &hash_jogadores, TrieST<Jogador *> &trie)
{
    // Abra o arquivo CSV usando std::ifstream
    std::ifstream players("players.csv");

    std::ifstream rating("rating.csv");

    // Verifique se o arquivo foi aberto corretamente
    if (!players.is_open())
    {
        throw std::runtime_error("Não foi possível abrir o arquivo CSV.");
    }

    aria::csv::CsvParser players_csv(players);
    aria::csv::CsvParser rating_csv(rating);

    // Itere sobre o conteúdo do CSV
    bool cabecalho = true;
    for (const auto &row : players_csv)
    {
        if (cabecalho)
        {
            cabecalho = false;
            continue;
        }
        Jogador *j = new Jogador(stoi(row[0]), row[1], row[2], row[3], row[4]);

        hashingJ(j, hash_jogadores, 19001);

        trie.put(j->short_name, j);
    }

    cabecalho = true;

    for (const auto &row : rating_csv)
    {
        if (cabecalho)
        {
            cabecalho = false;
            continue;
        }

        Jogador *jog_aux = (buscaHashJ(stoi(row[1]), hash_jogadores));
        if (jog_aux != nullptr)
            (*jog_aux).add_avaliacao(stof(row[2]));
    }

    players.close();
    rating.close();
}

// Função para imprimir um vetor de inteiros
void imprime_vetor(const std::vector<int>& vetor, int elementos_por_linha = 10) {
    int contador = 0;
    for (int valor : vetor) {
        std::cout << valor << " ";
        contador++;
        if (contador % elementos_por_linha == 0) {
            std::cout << std::endl; // Adiciona uma quebra de linha após um certo número de elementos
        }
    }
    if (contador % elementos_por_linha != 0) {
        std::cout << std::endl; // Adiciona uma quebra de linha no final, se necessário
    }
}

TrieST_tags monta_tags(){
    std::ifstream tags("tags.csv");

    TrieST_tags trie_tags;

    bool cabecalho = true;

    if(!tags.is_open()){
        std::cerr << "Erro ao abrir o arquivo de tags" << std::endl;
        return trie_tags;
    }

    aria::csv::CsvParser tags_csv(tags);
    // cria a arvore de tags
    for(const auto& row : tags_csv){
        if(cabecalho){
            cabecalho = false;
            continue;
        }
        // row[2] pq é onde esta contido as tags e row[1] os id_jogadores
        trie_tags.put(row[2],std::stoi(row[1]));
    }
    return trie_tags;

}

// Função para imprimir o vetor de tags
void imprime_tags(const std::vector<std::string>& tags_consulta) {
    for (const auto& tag : tags_consulta) {
        std::cout << "Tag: " << tag << std::endl;
    }
}

// Função para buscar jogadores pelo vetor de ids e ordenar por nome e rating
std::vector<Jogador*> ordena_tags(std::vector<int>& ids, std::vector<Jogador*>& hash_jogadores) {
    std::vector<Jogador*> jogadores;

    for (int id : ids) {
        Jogador* jogador = buscaHashJ(id, hash_jogadores);
        if (jogador != nullptr) {
            jogadores.push_back(jogador);
        }
    }

    // Ordenar jogadores por rating usando radix sort
    radix_sort(jogadores, 10);
    inverteVetor(jogadores);

    return jogadores;
}

// Função para ordenar primeiro por rating e depois por nota
void ordenar_users(std::vector<Jogador_nota>& jogadores) {
    // Primeiro, ordena pelo rating (secundário)
    radix_sort_jogadores(jogadores, false);

    // Depois, ordena pela nota (principal), preservando a estabilidade
    radix_sort_jogadores(jogadores, true);
}

void printTop30PlayersByUser(Hash_user* hash_users, int id_user, std::vector<Jogador*>& hash_jogadores) {
    User* user = busca_user(*hash_users, id_user);
    if (!user) {
        std::cout << "Usuário não encontrado." << std::endl;
        return;
    }

    const std::vector<int>& ids = user->id_player;
    const std::vector<float>& notas = user->notas;

    std::vector<Jogador_nota> jogadores_com_notas;

    // Associa os IDs aos jogadores e suas respectivas notas
    for (size_t i = 0; i < ids.size(); ++i) {
        Jogador* jogador = buscaHashJ(ids[i], hash_jogadores);
        if (jogador) {
            jogadores_com_notas.push_back({jogador, notas[i]});
        }
    }

    // Ordena os jogadores
    ordenar_users(jogadores_com_notas);

    // Limita a 30 jogadores ou menos
    size_t top_count = std::min(jogadores_com_notas.size(), size_t(30));

    // Imprime os 30 melhores jogadores
    std::cout << "Top " << top_count << " jogadores avaliados pelo usuário " << id_user << ":\n";
    for (size_t i = 0; i < top_count; ++i) {
        Jogador* jogador = jogadores_com_notas[i].jog;
        float nota = jogadores_com_notas[i].nota;
        std::cout << i + 1 << ". " << jogador->short_name
                  << " (Nota: " << nota
                  << ", Rating: " << jogador->rating << ")\n";
    }
}
int main(){
    // monta as estruturas antes da pesquisa
    auto inicio = std::chrono::high_resolution_clock::now();
    Hash_user* hash = monta_hash();
    TrieST_tags arvore_tags = monta_tags();
    std::vector<Jogador*> hash_jogadores(19001, nullptr);
    TrieST<Jogador*> trie;
    constroiHashETrie(hash_jogadores, trie);
    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracao = fim - inicio;

    std::cout << "Tempo para montar as : " << duracao.count() << " segundos" << std::endl;

    // push back para nova string
    std::string consulta;
    std::string tipo_consulta; // tipo da consulta
    bool prefixo = false;
    bool user = false;
    bool top = false;
    bool tags = false;

    getline(std::cin,consulta);
    std::cout << "====================================="<<std::endl;
    bool principal = false; // tipo de consulta já foi testado?

    int i = 0;
    
    // quando a entrada for user; por exemplo , nao printa nada
    while((i<consulta.size()) && (principal == false)){
        // testa se o caracter é uma letra usando a tabela ascii
        if( (65 <= consulta[i] && consulta[i] <= 90) || (97 <= consulta[i] && consulta[i] <= 122)){
            tipo_consulta.push_back(consulta[i]);
        }
        else{
            principal = true;
            // tranformar o tipo_consulta em toupper
            if(tipo_consulta == "prefixo"){
                // aplica a pesquisa 3.1
                // liga uma flag_prefixo
                prefixo = true;
                std::cout << "prefixo" << std::endl;
            }
            else if(tipo_consulta == "user"){
                // aplica pesquisa 3.2
                // liga uma flag_user
                user = true;
                std::cout << "user" << std::endl;
            }
            // esse é diferente , tem que testar se é espaco ou numero
            else if(tipo_consulta == "top"){
                // aplica pesquisa 3.3
                // liga uma flag_top
                top = true;
                std::cout << "top" << std::endl;
            }
            else if(tipo_consulta == "tags"){
                // aplica 3.4
                // liga uma flag_tag
                tags = true;
                std::cout << "tags" << std::endl;
            }
            else{
                std::cout << "Comando invalido" << std::endl;
                return 1;
            }
        }
        i++;
    }

    i--; // para testar se a entrada esta no formato valido

    if(prefixo){
        // testo se o proximo caracter é ' ' se for comeco a pegar o prefixo ate a palavra acabar 
        if(consulta[i] == ' '){
            i++;
            std::string nome_prefixo;
            for(int j = i; j <consulta.size() ; j++){
                nome_prefixo.push_back(consulta[j]);
            }
            std::cout << nome_prefixo << std::endl;
            // chama pesquisa 3.1
        }
        else{
           std::cout << "Comando invalido" << std::endl;
            return 1; 
        }
    }

    if(user){
       // testo se o proximo caracter é ' ' se for comeco a pegar o prefixo ate a palavra acabar
       // usa stoi e testa se é um numero
        if(consulta[i] == ' '){
            i++;
            std::string id_user_std;
            bool num_valido = true; // usando quando a pesquisa for chamada
            for(int j = i ; j < consulta.size() ; j++){
                // testa se o caracter é um numero usanda a tabela ascii
                if((48 <= consulta[j]) && (consulta[j] <= 57)){
                    id_user_std.push_back(consulta[j]);
                }
                else{
                    num_valido = false;
                }
            }
            // transforma o id em um numero 
            int id_user = std::stoi(id_user_std);
            std::cout << id_user << std::endl;
            // testa se o numero é valido 
            // se for chama pesquisa 3.2
            printTop30PlayersByUser(hash,id_user,hash_jogadores);
       }
       else{
            std::cout << "Comando invalido" << std::endl;
            return 1;
       }
    }

    if(top){
        // pega o numero ate o proximo espaco depois pega a posicao
        std::string num_top_std;
        std::string posicao; // posicao que deseja ranquear
        int num_top;
        bool terminou_num = false; // o numero já foi lido?
        bool primeiro_carac = false; // testa se é num

        int j = i;

        // pega quantos jogadores devem ser ranqueados
        while((j<consulta.size()) && (terminou_num == false)){
            if((48 <= consulta[j]) && (consulta[j] <= 57)){
                num_top_std.push_back(consulta[j]);
                primeiro_carac = true;
            }
            else if(consulta[j] == ' '){
                if(primeiro_carac){
                    terminou_num = true;
                }
                else{
                    std::cout << "Comando invalido" << std::endl;
                    return 1;
                }
            }
            else{
                std::cout << "Comando invalido" << std::endl;
                return 1;
            }
            j++;
        }
        // converte para inteiros
        num_top = std::stoi(num_top_std);

        // continua de onde parou 
        for(j ; j < consulta.size() ; j++){
            posicao.push_back(consulta[j]);
        }
        std::cout << "Posicao : " << posicao << "Num : " << num_top << std::endl;

        // Oq acontece quando a posicao nao existe?

        // chama pesquisa
    }

    if(tags){
        // percorre ate achar aspar e forma uma palavra a cada fecha aspas
        if(consulta[i] == ' '){
            i++;
            int cria_tag = 0;
            std::vector<std::string> tags_consulta;
            std::string tag_aux; // vai ser usada para colocar as tags no vetor

            for(int j = i ; j < consulta.size() ; j++){
                // testa se o caracter é uma aspa
                if(consulta[j] == '\''){
                    cria_tag++;
                    if(cria_tag == 2){
                        tags_consulta.push_back(tag_aux);
                        tag_aux.clear(); // limpa a string para proxima palavra
                        cria_tag = 0;
                    }
                }
                else{
                    // testa se o cria_tag é diferente de zero(aspa tá aberta)
                    if(cria_tag){
                        tag_aux.push_back(consulta[j]);
                    }
                }
            }
            // testa se tem aspas abertas
            if(cria_tag == 1){
                std::cout << "Comando invalido" << std::endl;
                return 1;
            }
            // tags_consulta é um vetor de tags
            // quero um vetor de ids que mantem as informacoes de tag

            if(!tags_consulta.empty()){
                std::cout << "Tags consulta nao esta vazio" << std::endl;
                
                std::vector<int> id_primeira_tag = arvore_tags.get(tags_consulta[0]);
                std::set<int> cluster_id(id_primeira_tag.begin(), id_primeira_tag.end());
                
                std::vector<int> aux_arr;
                std::set<int> aux_cluster;

                for(int k = 1 ; k < tags_consulta.size() ; k++){
                    std::set<int> intersection;
                    
                    // criando o set2
                    aux_arr = arvore_tags.get(tags_consulta[k]);
                    std::set<int> aux_cluster(aux_arr.begin(),aux_arr.end());

                    std::set_intersection(
                        cluster_id.begin() , cluster_id.end() ,
                        aux_cluster.begin() , aux_cluster.end() ,
                        std::inserter(intersection,intersection.begin()) // insere no conjunto
                    );

                    // atualiza o vetor de ids apos a interseccao
                    cluster_id = intersection;
                }
                // transforma o set resultande em vetor
                std::vector<int> id_jog(cluster_id.begin() , cluster_id.end());
                imprime_vetor(id_jog);

                // Buscar e ordenar jogadores
                std::vector<Jogador*> hash_jogadores(19001, nullptr);
                TrieST<Jogador*> trie;
                constroiHashETrie(hash_jogadores, trie);

                auto jogadores_ordenados = ordena_tags(id_jog, hash_jogadores);

                for (auto jogador : jogadores_ordenados) {
                    jogador->imprimeJogador();
                }
                // deixar bonito 
            }
            else{
                std::cout << "Comando invalido" << std::endl;
                return 1;
            }
        }
        else{
            std::cout << "Comando invalido" << std::endl;
            return 1;
        }
    }
}
