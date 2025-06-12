//
// Created by Jeff on 5/27/2025.
// Finished 6/11/25
//

#include "plant.h"
#include <iostream>
#include <fstream>
#include <filesystem>

Plant::Plant() {}

Plant::Plant(const std::string& name, double h, int a, const std::string& native)
    : commonName(name), height(h), age(a), nativeArea(native) {}

void Plant::setLatinName(const std::string& name) {
    latinName = name;
}

void Plant::setCareInstructions(const std::string& instructions) {
    careInstructions = instructions;
}

void Plant::setGrowthExpectations(const std::string& expectations) {
    growthExpectations = expectations;
}

void Plant::setDateEntered(const std::string& date) {
    dateEntered = date;
}

void Plant::logWatering(const std::string& entry) {
    lastWatered = entry;
}

void Plant::logFeeding(const std::string& entry) {
    lastFed = entry;
}

std::string Plant::getReminder() const {
    std::string reminder;
    if (lastWatered.empty()) reminder += "- " + commonName + " needs watering log.\n";
    if (lastFed.empty()) reminder += "- " + commonName + " needs feeding log.\n";
    return reminder;
}

void Plant::displayInfo() const {
    std::cout << "\n--- Plant Info ---\n";
    std::cout << "Common Name: " << commonName << "\n";
    std::cout << "Latin Name: " << latinName << "\n";
    std::cout << "Native Area: " << nativeArea << "\n";
    std::cout << "Height: " << height << " cm\n";
    std::cout << "Age: " << age << " weeks\n";
    std::cout << "Date Entered: " << dateEntered << "\n";
    std::cout << "Care: " << careInstructions << "\n";
    std::cout << "Growth: " << growthExpectations << "\n";
    std::cout << "Last Watered: " << lastWatered << "\n";
    std::cout << "Last Fed: " << lastFed << "\n";
}

std::string Plant::getCommonName() const {
    return commonName;
}

std::string Plant::getDateEntered() const {
    return dateEntered;
}

void Plant::saveToFile() const {
    std::filesystem::create_directory("data");
    std::ofstream file("data/" + commonName + ".txt");
    if (file.is_open()) {
        file << commonName << "\n" << latinName << "\n" << nativeArea << "\n";
        file << height << "\n" << age << "\n";
        file << careInstructions << "\n" << growthExpectations << "\n";
        file << dateEntered << "\n";
        file << lastWatered << "\n" << lastFed << "\n";
        file.close();
    }
}

void Plant::loadFromFile(const std::string& name) {
    std::ifstream file("data/" + name + ".txt");
    if (file.is_open()) {
        std::getline(file, commonName);
        std::getline(file, latinName);
        std::getline(file, nativeArea);
        file >> height;
        file >> age;
        file.ignore();
        std::getline(file, careInstructions);
        std::getline(file, growthExpectations);
        std::getline(file, dateEntered);
        std::getline(file, lastWatered);
        std::getline(file, lastFed);
        file.close();
    }
}
