#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "drone.h" // Includiamo il file header della classe Drone
#include "con2redis.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <chrono>
#include <thread>

class Environment {
private:
    std::vector<Drone> drones; // Vettore di droni presenti nell'ambiente
    double areaWidth;           // Larghezza dell'area di sorveglianza
    double areaHeight;          // Altezza dell'area di sorveglianza
    int numGridRows;            // Numero di righe della griglia di sorveglianza
    int numGridCols;            // Numero di colonne della griglia di sorveglianza
    const double surveillanceCellSize = 10.0; // Dimensione di ogni cella della griglia di sorveglianza
    const double surveillanceRadius = 10.0;  // Raggio di sorveglianza attorno al centro della cella
    const int numSimulationSteps = 10; // Numero di passi di simulazione

    // Griglia di sorveglianza con i tempi delle ultime sorveglianze
    std::vector<std::vector<std::chrono::system_clock::time_point>> lastSurveillanceTime;

public:
    // Costruttore
    Environment(double width, double height);

    // Metodo per aggiungere un drone all'ambiente
    void addDrone(const Drone& drone);

    void generateRandomDrones(int numDrones);

    void status();

    // Metodo per eseguire una simulazione
    void runSimulation();

private:
    // Metodo per pianificare le sorveglianze
    void planSurveillance();
};

int micro_sleep(long usec);

#endif // ENVIRONMENT_H

