#include <iostream>
#include <fstream>
#include <vector>
#include <set>


using namespace std;

vector<vector<int>> trova_cicli(vector<vector<pair<int,bool>>> grafo, int num_nodi){ // sparatemi

    vector<vector<int>> cicli;

    stack_polaretto stack;

    stack.push(0); // se 0 è separato da problemi
    vector<bool> visited(num_nodi,false);

    while(!stack.isEmpty()){

        int elem = stack.top();
        visited[elem] = true;

        for( auto a : grafo[0]){
            if(stack.isInStack(a.first)){
                // ciclo
                cicli.push_back(stack.getCycle(a.first));
                break;
            }
            if(!a.second){
                a.second = true;
                stack.push(a.first); // il primo adiacente non visitato
                break;
            }
        }

    }
    return cicli;
}


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
        return vec[vec.size()];
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
        if(i < 0 && vec[0] != n){ // se arrivo infondo e l'ultimo elemento non è quello cercato allora ritorno vettore vuoto
            return vector<int>(0);
        }
        return ris;
    }
};

//struttura per memorizzare il nodo
/* struct node{
    int arrive = -1;
    node* next;
};
 */

int main(){

    int numero_nodi, numero_archi;

    ifstream inputFile("input.txt");
    if (!inputFile) {
        cout << "Errore: impossibile aprire il file di input" << endl;
        return -1;
    }

    inputFile >> numero_nodi >> numero_archi;
    vector<vector<pair<int,bool>>> grafo_iniziale;
    int s,a;
    for(int i = 0 ; i < numero_archi; ++i){
        inputFile>>s>>a;
        grafo_iniziale[s].push_back(pair<int,bool>(a,false));
    }
    //vector<set<int>> corridoi(numero_nodi);
                                                                                                            
    vector<vector<int>> cicli;

    cicli = trova_cicli(grafo_iniziale,numero_nodi);

    for(auto a: cicli){
        for(auto b: a){
            cout << b << " ";
        }
        cout <<endl;
    }

}







//memorizzazione del file input nella lista di adiacenza



