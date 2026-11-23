#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;

//Functions
void mainMenu(int choice);
int mainMenuChoice();
bool readFile(string categories[], string names[], double prices[], int quantities[], int &index);
int getNumber();


int main() {
    int choice;
    int index = 0;
    string categories[100];
    string names[100];
    double prices[100];
    int quantities[100];

    if (!readFile(categories, names, prices, quantities, index)) {
        return 0;
    }


    while (true) {
        choice = mainMenuChoice();
        mainMenu(choice);

        if (choice == 7) {
            break;
        }
    }

    return 0;
}

void mainMenu(int choice) {

    switch (choice) {
        case 1:
            cout << "Visos prekes\n";
            break;

        case 2:
            cout << "Prekes pagal kategorija\n";
            break;

        case 3:
            cout << "Uzsakymo suma\n";
            break;

        case 4:
            cout << "Suma pagal kategorija\n";
            break;

        case 5:
            cout << "Ataskaita\n";
            break;

        case 6:
            cout << "Ataskaitos issaugojimas\n";
            break;

        case 7:
            cout << "Programa baigta.\n";
            break;

        default:
            cout << "Neteisingas pasirinkimas.\n";
            break;
    }
}

int mainMenuChoice() {
    int choice;

    cout << "\n--- Dviraciu parduotuves uzsakymas ---\n";
    cout << "1. Perziureti visas prekes\n";
    cout << "2. Perziureti pasirinktos kategorijos prekes\n";
    cout << "3. Perziureti uzsakymo suma\n";
    cout << "4. Perziureti sumas pagal kategorijas\n";
    cout << "5. Parodyti visa uzsakymo ataskaita\n";
    cout << "6. Issaugoti visa ataskaita i faila\n";
    cout << "7. Iseiti\n";
    cout << "Pasirinkimas: ";
    choice = getNumber();

    return choice;
}

bool readFile(string categories[], string names[], double prices[], int quantities[], int &index) {
    ifstream file("uzsakymas.txt");

    if (!file.is_open()) {
        cout << "Nepavyko atidaryti uzsakymas.txt failo.\n";
        return false;
    }

    file >> index;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    if (index < 1 || index > 100) {
        cout << "Neteisingas prekiu kiekis faile.\n";
        return false;
    }

    for (int i = 0; i < index; i++) {
        string line;
        string priceText;
        string quantityText;

        if (!getline(file, line)) {
            cout << "Nepavyko nuskaityti visu prekiu.\n";
            return false;
        }

        stringstream data(line);

        if (!getline(data, categories[i], ';') ||
            !getline(data, names[i], ';') ||
            !getline(data, priceText, ';') ||
            !getline(data, quantityText)) {

            cout << "Neteisingas failo formatas.\n";
            return false;
            }

        stringstream priceStream(priceText);
        stringstream quantityStream(quantityText);

        if (!(priceStream >> prices[i]) || !(quantityStream >> quantities[i])) {
            cout << "Neteisinga kaina arba kiekis.\n";
            return false;
        }

        if (prices[i] <= 0 || quantities[i] <= 0) {
            cout << "Kaina ir kiekis turi buti teigiami.\n";
            return false;
        }

        if (categories[i] != "Dviraciai" &&
            categories[i] != "Dalys" &&
            categories[i] != "Aksesuarai") {

            cout << "Neteisinga kategorija: " << categories[i] << endl;
            return false;
            }
    }

    file.close();
    return true;
}

int getNumber() {
    int number;

    while (!(cin >> number)) {
        cout << "iveskite skaičiu: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return number;
}