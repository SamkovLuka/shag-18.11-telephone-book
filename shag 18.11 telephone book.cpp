#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Contact {
private:
    string fullName;
    

public:
    string homePhone;
    string workPhone;
    string mobilePhone;
    string additionalInfo;
    Contact(string name, string home, string work, string mobile, string info)
        : fullName(name), homePhone(home), workPhone(work), mobilePhone(mobile), additionalInfo(info) {}

    void display() const {
        cout << "ПІБ: " << fullName << endl;
        cout << "Домашній телефон: " << homePhone << endl;
        cout << "Робочий телефон: " << workPhone << endl;
        cout << "Мобільний телефон: " << mobilePhone << endl;
        cout << "Додаткова інформація: " << additionalInfo << endl;
    }

    string getFullName() const {
        return fullName;
    }

    void setFullName(const string& name) {
        fullName = name;
    }

    void setHomePhone(const string& phone) {
        homePhone = phone;
    }

    void setWorkPhone(const string& phone) {
        workPhone = phone;
    }

    void setMobilePhone(const string& phone) {
        mobilePhone = phone;
    }

    void setAdditionalInfo(const string& info) {
        additionalInfo = info;
    }
};

class PhoneBook {
private:
    Contact* contacts[100];
    int contactCount;

public:
    PhoneBook() : contactCount(0) {}

    void addContact(const Contact& contact) {
        if (contactCount < 100) {
            contacts[contactCount] = new Contact(contact);
            contactCount++;
        }
        else {
            cout << "Телефонна книга переповнена!" << endl;
        }
    }

    void removeContact(const string& fullName) {
        bool found = false;
        for (int i = 0; i < contactCount; ++i) {
            if (contacts[i]->getFullName() == fullName) {
                delete contacts[i];
                for (int j = i; j < contactCount - 1; ++j) {
                    contacts[j] = contacts[j + 1];
                }
                contactCount--;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Контакт не знайдено." << endl;
        }
    }

    void searchContact(const string& fullName) const {
        bool found = false;
        for (int i = 0; i < contactCount; ++i) {
            if (contacts[i]->getFullName() == fullName) {
                contacts[i]->display();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Контакт не знайдено." << endl;
        }
    }

    void displayAllContacts() const {
        if (contactCount == 0) {
            cout << "Телефонна книга порожня." << endl;
            return;
        }

        for (int i = 0; i < contactCount; ++i) {
            contacts[i]->display();
            cout << "-------------------------" << endl;
        }
    }

    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (int i = 0; i < contactCount; ++i) {
                outFile << contacts[i]->getFullName() << endl;
                outFile << contacts[i]->homePhone << endl;
                outFile << contacts[i]->workPhone << endl;
                outFile << contacts[i]->mobilePhone << endl;
                outFile << contacts[i]->additionalInfo << endl;
            }
            outFile.close();
            cout << "Дані збережено у файл." << endl;
        }
        else {
            cout << "Не вдалося відкрити файл для запису." << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            string name, home, work, mobile, info;
            while (getline(inFile, name) && getline(inFile, home) && getline(inFile, work) && getline(inFile, mobile) && getline(inFile, info)) {
                addContact(Contact(name, home, work, mobile, info));
            }
            inFile.close();
            cout << "Дані завантажено з файлу." << endl;
        }
        else {
            cout << "Не вдалося відкрити файл для читання." << endl;
        }
    }

    ~PhoneBook() {
        for (int i = 0; i < contactCount; ++i) {
            delete contacts[i];
        }
    }
};

int main() {
    setlocale(LC_ALL, "ukr");
    PhoneBook phoneBook;
    int choice;

    do {
        cout << "Меню:" << endl;
        cout << "1. Додати абонента" << endl;
        cout << "2. Видалити абонента" << endl;
        cout << "3. Шукати абонента" << endl;
        cout << "4. Показати всіх абонентів" << endl;
        cout << "5. Зберегти в файл" << endl;
        cout << "6. Завантажити з файлу" << endl;
        cout << "0. Вихід" << endl;
        cout << "Виберіть дію: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string name, home, work, mobile, info;
            cout << "Введіть ПІБ: ";
            getline(cin, name);
            cout << "Введіть домашній телефон: ";
            getline(cin, home);
            cout << "Введіть робочий телефон: ";
            getline(cin, work);
            cout << "Введіть мобільний телефон: ";
            getline(cin, mobile);
            cout << "Введіть додаткову інформацію: ";
            getline(cin, info);
            phoneBook.addContact(Contact(name, home, work, mobile, info));
            break;
        }
        case 2: {
            string name;
            cout << "Введіть ПІБ абонента для видалення: ";
            getline(cin, name);
            phoneBook.removeContact(name);
            break;
        }
        case 3: {
            string name;
            cout << "Введіть ПІБ абонента для пошуку: ";
            getline(cin, name);
            phoneBook.searchContact(name);
            break;
        }
        case 4:
            phoneBook.displayAllContacts();
            break;
        case 5: {
            string filename;
            cout << "Введіть ім'я файлу для збереження: ";
            getline(cin, filename);
            phoneBook.saveToFile(filename);
            break;
        }
        case 6: {
            string filename;
            cout << "Введіть ім'я файлу для завантаження: ";
            getline(cin, filename);
            phoneBook.loadFromFile(filename);
            break;
        }
        case 0:
            cout << "Вихід з програми." << endl;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    } while (choice != 0);

   
}

