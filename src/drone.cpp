#include <iostream>
#include <vector>
#include "environment.h"
#include "drone.h"


// Implementazioni dei metodi della classe Drone

// Costruttore
Drone::Drone(int id, double battery, double speed, double x, double y)
    : id(id), battery(battery), speed(speed), position(std::make_pair(x, y)) {}

int Drone::getId() const { return id; }

double Drone::getBattery() const { return battery; }

double Drone::getSpeed() const { return speed; }

// Metodo per ottenere la posizione attuale del drone
std::pair<double, double> Drone::getPosition() const { return position; }

// Metodo per muovere il drone verso una nuova posizione
void Drone::moveTo(double x, double y) {
    position = std::make_pair(x, y);
}

