#ifndef DRONE_H
#define DRONE_H

#include <iostream>
#include <utility>

class Drone {
private:
    int id;
    double battery; // minutes
    double speed; // km/h
    std::pair<double, double> position; // (x, y)

public:
    // Constructor
    Drone(int id, double battery, double speed, double x, double y);

    //Getters

    int getId() const;

    double getBattery() const;

    double getSpeed() const;

    std::pair<double, double> getPosition() const;

    //Updaters

    void moveTo(double x, double y);
};

#endif // DRONE_H
