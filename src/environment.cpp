#include <iostream>
#include <vector>
#include <cstdlib> // Per la generazione di numeri casuali
#include <ctime>   // Per l'inizializzazione del generatore di numeri casuali
#include "drone.h"

class Environment {
private:
    std::vector<Drone> drones; // Vettore di droni presenti nell'ambiente
    double areaWidth;           // Larghezza dell'area di sorveglianza
    double areaHeight;          // Altezza dell'area di sorveglianza

public:
    // Costruttore
    Environment(double width, double height) : areaWidth(width), areaHeight(height) {
        // Inizializza il generatore di numeri casuali con il tempo corrente
        srand(time(nullptr));
    }

    // Metodo per aggiungere un drone all'ambiente
    void addDrone(const Drone& drone) {
        drones.push_back(drone);
    }

    // Metodo per eseguire una simulazione
    void runSimulation() {
        // Eseguiamo la simulazione per un numero arbitrario di passi
        for (int i = 0; i < 10; ++i) {
            // Per ogni drone, eseguiamo un'azione casuale
            for (Drone& drone : drones) {
                // Dichiarazione delle variabili x e y all'esterno del switch
                double x, y;
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
                        // Assegniamo i valori di x e y prima del case
                        x = (rand() / (double)RAND_MAX) * areaWidth;
                        y = (rand() / (double)RAND_MAX) * areaHeight;
                        // Muoviamo il drone in una posizione casuale nell'area di sorveglianza
                        drone.moveTo(x, y);
                        break;
                    case 3:
                        drone.recharge();
                        break;
                }
            }
        }
    }
};

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
