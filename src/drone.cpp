#include <iostream>
#include <vector>

class Drone {
private:
    int id; // ID univoco del drone
    double batteryLevel; // Livello della batteria del drone (in percentuale)
    std::pair<double, double> position; // Posizione attuale del drone (coordinate x, y)
    bool isInFlight; // Flag che indica se il drone è in volo o meno

public:
    // Costruttore
    Drone(int id, double initialBatteryLevel, std::pair<double, double> initialPosition)
        : id(id), batteryLevel(initialBatteryLevel), position(initialPosition), isInFlight(false) {}

    // Metodo per ottenere l'ID del drone
    int getId() const { return id; }

    // Metodo per ottenere il livello della batteria del drone
    double getBatteryLevel() const { return batteryLevel; }

    // Metodo per ottenere la posizione attuale del drone
    std::pair<double, double> getPosition() const { return position; }

    // Metodo per verificare se il drone è in volo
    bool isFlying() const { return isInFlight; }

    // Metodo per far decollare il drone
    void takeOff() {
        if (!isFlying()) {
            std::cout << "Drone " << id << " taking off." << std::endl;
            isInFlight = true;
        } else {
            std::cout << "Drone " << id << " is already flying." << std::endl;
        }
    }

    // Metodo per far atterrare il drone
    void land() {
        if (isFlying()) {
            std::cout << "Drone " << id << " landing." << std::endl;
            isInFlight = false;
        } else {
            std::cout << "Drone " << id << " is already on the ground." << std::endl;
        }
    }

    // Metodo per muovere il drone verso una nuova posizione
    void moveTo(double x, double y) {
        if (isFlying()) {
            std::cout << "Drone " << id << " moving to position (" << x << ", " << y << ")." << std::endl;
            position = std::make_pair(x, y);
        } else {
            std::cout << "Drone " << id << " cannot move while on the ground." << std::endl;
        }
    }

    // Metodo per ricaricare la batteria del drone
    void recharge() {
        std::cout << "Drone " << id << " recharging." << std::endl;
        // Simulazione della ricarica della batteria
        batteryLevel = 100.0;
    }
};

