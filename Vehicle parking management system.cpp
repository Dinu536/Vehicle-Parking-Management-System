#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Vehicle {
protected:
    string licensePlate;
    int hoursParked;

public:
    Vehicle(string licensePlate, int hoursParked) {
        this->licensePlate = licensePlate;
        this->hoursParked = hoursParked;
    }

    virtual float calculateCharges() = 0;
};

class TwoWheeler : public Vehicle {
public:
    TwoWheeler(string licensePlate, int hoursParked) : Vehicle(licensePlate, hoursParked) {}

    float calculateCharges() {
        if (hoursParked <= 3) {
            return 20;
        } else {
            return 20 + (hoursParked - 3) * 5;
        }
    }
};

class ThreeWheeler : public Vehicle {
public:
    ThreeWheeler(string licensePlate, int hoursParked) : Vehicle(licensePlate, hoursParked) {}

    float calculateCharges() {
        if (hoursParked <= 3) {
            return 40;
        } else {
            return 40 + (hoursParked - 3) * 10;
        }
    }
};

class FourWheeler : public Vehicle {
public:
    FourWheeler(string licensePlate, int hoursParked) : Vehicle(licensePlate, hoursParked) {}

    float calculateCharges() {
        if (hoursParked <= 3) {
            return 50;
        } else {
            return 50 + (hoursParked - 3) * 15;
        }
    }
};

void display() {
    ifstream inFile("parking3.txt");
    if (!inFile) {
        cerr << "Error opening file" << endl;
        return;
    }

    string licensePlate;
    int hoursParked, vehicleType;
    float charges;

    cout << "License Plate\tHours Parked\tVehicle Type\tCharges" << endl;
    while (inFile >> licensePlate >> hoursParked >> vehicleType >> charges) {
        cout << licensePlate << "\t\t" << hoursParked << "\t\t" << vehicleType << "\t\t" << charges << endl;
    }

    inFile.close();
}

int main() {
    while (true) {
        cout << "1. Park a vehicle" << endl;
        cout << "2. Delete vehicle data" << endl;
        cout << "3. Display parking records" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string licensePlate;
                int hoursParked, vehicleType;

                cout << "Enter license plate number: ";
                cin >> licensePlate;
                cout << "Enter hours parked: ";
                cin >> hoursParked;
                cout << "Enter vehicle type (2 for two wheeler, 3 for three wheeler, 4 for four wheeler): ";
                cin >> vehicleType;

                Vehicle* vehicle;

                if (vehicleType == 2) {
                    vehicle = new TwoWheeler(licensePlate, hoursParked);
                } else if (vehicleType == 3) {
                    vehicle = new ThreeWheeler(licensePlate, hoursParked);
                } else if (vehicleType == 4) {
                    vehicle = new FourWheeler(licensePlate, hoursParked);
                } else {
                    cout << "Invalid vehicle type" << endl;
                    continue;
                }

                float charges = vehicle->calculateCharges();

                cout << "Charges for vehicle with license plate " << licensePlate << " is " << charges << endl;

                // Save vehicle data to file
                ofstream outFile("parking3.txt", ios::app);
                if (!outFile) {
                    cerr << "Error opening file" << endl;
                    return -1;
                }
                outFile << licensePlate << " " << hoursParked << " " << vehicleType << " " << charges << endl;
                outFile.close();

                break;
            }

            case 2: {
                // Delete vehicle data
                ofstream outFile("parking3.txt");
                if (!outFile) {
                    cerr << "Error opening file" << endl;
                    return -1;
                }
                outFile.close();

                cout << "Vehicle data deleted" << endl;

                break;
            }

            case 3: {
                // Display parking records
                display();

                break;
            }

            case 4:
                cout << "Exiting..." << endl;
                return 0;

            default:
                cout << "Invalid choice" << endl;
                break;
        }
    }

    return 0;
}

