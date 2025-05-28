#include "gardenLog.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <iomanip>
#include <sstream>

void GardenLog::loadAllPlants() {
    plants.clear();

    if (!std::filesystem::exists("data")) {
        std::filesystem::create_directory("data");
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator("data")) {
        if (entry.path().extension() == ".txt") {
            Plant p;
            std::string filename = entry.path().stem().string();
            p.loadFromFile(filename);
            plants.push_back(p);
        }
    }
}

void GardenLog::addPlant() {
    std::string name, native;
    double height;
    int age;

    std::cout << "Enter common name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter height (cm): ";
    std::cin >> height;
    std::cout << "Enter age (weeks): ";
    std::cin >> age;
    std::cin.ignore();
    std::cout << "Enter native area: ";
    std::getline(std::cin, native);

    Plant newPlant(name, height, age, native);

    std::string latin, care, growth;
    std::cout << "Enter Latin name (optional): ";
    std::getline(std::cin, latin);
    newPlant.setLatinName(latin);

    std::cout << "Enter care instructions (optional): ";
    std::getline(std::cin, care);
    newPlant.setCareInstructions(care);

    std::cout << "Enter growth expectations (optional): ";
    std::getline(std::cin, growth);
    newPlant.setGrowthExpectations(growth);

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    newPlant.setDateEntered(oss.str());

    newPlant.saveToFile();
    plants.push_back(newPlant);
}

void GardenLog::displayPlants() const {
    for (const auto& plant : plants) {
        plant.displayInfo();
    }
}

void GardenLog::logActivity() {
    std::string name;
    std::cout << "Enter plant name to log activity for: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    for (auto& plant : plants) {
        if (plant.getCommonName() == name) {
            int choice;
            std::cout << "1. Log watering\n2. Log feeding\nChoice: ";
            std::cin >> choice;
            std::cin.ignore();

            std::string date;
            std::cout << "Enter date (e.g., 2025-05-27): ";
            std::getline(std::cin, date);

            if (choice == 1) {
                std::string amount;
                std::cout << "How much water was used (e.g., 500ml)? ";
                std::getline(std::cin, amount);
                plant.logWatering(date + " - " + amount);

                std::string feedChoice;
                std::cout << "Did you also feed the plant? (y/n): ";
                std::getline(std::cin, feedChoice);

                if (feedChoice == "y" || feedChoice == "Y") {
                    std::string feedType;
                    std::cout << "Type of feeding - (1) Top dress or (2) Liquid solution? ";
                    std::getline(std::cin, feedType);
                    std::string feedDesc = (feedType == "1") ? "Top dress" : "Liquid solution";
                    plant.logFeeding(date + " - " + feedDesc);
                }
            } else if (choice == 2) {
                std::string feedType;
                std::cout << "Type of feeding - (1) Top dress or (2) Liquid solution? ";
                std::getline(std::cin, feedType);
                std::string feedDesc = (feedType == "1") ? "Top dress" : "Liquid solution";
                plant.logFeeding(date + " - " + feedDesc);
            }

            plant.saveToFile();
            return;
        }
    }

    std::cout << "Plant not found.\n";
}

void GardenLog::showReminders() const {
    std::cout << "\n--- Reminders ---\n";
    for (const auto& plant : plants) {
        std::string reminder = plant.getReminder();
        if (!reminder.empty()) {
            std::cout << reminder;
        }
    }
}

void GardenLog::exportSummaryLog() const {
    std::ofstream outFile("Garden_Summary_Log.txt");
    if (!outFile.is_open()) {
        std::cerr << "Failed to write summary log.\n";
        return;
    }

    for (const auto& plant : plants) {
        outFile << "--------------------------\n";
        outFile << "Name: " << plant.getCommonName() << "\n";
        outFile << "Age: " << plant.getDateEntered() << "\n";
        outFile << "Date Entered: " << plant.getDateEntered() << "\n";
        outFile << "Last Watered: " << (plant.getReminder().find("watering") == std::string::npos ? "✓" : "No record") << "\n";
    }

    outFile << "--------------------------\n";
    outFile.close();
    std::cout << "Summary exported to Garden_Summary_Log.txt\n";
}

void GardenLog::deletePlant() {
    std::string name;
    std::cout << "Enter plant name to delete: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::filesystem::path filePath = "data/" + name + ".txt";
    if (std::filesystem::exists(filePath)) {
        std::filesystem::remove(filePath);
        std::cout << "Deleted " << name << " from records.\n";
        loadAllPlants();
    } else {
        std::cout << "Plant not found.\n";
    }
}
