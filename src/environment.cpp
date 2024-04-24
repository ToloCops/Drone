#include "drone.h"
#include "environment.h"
#include "route.h"

#include <iostream>
#include <vector>
#include <cstdlib> // Per la generazione di numeri casuali
#include <ctime>   // Per l'inizializzazione del generatore di numeri casuali
#include <cmath>   // Per le operazioni matematiche
#include <random>

#define WRITE_STREAM "control_to_drones"

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

void Environment::generateRandomDrones(int numDrones) {
    std::mt19937 rng(std::time(nullptr)); // Generatore di numeri casuali
    std::uniform_real_distribution<double> batteryDist(20.0, 100.0); // Batteria da 20.0 a 100.0
    std::uniform_real_distribution<double> positionDist(0.0, areaWidth); // Posizione x da 0.0 a areaWidth
    std::uniform_real_distribution<double> positionDistY(0.0, areaHeight); // Posizione y da 0.0 a areaHeight

    for (int i = 0; i < numDrones; ++i) {
        int id = drones.size() + 1; // Id univoco per ogni drone
        double battery = batteryDist(rng);
        double speed = 30;
        double x = positionDist(rng);
        double y = positionDistY(rng);
        Drone newDrone(id, battery, speed, x, y);
        addDrone(newDrone); // Aggiunge il drone appena creato all'ambiente
    }
}

void Environment::status() {
    for (Drone& drone : drones) {
        printf("Drone %d: battery = %f, velocity = %f, position = (%f, %f)\n", drone.getId(), drone.getBattery(), drone.getSpeed(), drone.getPosition().first, drone.getPosition().second);
    }
    printf("%d, %d\n", numGridRows, numGridCols);
}

void Environment::runSimulation() {
    planSurveillance();
}

/*
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
}*/
/*
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
                printf("%f, %f\n", cellCenterX, cellCenterY);
                
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
}*/

void Environment::planSurveillance(){
    double control_center = 3000.0;
    int count_center = 0;
    int count_side = 0;
    for (int col = 0; col < numGridCols; ++col) {
        if (col % 4 != 0) {
            continue;
        }
        double cellCenterX = (col + 0.5) * surveillanceCellSize;
        double cellCenterY = 0.5 * surveillanceCellSize;
        printf("Colonna %d ", col);
        if (cellCenterX-control_center <= 1480.0 and cellCenterX-control_center >= -1480.0) {
            printf("centro\n");
            count_center++;
        }
        else {
            printf("lato\n");
            count_side++;
            Route route;
            for (int y = cellCenterY; y < areaHeight; y += 10) {
            route.addPoint(cellCenterX, y);
            }
            std::pair<int, int> p = route.getRoute().back();
            std::cout << "(" << p.first << ", " << p.second << ")" << std::endl;
        }
    }
    printf("Colonne centro: %d\n", count_center);
    printf("Colonne lato: %d\n", count_side);
}

void stampa_elementi(struct redisReply **element, size_t num_elementi) {
    for (size_t i = 0; i < num_elementi; ++i) {
        printf("Elemento %zu:\n", i);
        printf("  Type: %d\n", element[i]->type);
        printf("  Integer: %lld\n", element[i]->integer);
        printf("  Double: %f\n", element[i]->dval);
        printf("  Len: %zu\n", element[i]->len);
        printf("  String: %s\n", element[i]->str);
        printf("  VType: %s\n", element[i]->vtype);
        printf("  Elements: %zu\n", element[i]->elements);

        // Ricorsivamente stampa gli elementi, se è un array
        if (element[i]->type == REDIS_REPLY_ARRAY) {
            printf("  Elementi dell'array:\n");
            stampa_elementi(element[i]->element, element[i]->elements);
        }
    }
}


int main() {
    double areaWidth = 6000.0;
    double areaHeight = 6000.0;
    Environment environment(areaWidth, areaHeight);
    /*Drone drone1(1, 30.0, 30.0, 0, 0);
    environment.addDrone(drone1);
    Drone drone2(2, 22, 15, 5, 9);
    environment.addDrone(drone2);*/
    environment.generateRandomDrones(5);
    environment.status();
    environment.runSimulation();
    /*redisContext *c2r;
    redisReply *reply;
    int block = 1000000000;

    c2r = redisConnect("localhost", 6379);
    printf("main(): pid = %d: user %s: connected to redis\n", 3, "prova");

    reply = RedisCommand(c2r, "DEL %s", WRITE_STREAM);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    initStreams(c2r, WRITE_STREAM);

    reply = RedisCommand(c2r, "XADD %s * %s %s", WRITE_STREAM, "3", "ciao");
    assertReplyType(c2r, reply, REDIS_REPLY_STRING);
    printf("main(): pid = %d: stream %s: Added %s -> %s (id: %s)\n", 3, WRITE_STREAM, "3", "ciao", reply->str);
    freeReplyObject(reply);

    reply = RedisCommand(c2r, "XADD %s * %s %s", WRITE_STREAM, "5", "ok");
    assertReplyType(c2r, reply, REDIS_REPLY_STRING);
    printf("main(): pid = %d: stream %s: Added %s -> %s (id: %s)\n", drone1.getId(), WRITE_STREAM, "5", "ok", reply->str);
    freeReplyObject(reply);

    micro_sleep(1000000);

    environment.addDrone(drone1);
    reply = RedisCommand(c2r, "XREADGROUP GROUP diameter %s BLOCK %d COUNT 2 NOACK STREAMS %s >", "luca", block, WRITE_STREAM);
    assertReply(c2r, reply);
    stampa_elementi(reply->element, reply->elements);
    freeReplyObject(reply);
    environment.runSimulation();*/

    return 0;
}
