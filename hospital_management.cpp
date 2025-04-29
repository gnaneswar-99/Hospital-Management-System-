#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Structure to hold patient details
struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string disease;
};

class HospitalManagement {
private:
    vector<Patient> patients;
    int nextId = 1;

    void loadPatients() {
        ifstream fin("patients.txt");
        if (!fin) return;

        Patient p;
        while (fin >> p.id) {
            fin.ignore();
            getline(fin, p.name);
            fin >> p.age >> p.gender;
            fin.ignore();
            getline(fin, p.disease);
            patients.push_back(p);
            if (p.id >= nextId) nextId = p.id + 1;
        }
        fin.close();
    }

    void savePatients() {
        ofstream fout("patients.txt");
        for (auto& p : patients) {
            fout << p.id << endl
                 << p.name << endl
                 << p.age << " " << p.gender << endl
                 << p.disease << endl;
        }
        fout.close();
    }

public:
    HospitalManagement() {
        loadPatients();
    }

    ~HospitalManagement() {
        savePatients();
    }

    void addPatient() {
        Patient newPatient;
        newPatient.id = nextId++;
        cout << "\nEnter Patient Name: ";
        cin.ignore();
        getline(cin, newPatient.name);
        cout << "Enter Age: ";
        cin >> newPatient.age;
        cout << "Enter Gender: ";
        cin >> newPatient.gender;
        cout << "Enter Disease: ";
        cin.ignore();
        getline(cin, newPatient.disease);

        patients.push_back(newPatient);
        cout << "\nPatient Registered Successfully! Patient ID: " << newPatient.id << "\n";
    }

    void viewPatients() {
        if (patients.empty()) {
            cout << "\nNo patients registered yet.\n";
            return;
        }

        cout << "\nList of Registered Patients:\n";
        cout << "----------------------------------------\n";
        for (const auto& patient : patients) {
            cout << "ID: " << patient.id
                 << " | Name: " << patient.name
                 << " | Age: " << patient.age
                 << " | Gender: " << patient.gender
                 << " | Disease: " << patient.disease << "\n";
        }
        cout << "----------------------------------------\n";
    }

    void searchPatientById() {
        int id;
        cout << "\nEnter Patient ID to search: ";
        cin >> id;
        for (const auto& patient : patients) {
            if (patient.id == id) {
                cout << "\nPatient Found:\n";
                cout << "Name: " << patient.name
                     << " | Age: " << patient.age
                     << " | Gender: " << patient.gender
                     << " | Disease: " << patient.disease << "\n";
                return;
            }
        }
        cout << "\nPatient with ID " << id << " not found.\n";
    }

    void deletePatient() {
        int id;
        cout << "\nEnter Patient ID to delete: ";
        cin >> id;
        for (auto it = patients.begin(); it != patients.end(); ++it) {
            if (it->id == id) {
                patients.erase(it);
                cout << "\nPatient deleted successfully.\n";
                return;
            }
        }
        cout << "\nPatient with ID " << id << " not found.\n";
    }

    void updatePatient() {
        int id;
        cout << "\nEnter Patient ID to update: ";
        cin >> id;
        for (auto& patient : patients) {
            if (patient.id == id) {
                cout << "\nUpdating details for " << patient.name << "\n";
                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin, patient.name);
                cout << "Enter New Age: ";
                cin >> patient.age;
                cout << "Enter New Gender: ";
                cin >> patient.gender;
                cout << "Enter New Disease: ";
                cin.ignore();
                getline(cin, patient.disease);
                cout << "\nPatient details updated successfully.\n";
                return;
            }
        }
        cout << "\nPatient with ID " << id << " not found.\n";
    }
};

int main() {
    HospitalManagement hm;
    int choice;

    do {
        cout << "\n=== Hospital Management System ===\n";
        cout << "1. Register New Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Search Patient by ID\n";
        cout << "4. Delete Patient by ID\n";
        cout << "5. Update Patient Details\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hm.addPatient();
                break;
            case 2:
                hm.viewPatients();
                break;
            case 3:
                hm.searchPatientById();
                break;
            case 4:
                hm.deletePatient();
                break;
            case 5:
                hm.updatePatient();
                break;
            case 6:
                cout << "\nThank you for using Hospital Management System!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
