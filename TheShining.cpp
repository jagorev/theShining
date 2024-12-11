#include <iostream>
#include <fstream>
#include <vector>
#include <set>


using namespace std;

class stack_polaretto{
    private:
        vector<int> vec;
        set<int> in_stack;
    public:

    void push(int v){
        vec.push_back(v);
        in_stack.insert(v);
    }
    
    void pop(){
        int v = vec[vec.size() - 1];
        vec.pop_back();
        in_stack.erase(v);
    }

    int top(){
        return vec[vec.size() - 1];
    }

    bool isInStack(int n){
        return in_stack.find(n) != in_stack.end(); // controlla
    }
    
    bool isEmpty(){
        return vec.size() == 0;
    }


    vector<int> getCycle(int n){ // da chiamare solo quando si è sicuri, gestisco il caso in cui non ci sia ma è meglio non specare tempo
        vector<int> ris;
        int i;
        for(i = vec.size() -1 ; i >= 0 && vec[i] != n ; --i){
            ris.push_back(vec[i]);
        }
        ris.push_back(n);
        if(i < 0 && vec[0] != n){ // se arrivo infondo e l'ultimo elemento non è quello cercato allora ritorno vettore vuoto
            return vector<int>(0);
        }
        return ris;
    }
};

class node{
    bool swapped = false;
    set<int> daVisitare;
    set<int> visitati;
    public:
    set<int>& getVisistati(){
        return swapped ? daVisitare : visitati;
    }
    set<int>& getDaVisitare(){
        return swapped ? visitati : daVisitare;
    }

    void swap(){
        swapped = !swapped;
    }

};


vector<vector<int>> trova_cicli(vector<node> grafo, int num_nodi, vector<vector<int>> &cicli ){ // ritorna i cicli del grafo

    stack_polaretto stack;

    stack.push(0); // se 0 è separato da problemi

    vector<bool> visited(num_nodi,false);

    while(!stack.isEmpty()){

        int elem = stack.top();

        visited[elem] = true;

        if(grafo[elem].getDaVisitare().empty()){
            grafo[elem].swap();
            stack.pop();

        }else{
             // Prendo il primo elemento da `daVisitare`
            auto it = grafo[elem].getDaVisitare().begin();
            int a = *it;

            // Sposto l'elemento
            grafo[elem].getVisistati().insert(a);
            grafo[elem].getDaVisitare().erase(it);

            if (stack.isInStack(a)) {
                // Trovato un ciclo, non pusho nello stack
                cicli.push_back(stack.getCycle(a));
            } else {
                // Aggiungi il nodo nello stack
                stack.push(a);
            }
        }

    }

    return cicli;
}

// quando faccio pop() devo guardare nel set 'daVisitare'


int main(){

    int numero_nodi, numero_archi;

    ifstream inputFile("input.txt");
    if (!inputFile) {
        cout << "Errore: impossibile aprire il file di input" << endl;
        return -1;
    }

    inputFile >> numero_nodi >> numero_archi;
    vector<node> grafo_iniziale(numero_nodi);
    int s,a;
    for(int i = 0 ; i < numero_archi; ++i){
        inputFile>>s>>a;
        
        grafo_iniziale[s].getDaVisitare().insert(a);
    }
    //vector<set<int>> corridoi(numero_nodi);
                                                                                                            
    vector<vector<int>> cicli(numero_nodi/3);

    trova_cicli(grafo_iniziale,numero_nodi,cicli);

    for(auto a: cicli){
        for(auto b: a){
            cout << b << " | ";
        }
        cout <<endl;
    }

    return 0;
}

//memorizzazione del file input nella lista di adiacenza



