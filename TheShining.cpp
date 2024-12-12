#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int n_cicli = 0;
vector<int> ciclo;

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

        void getCycle(int n, vector<int> &conteggio) {
            ciclo.clear();
            for (int i = vec.size() - 1; i >= 0; --i) {
                ciclo.push_back(vec[i]);
                ++conteggio[vec[i]];
                if (vec[i] == n) break;
            }
            ++n_cicli;
        }
};

void trova_cicli(const vector<vector<int>> &grafo, vector<int> &conteggio, vector<bool> &visitati) {
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
                    stack.getCycle(vicino, conteggio);
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
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile) {
        cerr << "Errore: impossibile aprire il file di input" << endl;
        return -1;
    }

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
    vector<int> conteggio(numero_nodi, 0);
    vector<bool> visitati(numero_nodi, false);

    // Trova cicli
    trova_cicli(grafo, conteggio, visitati);

    // Cerca il nodo con il numero di cicli uguale a `n_cicli` e stampa
    for (int i = 0; i < conteggio.size(); ++i) {
        if (n_cicli == conteggio[i]) {
            outputFile << i << endl;
            outputFile << ciclo.size() << " ";
            for (auto it = ciclo.rbegin(); it != ciclo.rend(); ++it) {
                outputFile << *it << " ";
            }
            outputFile << endl;
            return 0;
        }
    }

    outputFile << "-1";
    return 0;
}