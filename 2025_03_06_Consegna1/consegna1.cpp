#include <fstream>
#include <iostream>
using namespace std;

// compilazione: g++ consegna1-loader.c
//

// Il programma carica il file data.txt contenente 100 righe con dati da ordinare in modo crescente
// ./a.out
// In output viene mostrato il numero di accessi in read alla memoria per eseguire il sorting di ciascuna riga

// Obiettivo:
// Creare un algoritmo di sorting che minimizzi la somma del numero di accessi per ogni sorting di ciascuna riga del file

int ct_read = 0;
int max_dim = 1000;
int ntests = 100;
int ndiv = 1;
int details = 0;
int graph = 0;

int n = 0; /// dimensione dell'array

void print_array(int *A, int dim) {
    for (int j = 0; j < dim; j++) {
        std::cout << A[j];
    }
    std::cout << std::endl;
}

/*
void isSorted(int arr[] , int n){
    for(int i = 0 ; i < n - 1 ; i++)
            std::cout << arr[i] << " ";
    std::cout << std::endl;
}
*/

int shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            ct_read++;
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                ct_read+=2;
            }

            arr[j] = temp;
        }
    }
    return 0;
}


int main(int argc, char **argv) {
    int i, test;
    int *A;
    int read_min = -1;;
    int read_max = 0;
    long read_avg = 0;

    ifstream input_data;
    std::ofstream output_file;

    /// allocazione array
    A = new int[max_dim];

    n = max_dim;

    input_data.open("data.txt");
    output_file.open("consegna1.txt");

    if (!input_data.is_open()) {
        std::cerr << "Errore nella lettura del file!" << std::endl;
        return 1;
    }

    if (!output_file.is_open()) {
        std::cerr << "Errore nella creazione del file!" << std::endl;
        return 1;
    }


    //// lancio ntests volte per coprire diversi casi di input random
    for (test = 0; test < ntests; test++) {

        /// inizializzazione array: numeri random con range dimensione array
        for (i = 0; i < n; i++) {
            char comma;
            input_data >> A[i];
            input_data >> comma;
        }

        if (details) {
            printf("caricato array di dimensione %d\n", n);
            print_array(A, n);
        }

        ct_read = 0;
        shellSort(A,1000);

        //isSorted(A,1000);

        if (details) {
            printf("Output:\n");
            print_array(A, n);
        }

        /// statistiche
        read_avg += ct_read;
        if (read_min < 0 || read_min > ct_read)
            read_min = ct_read;
        if (read_max < 0 || read_max < ct_read)
            read_max = ct_read;
        output_file << "Test n°" << test << " Numero letture: " << ct_read << std::endl;
    }

    output_file << "N° Test" << ntests <<  " Min: " << read_min << " Avg: "
                << (read_avg) / static_cast<long>(ntests) << " Max: " << read_max << std::endl;

    input_data.close();
    output_file.close();

    delete[] A;

    return 0;
}