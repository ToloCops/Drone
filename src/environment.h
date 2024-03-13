#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Drone.h" // Includiamo il file header della classe Drone
#include <vector>

class Environment {
private:
    std::vector<Drone> drones; // Vettore di droni presenti nell'ambiente
    double areaWidth;           // Larghezza dell'area di sorveglianza
    double areaHeight;          // Altezza dell'area di sorveglianza

public:
    // Costruttore
    Environment(double width, double height);

    // Metodo per aggiungere un drone all'ambiente
    void addDrone(const Drone& drone);

    // Metodo per eseguire una simulazione
    void runSimulation();
};

#endif // ENVIRONMENT_H
