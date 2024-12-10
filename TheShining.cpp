#include <iostream>
#include <fstream>


using namespace std;

struct stack_polaretto{

    vector<int> vec();

    void push(int v){
        vec.push_back(v);
    }
    
    void pop(){
        vec.pop_back();
    }

    vector<int> getCycle(int n){ // da chiamare solo quando si è sicuri, gestisco il caso in cui non ci sia ma è meglio non specare tempo
        vector<int> ris();
        int i;
        for(i = vec.size() -1 ; i >= 0 && vec[i] != n ; --i){
            ris.push_back(vec[i]);
        }
        if(i < 0 && vec[0] != n){ // se arrivo infondo e l'ultimo elemento non è quello cercato allora ritorno vettore vuoto
            return vector<int>(0);
        }
        return ris;
        
    }
}

//struttura per memorizzare il nodo
struct node{
    int value;
    node* next;
};



int main(){

    int numero_nodi, numero_archi;

    
    

    ifstream inputFile("input.txt");
    if (!inputFile) {
        cout << "Errore: impossibile aprire il file di input" << endl;
        return 1;
    }
    else{
        inputFile >> numero_nodi >> numero_archi;
        

    }
        
    



    vector<node> grafo_iniziale();
}






//memorizzazione del file input nella lista di adiacenza



