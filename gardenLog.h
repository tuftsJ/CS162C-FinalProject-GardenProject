//
// Created by Jeff on 5/27/2025.
// Finished 6/11/25

#ifndef GARDENLOG_H
#define GARDENLOG_H

#include "plant.h"
#include <vector>

class GardenLog {
private:
    std::vector<Plant> plants;

public:
    void loadAllPlants();
    void addPlant();
    void displayPlants() const;
    void logActivity();
    void showReminders() const;
    void exportSummaryLog() const;
    void deletePlant();
};

#endif

