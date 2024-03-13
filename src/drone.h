#ifndef DRONE_H
#define DRONE_H

#include <iostream>
#include <utility>

class Drone {
private:
    int id; // ID univoco del drone
    double batteryLevel; // Livello della batteria del drone (in percentuale)
    std::pair<double, double> position; // Posizione attuale del drone (coordinate x, y)
    bool isInFlight; // Flag che indica se il drone è in volo o meno

public:
    // Costruttore
    Drone(int id, double initialBatteryLevel, std::pair<double, double> initialPosition);

    // Metodo per ottenere l'ID del drone
    int getId() const;

    // Metodo per ottenere il livello della batteria del drone
    double getBatteryLevel() const;

    // Metodo per ottenere la posizione attuale del drone
    std::pair<double, double> getPosition() const;

    // Metodo per verificare se il drone è in volo
    bool isFlying() const;

    // Metodo per far decollare il drone
    void takeOff();

    // Metodo per far atterrare il drone
    void land();

    // Metodo per muovere il drone verso una nuova posizione
    void moveTo(double x, double y);

    // Metodo per ricaricare la batteria del drone
    void recharge();
};

#endif // DRONE_H
