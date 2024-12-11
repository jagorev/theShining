
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>


using namespace std;

int n_cicli = 0;
vector<int> ciclo;

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


    void getCycle(int n, vector<int> &conteggio){ // da chiamare solo quando si è sicuri, gestisco il caso in cui non ci sia ma è meglio non specare tempo
        int i;
        
        if(n_cicli == 0){
            for(i = vec.size() -1 ; i >= 0 && vec[i] != n ; --i){
                ciclo.push_back(vec[i]);
                ++conteggio[vec[i]];
            }
            conteggio[n]++;
            ciclo.push_back(n);
            ++n_cicli;
        }else{
            for(i = vec.size() -1 ; i >= 0 && vec[i] != n ; --i){
                ++conteggio[vec[i]];
            }
            conteggio[n]++;
            ++n_cicli;
        }
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


void trova_cicli(vector<node> grafo, int num_nodi, vector<int>& conteggio, set<int>& nodi_visistare ){ // ritorna i cicli del grafo


    stack_polaretto stack;

  /*   vector<bool> visited(num_nodi,false); // inizializzo a false */

    while(!nodi_visistare.empty()){

        stack.push(*nodi_visistare.begin());

        while(!stack.isEmpty()){

            int elem = stack.top(); // prendo il primo elemento. (?) se zero NON è nel grafo?
            nodi_visistare.erase(elem);

           /*  visited[elem] = true; */

            if(grafo[elem].getDaVisitare().empty()){ // se non ci sono elementi da visitare (non ci sono vicini)
                grafo[elem].swap();
                stack.pop();

            }else{
                // Prendo il primo elemento da `daVisitare`
                auto it = grafo[elem].getDaVisitare().begin(); //restiutuisce un iteratore al primo elemento
                int a = *it;

                // Sposto l'elemento
                grafo[elem].getVisistati().insert(a);
                grafo[elem].getDaVisitare().erase(it);

                if (stack.isInStack(a)) {
                    // Trovato un ciclo, non pusho nello stack
                    
                    stack.getCycle(a, conteggio);

                } else {
                    // Aggiungi il nodo nello stack
                    stack.push(a);
                }
            }

        }

    }
}


// quando faccio pop() devo guardare nel set 'daVisitare'


int main(){


    int numero_nodi, numero_archi;

    ifstream inputFile("input.txt");
    ofstream out("output.txt");

    inputFile >> numero_nodi >> numero_archi;
    vector<node> grafo_iniziale(numero_nodi);
    set<int> nodi_da_visitare;
    for(int i = 0; i < numero_nodi; ++i){
        nodi_da_visitare.insert(i);
    }
    int s,a;
    for(int i = 0 ; i < numero_archi; ++i){
        inputFile>>s>>a;

        grafo_iniziale[s].getDaVisitare().insert(a);
    }
    //vector<set<int>> corridoi(numero_nodi);

    vector<int> conteggio(numero_nodi,0);

    trova_cicli(grafo_iniziale,numero_nodi,conteggio,nodi_da_visitare);

    /*
    for(auto a: cicli){
        for(auto b: a){
            cout << b << " | ";
        }
        cout <<endl;
    }*/


    //cout << "cicli size: " << cicli.size() << endl;
    for(int i = 0; i < conteggio.size(); ++i){
        if(n_cicli == conteggio[i]) {
            //cout << conteggio[i] << " ";
            //cout << i << "";
            out << i << endl;
            out << ciclo.size()<<" ";
            for(auto a = ciclo.rbegin(); a != ciclo.rend(); a++){
                out<<*a<<" ";
            }
            out.close();
            return 0;
        }
    }
    out << "-1";
    out.close();
    return 0;
}

//memorizzazione del file input nella lista di adiacenza



