#include "hash.hpp"
#include "hash_user.hpp"
#include "Jogador.hpp"
#include "TrieST.hpp"

// toupper
// Função para imprimir o vetor de tags
void imprime_tags(const std::vector<std::string>& tags_consulta) {
    for (const auto& tag : tags_consulta) {
        std::cout << "Tag: " << tag << std::endl;
    }
}
// pensar nos atributos passados e no retorno
void pesquisas(){

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
                return ;
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
            return; 
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
       }
       else{
            std::cout << "Comando invalido" << std::endl;
            return ;
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
                    return ;
                }
            }
            else{
                std::cout << "Comando invalido" << std::endl;
                return ;
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
            imprime_tags(tags_consulta);
        }
        else{
            std::cout << "Comando invalido" << std::endl;
            return ;
        }

    }
}