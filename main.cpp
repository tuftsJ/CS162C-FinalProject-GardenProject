#include "gardenLog.h"
#include <iostream>

int main() {
    GardenLog myGarden;
    myGarden.loadAllPlants();

    int choice;
    do {
        std::cout << "\n--- Garden Log Menu ---\n";
        std::cout << "1. Add Plant\n";
        std::cout << "2. Display Plants\n";
        std::cout << "3. Log Activity\n";
        std::cout << "4. Show Reminders\n";
        std::cout << "5. Export Plant Summary Log\n";
        std::cout << "6. Delete Plant\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: myGarden.addPlant(); break;
            case 2: myGarden.displayPlants(); break;
            case 3: myGarden.logActivity(); break;
            case 4: myGarden.showReminders(); break;
            case 5: myGarden.exportSummaryLog(); break;
            case 6: myGarden.deletePlant(); break;
            case 7: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice.\n"; break;
        }
    } while (choice != 7);

    return 0;
}
