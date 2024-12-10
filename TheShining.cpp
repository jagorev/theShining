#include <iostream>
#include <fstream>


using namespace std;

class stack_polaretto{
    vector<int> vec();
    set<int> in_stack;

    public:

    void push(int v){
        vec.push_back(v);
        in_stack.insert(v);
    }
    
    void pop(){
        int v = vec[vec.size()-1]
        vec.pop_back();
        in_stack.remove(v);
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
    vector<vector<int>> grafo_iniziale;
    int s,a;
    for(int i = 0 ; i < numero_archi; ++i){
        inputFile>>s>>a;
        grafo_iniziale[s].push_back(a);
    }
    //vector<set<int>> corridoi(numero_nodi);
                                                                                                            
   

    

    vector<vector<int>> cicli;

    cicli = trova_cicli(grafo_iniziale);

}

vector<vector<int>> trova_cicli(vector<vector<pair<int,bool>>> grafo){ // sparatemi

    vector<vector<int>> cicli;

    stack_polaretto stack;

    stack.push(0);
    vector<bool> visited(numero_nodi,false);
    visited[0] = true;

    while(!stack.isEmpty()){

        int elem = stack.top();
        visieted[elem] = true;

        for( auto a : grafo[0]){
            if(stack.isInStack(a)){
                // ciclo

                break;
            }
            if(!visited[a]){
                stack.push(a); // il primo adiacente non visitato
                break;
            }
        }

    }

}






//memorizzazione del file input nella lista di adiacenza



