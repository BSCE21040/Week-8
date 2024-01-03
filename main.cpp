#include"function.h"

int main()
{
    initializeBoats();
    int currentHour = getCurrentHour();

    int choice;
    do {
        cout << "1. Calculate the money taken in a day for one boat\n";
        cout << "2. Find the next boat available\n";
        cout << "3. Calculate the money taken for all the boats at the end of the day\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            calculateMoneyForOneBoat(currentHour);
            break;
        case 2:
            findNextAvailableBoat(currentHour);
            break;
        case 3:
            calculateMoneyForAllBoats();
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 4);

	return 0;
}


