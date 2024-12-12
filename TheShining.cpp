#include <fstream>
#include <vector>
#include <iostream>
#include <bitset>

using namespace std;

int n_cicli = 0;
vector<int> ciclo;
bitset<100000> nodi_ciclo;
bitset<100000> nodi_comuni;
bitset<100000> temp;

ifstream inputFile("input.txt");
ofstream outputFile("output.txt");

void casoBrutto(vector<int>& altroCiclo){

    outputFile << "-1"<<endl;
    outputFile << *ciclo.rbegin() << endl;
    outputFile << ciclo.size() << " ";
    for(auto a = ciclo.rbegin(); a != ciclo.rend(); a++){
        outputFile << *a << " ";
    }
    outputFile<<endl;

    outputFile << altroCiclo.size() << " ";
    for(auto a = altroCiclo.rbegin(); a != altroCiclo.rend(); a++){
        outputFile << *a << " ";
    }
    outputFile<<endl;

    exit(0);
}


class StackPolaretto {
    private:
        vector<int> vec;
        vector<bool> in_stack;

    public:
        StackPolaretto(int n) : in_stack(n, false) {}

        void push(int v) {
            vec.push_back(v);
            in_stack[v] = true;
        }

        void pop() {
            int v = vec.back();
            vec.pop_back();
            in_stack[v] = false;
        }

        int top() {
            return vec.back();
        }

        bool isInStack(int n) {
            return in_stack[n];
        }

        bool isEmpty() {
            return vec.empty();
        }

        void getCycle(int n) {
            temp.reset();
            if(n_cicli == 0){
                
                for (int i = vec.size() - 1; i >= 0; --i) {
                    ciclo.push_back(vec[i]);
                    nodi_ciclo[vec[i]] = 1;
                    nodi_comuni[vec[i]] = 1;
                    if (vec[i] == n) break;
                }
            }else{ // se ricevo un ciclo senza nodi in comune al primo chiamo funzione e passo 2 cicli (-1)
                bool trovato = false;
                for (int i = vec.size() - 1; i >= 0; --i) {
                    if(nodi_ciclo[vec[i]]){
                        trovato = true;
                    }
                   /*  conteggio[vec[i]]; // forse non serve più */
                    temp[vec[i]] = 1;
                    if (vec[i] == n) break;
                }
                if(!trovato){
                    vector<int> altroCiclo;
                    for (int i = vec.size() - 1; i >= 0; --i) {
                        altroCiclo.push_back(vec[i]);
                        if (vec[i] == n) break;
                    }
                    casoBrutto(altroCiclo); 
                }
                nodi_comuni &= temp;
            }
            ++n_cicli;
        }
};

void trova_cicli(const vector<vector<int>> &grafo, vector<bool> &visitati) {
    int n = grafo.size();
    StackPolaretto stack(n);

    for (int start = 0; start < n; ++start) {
        if (visitati[start]) continue;

        stack.push(start);

        while (!stack.isEmpty()) {
            int nodo = stack.top();

            // Se tutti i vicini sono stati visitati o non ci sono vicini, esci
            bool avanzato = false;
            for (int vicino : grafo[nodo]) {
                if (stack.isInStack(vicino)) {
                    // Trovato un ciclo
                    stack.getCycle(vicino);
                } else if (!visitati[vicino]) {
                    // Continua il DFS
                    stack.push(vicino);
                    avanzato = true;
                    break;
                }
            }

            if (!avanzato) {
                stack.pop();
                visitati[nodo] = true;
            }
        }
    }
}


int main() {
    int numero_nodi, numero_archi;
    inputFile >> numero_nodi >> numero_archi;
    // Lista di adiacenza per rappresentare il grafo
    vector<vector<int>> grafo(numero_nodi);
    for (int i = 0; i < numero_archi; ++i) {
        int s, a;
        inputFile >> s >> a;
        grafo[s].push_back(a);
    }

    // Inizializza il vettore per contare i nodi nei cicli e il bitmap per i nodi visitati
    //vector<bool> conteggio(numero_nodi, 1); // vector<bool>
    nodi_ciclo.reset();
    nodi_comuni.reset();
    vector<bool> visitati(numero_nodi, false);

    // Trova cicli
    trova_cicli(grafo, visitati);

    // Cerca il nodo con il numero di cicli uguale a `n_cicli` e stampa

    int index = nodi_comuni._Find_first();

    outputFile << index << endl;
    outputFile << ciclo.size() << " ";
    for (auto it = ciclo.rbegin(); it != ciclo.rend(); ++it) {
        outputFile << *it << " ";
    }
    outputFile << endl;
    return 0;
}