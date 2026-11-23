#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <iomanip>

using namespace std;

//Functions
void mainMenu(int choice, string categories[], string names[], double prices[], int quantities[], int index);
int mainMenuChoice();
bool readFile(string categories[], string names[], double prices[], int quantities[], int &index);
int getNumber();
void showAll(string categories[], string names[], double prices[], int quantities[], int index);
int getAvailableCategories(string categories[], string availableCategories[], int index);
string categoryMenu(string categories[], int index);
void showByCategory(string categories[], string names[], double prices[], int quantities[], int index);
double getTotal(double prices[], int quantities[], int index);
void showTotal(double prices[], int quantities[], int index);
void showTotalsByCategory(string categories[], double prices[], int quantities[], int index);
void showReport(string categories[], string names[], double prices[], int quantities[], int index);
void saveReport(string categories[], string names[], double prices[], int quantities[], int index);


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
        mainMenu(choice, categories, names, prices, quantities, index);

        if (choice == 7) {
            break;
        }
    }

    return 0;
}

void mainMenu(int choice, string categories[], string names[], double prices[], int quantities[], int index) {

    switch (choice) {
        case 1:
            showAll(categories, names, prices, quantities, index);
            break;

        case 2:
            showByCategory(categories, names, prices, quantities, index);
            break;

        case 3:
            showTotal(prices, quantities, index);
            break;

        case 4:
            showTotalsByCategory(categories, prices, quantities, index);
            break;

        case 5:
            showReport(categories, names, prices, quantities, index);
            break;

        case 6:
            saveReport(categories, names, prices, quantities, index);
            break;

        case 7:
            cout << "Programa baigta.\n";
            break;

        default:
            cout << "Neteisingas pasirinkimas.\n";
            break;
    }
}

string categoryMenu(string categories[], int index) {
    string availableCategories[100];

    int categoryCount = getAvailableCategories(
        categories,
        availableCategories,
        index
    );

    while (true) {
        cout << "\n--- Pasirinkite kategorija ---\n";

        for (int i = 0; i < categoryCount; i++) {
            cout << i + 1 << ". " << availableCategories[i] << endl;
        }

        cout << "Pasirinkimas: ";
        int choice = getNumber();

        if (choice >= 1 && choice <= categoryCount) {
            return availableCategories[choice - 1];
        }

        cout << "Neteisingas pasirinkimas.\n";
    }
}

int getAvailableCategories(string categories[], string availableCategories[], int index) {
    int categoryCount = 0;

    for (int i = 0; i < index; i++) {
        bool exists = false;

        for (int j = 0; j < categoryCount; j++) {
            if (categories[i] == availableCategories[j]) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            availableCategories[categoryCount] = categories[i];
            categoryCount++;
        }
    }

    return categoryCount;
}

 void showAll(string categories[], string names[], double prices[], int quantities[], int index) {
    cout << "\n--- Visos prekes ---\n";
    for (int i = 0; i < index; i++) {
        cout << i + 1 << ". "
            << categories[i] << " | "
            << names[i] << " | "
            << fixed << setprecision(2)
            << prices[i] << " Eur | "
            << quantities[i] << " vnt. | "
            << "Suma: " << prices[i] * quantities[i] << " Eur\n";
    }
}

void showByCategory(string categories[], string names[], double prices[],int quantities[], int index) {
    string category = categoryMenu(categories, index);
    cout << "\n--- " << category << " ---\n";

    for (int i = 0; i < index; i++) {
        if (categories[i] == category) {
            cout << names[i] << " | "
            << fixed << setprecision(2)
            << prices[i] << " Eur | "
            << quantities[i] << " vnt. | "
            << "Suma: " << prices[i] * quantities[i] << " Eur\n";
        }
    }
}

double getTotal(double prices[], int quantities[], int index) {
    double total = 0;

    for (int i = 0; i < index; i++) {
        total += prices[i] * quantities[i];
    }

    return total;
}

void showTotal(double prices[], int quantities[], int index) {
    double total = getTotal(prices, quantities, index);

    cout << "\n--- Uzsakymo suma ---\n";
    cout << fixed << setprecision(2)
         << "Bendra suma: " << total << " Eur\n";
}

void showTotalsByCategory(string categories[], double prices[], int quantities[], int index) {
    string availableCategories[100];
    int categoryCount = getAvailableCategories(categories, availableCategories, index);
    cout << "\n--- Sumos pagal kategorijas ---\n";

    for (int i = 0; i < categoryCount; i++) {
        double categoryTotal = 0;

        for (int j = 0; j < index; j++) {
            if (categories[j] == availableCategories[i]) {
                double itemTotal = prices[j] * quantities[j];
                categoryTotal += itemTotal - itemTotal * 0.10;
            }
        }

        cout << availableCategories[i] << ": " << fixed << setprecision(2) << categoryTotal << " Eur\n";
    }
}

void showReport(string categories[], string names[], double prices[], int quantities[], int index) {
    double total = 0;
    double totalDiscount = 0;
    cout << "\n--- Visa uzsakymo ataskaita ---\n\n";

    for (int i = 0; i < index; i++) {
        double itemTotal = prices[i] * quantities[i];
        double discount = itemTotal * 0.10;
        double finalItemTotal = itemTotal - discount;
        cout << i + 1 << ". "
            << categories[i] << " | "
            << names[i] << " | "
            << fixed << setprecision(2)
            << prices[i] << " Eur | "
            << quantities[i] << " vnt. | "
            << "Suma: " << itemTotal << " Eur | "
            << "Nuolaida: " << discount << " Eur | "
            << "Po nuolaidos: " << finalItemTotal << " Eur\n";
        total += itemTotal;
        totalDiscount += discount;
    }

    cout << "\n--- Sumos pagal kategorijas ---\n";
    string availableCategories[100];
    int categoryCount = getAvailableCategories(categories, availableCategories, index);

    for (int i = 0; i < categoryCount; i++) {
        double categoryTotal = 0;

        for (int j = 0; j < index; j++) {
            if (categories[j] == availableCategories[i]) {
                double itemTotal = prices[j] * quantities[j];
                categoryTotal += itemTotal - itemTotal * 0.10;
            }
        }

        cout << availableCategories[i] << ": " << categoryTotal << " Eur\n";
    }

    double finalTotal = total - totalDiscount;
    cout << "\n--- Galutines sumos ---\n";
    cout << "Suma pries nuolaida: " << total << " Eur\n";
    cout << "Bendra nuolaida: " << totalDiscount << " Eur\n";
    cout << "Galutine moketina suma: " << finalTotal << " Eur\n";
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

        if (!getline(data, categories[i], ';') || !getline(data, names[i], ';') || !getline(data, priceText, ';') || !getline(data, quantityText)) {
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

        if (categories[i] != "Dviraciai" && categories[i] != "Dalys" && categories[i] != "Aksesuarai") {
            cout << "Neteisinga kategorija: " << categories[i] << endl;
            return false;
        }
    }

    file.close();
    return true;
}

void saveReport(string categories[], string names[], double prices[], int quantities[], int index) {
    ofstream file("ataskaita.txt");

    if (!file.is_open()) {
        cout << "Nepavyko atidaryti ataskaita.txt failo.\n";
        return;
    }

    double total = 0;
    double totalDiscount = 0;
    file << fixed << setprecision(2);
    file << "--- Visa uzsakymo ataskaita ---\n\n";

    for (int i = 0; i < index; i++) {
        double itemTotal = prices[i] * quantities[i];
        double discount = itemTotal * 0.10;
        double finalItemTotal = itemTotal - discount;
        file << i + 1 << ". "
             << categories[i] << " | "
             << names[i] << " | "
             << prices[i] << " Eur | "
             << quantities[i] << " vnt. | "
             << "Suma: " << itemTotal << " Eur | "
             << "Nuolaida: " << discount << " Eur | "
             << "Po nuolaidos: " << finalItemTotal << " Eur\n";
        total += itemTotal;
        totalDiscount += discount;
    }

    string availableCategories[100];
    int categoryCount = getAvailableCategories(categories, availableCategories, index);
    file << "\n--- Sumos pagal kategorijas ---\n";

    for (int i = 0; i < categoryCount; i++) {
        double categoryTotal = 0;
        for (int j = 0; j < index; j++) {
            if (categories[j] == availableCategories[i]) {
                double itemTotal = prices[j] * quantities[j];
                categoryTotal += itemTotal - itemTotal * 0.10;
            }
        }

        file << availableCategories[i] << ": " << categoryTotal << " Eur\n";
    }

    double finalTotal = total - totalDiscount;
    file << "\n--- Galutines sumos ---\n";
    file << "Suma pries nuolaida: " << total << " Eur\n";
    file << "Bendra nuolaida: " << totalDiscount << " Eur\n";
    file << "Galutine moketina suma: " << finalTotal << " Eur\n";
    file.close();

    if (file.fail()) {
        cout << "Nepavyko issaugoti ataskaitos.\n";
    } else {
        cout << "Ataskaita issaugota i ataskaita.txt.\n";
    }
}

int getNumber() {
    int number;

    while (!(cin >> number)) {
        cout << "iveskite skaiciu: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return number;
}