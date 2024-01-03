#include<iostream>
#include <iomanip>
using namespace std;

const int NUM_BOATS = 10;
const int OPEN_HOUR = 10;
const int CLOSE_HOUR = 17;
const double HOURLY_RATE = 20.0;
const double HALF_HOUR_RATE = 12.0;

struct Boat {
    bool available;
    double moneyTaken;
    int totalHoursHired;
    int returnTime;
};

Boat boats[NUM_BOATS];

int getCurrentHour() {
    int currentHour;
    cout << "Enter the current hour (between 10 and 17): ";
    cin >> currentHour;

    while (currentHour < OPEN_HOUR || currentHour > CLOSE_HOUR) {
        cout << "Invalid hour. Please enter a valid hour between 10 and 17: ";
        cin >> currentHour;
    }

    return currentHour;
}

void initializeBoats() {
    for (int i = 0; i < NUM_BOATS; ++i) {
        boats[i].available = true;
        boats[i].moneyTaken = 0.0;
        boats[i].totalHoursHired = 0;
        boats[i].returnTime = OPEN_HOUR;
    }
}

void calculateMoneyAndHours(int boatIndex, int duration) {
    double rate = (duration == 1) ? HOURLY_RATE : HALF_HOUR_RATE;

    boats[boatIndex].moneyTaken += rate * duration;
    boats[boatIndex].totalHoursHired += duration;
}

void calculateMoneyForOneBoat(int currentHour) {
    int boatIndex;

    cout << "Enter the boat number (1 to 10): ";
    cin >> boatIndex;

    while (boatIndex < 1 || boatIndex > NUM_BOATS) {
        cout << "Invalid boat number. Please enter a valid boat number between 1 and 10: ";
        cin >> boatIndex;
    }

    if (!boats[boatIndex - 1].available) {
        cout << "Boat " << boatIndex << " is not available until " << boats[boatIndex - 1].returnTime << ":00.\n";
        return;
    }

    int duration;
    cout << "Enter the duration (1 for one hour, 0.5 for half an hour): ";
    cin >> duration;

    while (duration != 1 && duration != 0.5) {
        cout << "Invalid duration. Please enter 1 for one hour or 0.5 for half an hour: ";
        cin >> duration;
    }

    int returnTime = currentHour + (duration == 1 ? 1 : 0.5);

    if (returnTime > CLOSE_HOUR) {
        cout << "Boat must be returned before 17:00. Cannot hire for this duration.\n";
        return;
    }

    boats[boatIndex - 1].available = false;
    boats[boatIndex - 1].returnTime = returnTime;

    calculateMoneyAndHours(boatIndex - 1, duration);
}

void findNextAvailableBoat(int currentHour) {
    int earliestReturnTime = CLOSE_HOUR + 1;

    for (int i = 0; i < NUM_BOATS; ++i) {
        if (boats[i].returnTime < earliestReturnTime) {
            earliestReturnTime = boats[i].returnTime;
        }
    }

    if (earliestReturnTime <= currentHour) {
        cout << "No boats are available. The next available boat will be at " << earliestReturnTime << ":00.\n";
    }
    else {
        cout << "All boats are available at the current time.\n";
    }
}

void calculateMoneyForAllBoats() {
    double totalMoney = 0.0;
    int totalHoursHired = 0;
    int boatsNotUsed = 0;
    int mostUsedBoatIndex = 0;

    for (int i = 0; i < NUM_BOATS; ++i) {
        totalMoney += boats[i].moneyTaken;
        totalHoursHired += boats[i].totalHoursHired;

        if (boats[i].totalHoursHired == 0) {
            ++boatsNotUsed;
        }

        if (boats[i].totalHoursHired > boats[mostUsedBoatIndex].totalHoursHired) {
            mostUsedBoatIndex = i;
        }
    }

    cout << fixed << setprecision(2);
    cout << "Total money taken for all boats: $" << totalMoney << endl;
    cout << "Total number of hours boats were hired: " << totalHoursHired << " hours\n";
    cout << "Number of boats not used today: " << boatsNotUsed << endl;
    cout << "Boat " << mostUsedBoatIndex + 1 << " was used the most with " << boats[mostUsedBoatIndex].totalHoursHired << " hours.\n";
}

