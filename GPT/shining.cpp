#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Algoritmo di Johnson per trovare tutti i cicli semplici in un grafo
class JohnsonCycles {
    vector<vector<int>> grafo;
    vector<bool> blocco;
    vector<vector<int>> B;
    vector<int> percorso;
    vector<vector<int>> cicli;

    void sblocca(int nodo) {
        blocco[nodo] = false;
        for (int w : B[nodo]) {
            if (blocco[w]) {
                sblocca(w);
            }
        }
        B[nodo].clear();
    }

    bool trova_ciclo(int v, int start) {
        bool trovato = false;
        percorso.push_back(v);
        blocco[v] = true; // visitato

        for (int w : grafo[v]) {
            if (w == start) {
                percorso.push_back(w);
                cicli.push_back(percorso);
                percorso.pop_back();
                trovato = true;
            } else if (!blocco[w]) {
                if (trova_ciclo(w, start)) {
                    trovato = true;
                }
            }
        }

        if (trovato) {
            sblocca(v);
        } else { // se il corridio è bloccato
            for (int w : grafo[v]) {
                if (find(B[w].begin(), B[w].end(), v) == B[w].end()) {
                    B[w].push_back(v);
                }
            }
        }

        percorso.pop_back();
        return trovato;
    }

public:
    JohnsonCycles(const vector<vector<int>> &grafo) : grafo(grafo) {
        int n = grafo.size();
        blocco.resize(n, false);
        B.resize(n);
    }

    vector<vector<int>> trova_cicli() {
        int n = grafo.size();
        for (int start = 0; start < n; ++start) {
            trova_ciclo(start, start);
            blocco[start] = true;
        }
        return cicli;
    }
};

void stampa_cicli(const vector<vector<int>> &cicli) {
    cout << "Cicli trovati nel grafo:" << endl;
    for (const auto &ciclo : cicli) {
        for (int nodo : ciclo) {
            cout << nodo << " ";
        }
        cout << endl;
    }
}

int trova_nodo_comune(const vector<vector<int>> &cicli) {
    if (cicli.empty()) {
        return -1;
    }

    // Inizializza l'intersezione con il primo ciclo
    unordered_set<int> comuni(cicli[0].begin(), cicli[0].end());

    // Trova l'intersezione con gli altri cicli
    for (int i = 1; i < cicli.size(); ++i) { // per me non è efficiente così
        unordered_set<int> intersezione;
        for (int nodo : cicli[i]) {
            if (comuni.find(nodo) != comuni.end()) {
                intersezione.insert(nodo);
            }
        }
        comuni = move(intersezione);

        // Se l'intersezione è vuota, possiamo interrompere presto
        if (comuni.empty()) {
            return -1;
        }
    }

    // Ritorna un nodo comune qualsiasi, se esiste
    return comuni.empty() ? -1 : *comuni.begin();
}

int main() {
    int numero_nodi, numero_archi;

    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    inputFile >> numero_nodi >> numero_archi;
    vector<vector<int>> grafo(numero_nodi);
    int s, a;
    for (int i = 0; i < numero_archi; ++i) {
        inputFile >> s >> a;
        grafo[s].push_back(a);
    }

    JohnsonCycles jc(grafo);
    auto cicli = jc.trova_cicli();

    //stampa_cicli(cicli);

    int nodo_comune=trova_nodo_comune(cicli);

    cout<<nodo_comune<<endl;

    outputFile<<nodo_comune;



    return 0;
}