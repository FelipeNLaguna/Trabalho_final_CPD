#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define R 256

using namespace std;

struct ContaPalavra {
    std::string palavra;
    int contagem;
};

int charAt(string S, int d){
    if(d < S.length()){
        return S.at(d);
    }
    return -1;
}

void radix_sort(vector<ContaPalavra>& C, int modulo){
    vector<ContaPalavra> aux;
    aux.resize(C.size());
    vector<int> indices(10, 0);
    int posicao, haValor = 0;

    // Zera os indices
    fill(indices.begin(), indices.end(), 0);

    // Passa contando cada casa (LSD)  
    for(int i = 0; i < C.size(); i++){
        posicao = (C[i].contagem % modulo) / (modulo / 10);
        indices[posicao]++;
        haValor = haValor || posicao;
    }

    // Se nenhuma posicao teve valor, o modulo ultrapassou o maior valor
    if(!haValor){
        return;
    }

    // Transforma em indice
    for(int i = 1; i < 10; i++){
        indices[i] += indices[i-1];
    }

    // Percorre o vetor das palavras, consulta o indices e coloca na posicao correta
    for(int i = C.size() - 1; i >= 0; i--){
        aux[--indices[(C[i].contagem % modulo) / (modulo / 10)]] = C[i];
    }

    for(int i = 0; i < C.size(); i++){
        C[i] = aux[i];
    }   

    radix_sort(C, modulo * 10);

    return;
}

void radix_sort_msd(vector<string>& C, int piso, int teto, int n){
    if(teto <= piso){
        return;
    }

    vector<int> conta(R+2, 0);
    vector<string> aux(teto - piso + 1);

    // Preenchendo o vetor das letras com as frequencias
    for(int i = piso; i <= teto; i++){
        conta[charAt(C[i], n) + 2]++;
    }

    // Transforma a contagem em indices
    for(int r = 0; r < R + 1; r++){
        conta[r+1] += conta[r];
    }

    // Distribui no auxiliar de acordo com os indices encontrados
    for(int i = piso; i <= teto; i++){
        aux[conta[charAt(C[i], n) + 1]++] = C[i];
    }

    // Copia do aux para o original
    for(int i = piso; i <= teto; i++){
        C[i] = aux[i - piso];
    }

    // Chama recursivamente para cada caracter
    for(int r = 0; r < R; r++){
        radix_sort_msd(C, piso + conta[r], piso + conta[r + 1] - 1, n + 1);
    }

}

int ordenaLivro(string pathLivro, string pathSaida){
    vector<string> palavras;
    string pala_aux;
    
    // Abrindo o arquivo do livro
    ifstream livro(pathLivro);

    if(!livro){
        cout << "Não foi possível abrir o arquivo de texto.\n";
        return 0;
    }

    ofstream saida(pathSaida);
    
    if(!saida){
        cout << "Não foi possível abrir o arquivo de saídas.\n";
        return 0;
    }


    // Leitura e alocamento em vetor
    while(livro >> pala_aux){
        palavras.push_back(pala_aux);
    }

    radix_sort_msd(palavras, 0, palavras.size() - 1, 0);

    // Escreve no arquivo de saida
    for(auto& palavra : palavras){
        saida << palavra << "\n";
    }

    livro.close();
    saida.close();

    return 1;
}

int contaPalavrasLivro(string pathSorted, string pathCounted){
    vector<ContaPalavra> concordancia;
    ContaPalavra verbete;
    string pala_aux, pala_atual;
    int contagem = 1;
    
    // Abrindo o arquivo do livro
    ifstream sorted(pathSorted);

    if(!sorted){
        cout << "Não foi possível abrir o arquivo ordenado.\n";
        return 0;
    }

    ofstream counted(pathCounted);
    
    if(!counted){
        cout << "Não foi possível abrir o arquivo contado.\n";
        return 0;
    }

    // Primeira ocorrencia, assim o aux tem dado
    sorted >> pala_aux;

    while(sorted >> pala_atual){
        // Se a palavra atual for igual a anterior, adiciona a contagem
        if(pala_atual == pala_aux){
            contagem++;
        } else {
            verbete = {pala_aux, contagem};
            concordancia.push_back(verbete);
            contagem = 1;
            pala_aux = pala_atual;
        }
    }

    // Tratamento do ultimo caso
    verbete = {pala_aux, contagem};
    concordancia.push_back(verbete);

    // Escreve no arquivo de saida
    for(auto& verbete : concordancia){
        counted << verbete.palavra << " " << verbete.contagem << "\n";
    }

    sorted.close();
    counted.close();
            
}

int classificaPalavrasLivro(string pathCounted, string pathRanked, int escritas){
    vector<ContaPalavra> dicionario;
    string pala_aux;
    int contagem;
    
    // Abrindo o arquivo do livro
    ifstream counted(pathCounted);

    if(!counted){
        cout << "Não foi possível abrir o arquivo contado.\n";
        return 0;
    }

    ofstream ranked(pathRanked);
    
    if(!ranked){
        cout << "Não foi possível abrir o arquivo classificado.\n";
        return 0;
    }

    // Coloca todas os verbetes no dicionario
    while(counted >> pala_aux >> contagem){
        dicionario.push_back({pala_aux, contagem});
    }

    // Ordena o dicionario
    radix_sort(dicionario, 10);

    
    // Escreve, em ordem decrescente as n (escritas) primeiras palavras

    for(int j = dicionario.size() - 1; j > dicionario.size() - 1 - escritas; j--){
        ranked << dicionario[j].palavra << " " << dicionario[j].contagem << "\n";
    }
    
    counted.close();
    ranked.close();
    
}


int main(){
    
    ordenaLivro("entradas-lab3/frankestein.txt", "saidas/frankestein_sorted.txt");

    contaPalavrasLivro("saidas/frankestein_sorted.txt", "saidas/frankestein_counted.txt");
    
    classificaPalavrasLivro("saidas/frankestein_counted.txt", "saidas/frankestein_ranked.txt", 2000);

    ordenaLivro("entradas-lab3/war_and_peace.txt", "saidas/war_and_peace_sorted.txt");

    contaPalavrasLivro("saidas/war_and_peace_sorted.txt", "saidas/war_and_peace_counted.txt");
    
    classificaPalavrasLivro("saidas/war_and_peace_counted.txt", "saidas/war_and_peace_ranked.txt", 2000);

    ordenaLivro("entradas-lab3/biblia_c.txt", "saidas/biblia_c_sorted.txt");

    contaPalavrasLivro("saidas/biblia_c_sorted.txt", "saidas/biblia_c_counted.txt");
    
    classificaPalavrasLivro("saidas/biblia_c_counted.txt", "saidas/biblia_c_ranked.txt", 2000);
    
    return 0;
}
