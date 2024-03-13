#include "drone.h"
#include "environment.h"

#include <iostream>
#include <vector>
#include <cstdlib> // Per la generazione di numeri casuali
#include <ctime>   // Per l'inizializzazione del generatore di numeri casuali

// Implementazioni dei metodi della classe Environment

// Costruttore
Environment::Environment(double width, double height) : areaWidth(width), areaHeight(height) {
    // Inizializza il generatore di numeri casuali con il tempo corrente
    srand(time(nullptr));
}

// Metodo per aggiungere un drone all'ambiente
void Environment::addDrone(const Drone& drone) {
    drones.push_back(drone);
}

// Metodo per eseguire una simulazione
void Environment::runSimulation() {
    double x, y; // Dichiarazione delle variabili all'inizio della funzione

    // Eseguiamo la simulazione per un numero arbitrario di passi
    for (int i = 0; i < 10; ++i) {
        // Per ogni drone, eseguiamo un'azione casuale
        for (Drone& drone : drones) {
            int action = rand() % 4; // Generiamo un numero casuale da 0 a 3

            // Eseguiamo un'azione casuale sul drone
            switch (action) {
                case 0:
                    drone.takeOff();
                    break;
                case 1:
                    drone.land();
                    break;
                case 2:
                    // Muoviamo il drone in una posizione casuale nell'area di sorveglianza
                    x = (rand() / (double)RAND_MAX) * areaWidth;
                    y = (rand() / (double)RAND_MAX) * areaHeight;
                    drone.moveTo(x, y);
                    break;
                case 3:
                    drone.recharge();
                    break;
            }
        }
    }
}




int main() {
    // Creiamo un'istanza dell'ambiente con un'area di sorveglianza di 100x100
    Environment environment(100.0, 100.0);

    // Creiamo alcuni droni e li aggiungiamo all'ambiente
    Drone drone1(1, 50.0, std::make_pair(0.0, 0.0));
    Drone drone2(2, 75.0, std::make_pair(50.0, 50.0));
    environment.addDrone(drone1);
    environment.addDrone(drone2);

    // Eseguiamo la simulazione
    environment.runSimulation();

    return 0;
}
