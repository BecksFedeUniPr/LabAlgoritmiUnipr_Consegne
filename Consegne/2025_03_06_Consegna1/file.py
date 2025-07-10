import matplotlib.pyplot as plt
import numpy as np
import os

# Configurazione
FILE_PATH = 'data.txt'  # Sostituisci con il percorso del tuo file
NUM_RIGHE = 100
NUM_COLONNE = 1000

try:
    # Legge il file
    with open(FILE_PATH, 'r') as file:
        lines = file.readlines()
        print(f"File letto con successo. Trovate {len(lines)} righe.")
        
        dati = []
        for line in lines[:NUM_RIGHE]:
            # Rimuove spazi e divide per virgole
            valori = line.strip().replace(" ", "").split(',')
            # Converte in float (gestisce anche numeri interi)
            try:
                valori = [float(x) for x in valori if x]  # Ignora valori vuoti
                if len(valori) == NUM_COLONNE:
                    dati.append(valori)
                else:
                    print(f"Attenzione: riga con {len(valori)} colonne invece di {NUM_COLONNE}")
            except ValueError as e:
                print(f"Errore conversione riga: {e}")
                continue
        
        dati = np.array(dati)
        print(f"Dimensioni dati convertiti: {dati.shape}")
        
        if dati.size == 0:
            print("Nessun dato valido da plottare")
            exit()
        
        # Plot delle prime 10 righe
        plt.figure(figsize=(12, 6))
        for i in range(min(10, dati.shape[0])):
            plt.plot(dati[i], label=f'Riga {i+1}')
        
        plt.title(f'Prime {min(10, dati.shape[0])} righe su {dati.shape[0]} ({NUM_COLONNE} punti ciascuna)')
        plt.xlabel('Indice colonna')
        plt.ylabel('Valore')
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.show()

except FileNotFoundError:
    print(f"Errore: File '{FILE_PATH}' non trovato")
    print("Percorso corrente:", os.path.abspath('.'))  # Mostra dove sta cercando
except Exception as e:
    print(f"Errore durante l'esecuzione: {str(e)}")