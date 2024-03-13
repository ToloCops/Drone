#include "drone.h"
#include "environment.h"

#include <iostream>
#include <vector>
#include <cstdlib> // Per la generazione di numeri casuali
#include <ctime>   // Per l'inizializzazione del generatore di numeri casuali
#include <cmath>   // Per le operazioni matematiche

// Implementazioni dei metodi della classe Environment

// Costruttore
Environment::Environment(double width, double height) : areaWidth(width), areaHeight(height) {
    // Inizializza il generatore di numeri casuali con il tempo corrente
    srand(time(nullptr));

    // Calcola il numero di righe e colonne della griglia di sorveglianza
    numGridRows = static_cast<int>(std::ceil(areaHeight / surveillanceCellSize));
    numGridCols = static_cast<int>(std::ceil(areaWidth / surveillanceCellSize));

    // Inizializza la griglia di sorveglianza
    lastSurveillanceTime.resize(numGridRows, std::vector<std::chrono::system_clock::time_point>(numGridCols));
}

// Metodo per aggiungere un drone all'ambiente
void Environment::addDrone(const Drone& drone) {
    drones.push_back(drone);
}

// Metodo per eseguire una simulazione
void Environment::runSimulation() {
    double x, y;
    // Eseguiamo la simulazione per un numero arbitrario di passi
    for (int i = 0; i < numSimulationSteps; ++i) {
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

        // Pianifica le prossime sorveglianze
        planSurveillance();
        // Attendi un intervallo di tempo (es. 5 minuti)
        std::this_thread::sleep_for(std::chrono::minutes(5));
    }
}

// Metodo per pianificare le sorveglianze
void Environment::planSurveillance() {
    // Itera su ogni cella della griglia di sorveglianza
    for (int row = 0; row < numGridRows; ++row) {
        for (int col = 0; col < numGridCols; ++col) {
            // Verifica se è necessaria una nuova sorveglianza per questa cella
            auto currentTime = std::chrono::system_clock::now();
            if (currentTime - lastSurveillanceTime[row][col] >= std::chrono::minutes(5)) {
                // Calcola le coordinate del centro della cella
                double cellCenterX = (col + 0.5) * surveillanceCellSize;
                double cellCenterY = (row + 0.5) * surveillanceCellSize;

                // Invia istruzioni ai droni per muoversi verso il centro della cella
                for (Drone& drone : drones) {
                    double droneX, droneY;
                    std::tie(droneX, droneY) = drone.getPosition();
                    double distanceToCellCenter = std::sqrt(std::pow(droneX - cellCenterX, 2) + std::pow(droneY - cellCenterY, 2));
                    if (distanceToCellCenter <= surveillanceRadius) {
                        // Il drone è già vicino al centro della cella, segna il punto come sorvegliato
                        lastSurveillanceTime[row][col] = currentTime;
                        break;
                    } else {
                        // Muove il drone verso il centro della cella
                        drone.moveTo(cellCenterX, cellCenterY);
                    }
                }
            }
        }
    }
}


int main() {
    Environment environment(100.0, 100.0);
    Drone drone1(1, 50.0, std::make_pair(0.0, 0.0));
    environment.addDrone(drone1);
    environment.runSimulation();

    return 0;
}
