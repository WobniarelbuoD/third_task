#include <iostream>

using namespace std;

int mainMenu() {
    int choice;

    cout << "\n--- Dviraciu parduotuvės užsakymas ---\n";
    cout << "1. Peržiūreti visas prekes\n";
    cout << "2. Peržiūreti pasirinktos kategorijos prekes\n";
    cout << "3. Peržiūreti užsakymo suma\n";
    cout << "4. Peržiūreti sumas pagal kategorijas\n";
    cout << "5. Parodyti visą užsakymo ataskaitą\n";
    cout << "6. Išsaugoti visą ataskaitą į failą\n";
    cout << "7. Išeiti\n";
    cout << "Pasirinkimas: ";

    cin >> choice;

    return choice;
}

int main() {
    int choice;

    do {
        choice = mainMenu();

        switch (choice) {
            case 1:
                cout << "Visos prekės\n";
                break;

            case 2:
                cout << "Prekės pagal kategorija\n";
                break;

            case 3:
                cout << "Užsakymo suma\n";
                break;

            case 4:
                cout << "Suma pagal kategorija\n";
                break;

            case 5:
                cout << "Ataskaita\n";
                break;

            case 6:
                cout << "Ataskaitos išsaugojimas\n";
                break;

            case 7:
                cout << "Programa baigta.\n";
                break;

            default:
                cout << "Neteisingas pasirinkimas.\n";
                break;
        }

    } while (choice != 7);

    return 0;
}