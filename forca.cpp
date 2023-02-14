#include <iostream> 
#include <string>
#include <map>
#include <vector>
#include <fstream> // fluxo de dados de arquivos 
#include <ctime> // iniciar semente dos números aleatórios 
#include <cstdlib> 

using namespace std; 

string palavra_secreta = "MELANCIA"; 
map<char, bool> chutou; 
vector<char> chutes_errados;

bool letra_existe(char chute){
    for(char letra : palavra_secreta){
        if(chute == letra){
            return true; 
        }
    }
    return false; 
}

bool nao_acertou(){
    for(char letra : palavra_secreta){
        if(!chutou[letra]){
            return true; 
        } 
    }
    return false;
}

bool nao_enforcou(){
    return chutes_errados.size() < 5; 
}

void imprime_cabecalho(){
    cout << " ***************************************" << endl;
    cout << " **** Bem-vindos ao jogo da forca! ****" << endl;
    cout << " ***************************************" << endl;
    cout << endl; 
}

void imprime_erros(){
    cout << "Chutes errados: " << endl; 
    for(char letra: chutes_errados){
        cout << letra << endl; 
    }
    cout << endl; 
}

void imprime_palavra(){
    for(char letra : palavra_secreta){
            if(chutou[letra]){
                cout << letra << "  "; 
            } else {
                cout << "_ ";
            }
        }
    cout << endl;
}

void chuta(){
        cout << "Digite seu chute: " << endl;
        char chute; 
        cin >> chute; 
        chutou[chute] = true;

        if(letra_existe(chute)){
            cout << "Você acertou! Seu chute está na palavra" << endl;
        } else {
            cout << "Você errou! Seu chute não está na palavra." << endl;
            // jogar no final do vetor 
            chutes_errados.push_back(chute); 
        }
         cout << endl;
}

vector<string> le_arquivo(){
    ifstream arquivo;
    arquivo.open("palavras.txt");
    int quantidade_de_palavras;
    arquivo >> quantidade_de_palavras; 
    vector<string> palavras_do_arquivo; 

    if(arquivo.is_open())
    for(int i = 0; i < quantidade_de_palavras; i++){
        string palavra_lida;
        arquivo >> palavra_lida;
        palavras_do_arquivo.push_back(palavra_lida); 
    }
    // fechando arquivo 
    arquivo.close();
    return palavras_do_arquivo;
}

void sorteia_palavra(){
    vector<string> palavras = le_arquivo(); 

    srand(time(NULL));
    int indice_sorteado = rand() % palavras.size(); 

    palavra_secreta = palavras[indice_sorteado]; 
}

int main(){ 
    imprime_cabecalho();
    le_arquivo();
    sorteia_palavra();
    
    while(nao_acertou() && nao_enforcou()){
        imprime_erros();
        imprime_palavra();
        chuta(); 
    }

    cout << "Fim de jogo!" << endl;
    cout << "A palavra secreta era: " << palavra_secreta << endl;

    if(nao_acertou()){
        cout << "Você perdeu! Tente novamente!" << endl;
    } 
    else {
        cout << "Parabéns! Você acertou a palavra secreta!" << endl;        
    }
}