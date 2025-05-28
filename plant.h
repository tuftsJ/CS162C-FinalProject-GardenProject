#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant {
private:
    std::string commonName;
    std::string latinName;
    std::string nativeArea;
    double height;
    int age;
    std::string careInstructions;
    std::string growthExpectations;
    std::string dateEntered;
    std::string lastWatered;
    std::string lastFed;

public:
    Plant();
    Plant(const std::string& name, double height, int age, const std::string& nativeArea);

    void setLatinName(const std::string& name);
    void setCareInstructions(const std::string& instructions);
    void setGrowthExpectations(const std::string& expectations);
    void setDateEntered(const std::string& date);

    void logWatering(const std::string& entry);
    void logFeeding(const std::string& entry);

    std::string getReminder() const;
    void displayInfo() const;

    std::string getCommonName() const;
    std::string getDateEntered() const;

    void saveToFile() const;
    void loadFromFile(const std::string& name);
};

#endif
