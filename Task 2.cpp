#include <iostream>
#include <vector>
#include <string>

class Contact {
public:
    Contact(const std::string& name, const std::string& phone)
        : name(name), phone(phone) {}

    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }

private:
    std::string name;
    std::string phone;
};

class ContactManager {
public:
    void addContact(const std::string& name, const std::string& phone) {
        contacts.emplace_back(name, phone);
    }

    void viewContacts() const {
        if (contacts.empty()) {
            std::cout << "No contacts available." << std::endl;
            return;
        }

        for (const auto& contact : contacts) {
            std::cout << "Name: " << contact.getName()
                << ", Phone: " << contact.getPhone() << std::endl;
        }
    }

    void deleteContact(const std::string& name) {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->getName() == name) {
                contacts.erase(it);
                std::cout << "Contact deleted." << std::endl;
                return;
            }
        }
        std::cout << "Contact not found." << std::endl;
    }

private:
    std::vector<Contact> contacts;
};

void showMenu() {
    std::cout << "1. Add Contact" << std::endl;
    std::cout << "2. View Contacts" << std::endl;
    std::cout << "3. Delete Contact" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

int main() {
    ContactManager manager;
    int choice;
    std::string name, phone;

    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter phone number: ";
            std::getline(std::cin, phone);
            manager.addContact(name, phone);
            break;

        case 2:
            manager.viewContacts();
            break;

        case 3:
            std::cout << "Enter name of contact to delete: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            manager.deleteContact(name);
            break;

        case 4:
            return 0;

        default:
            std::cout << "Invalid option. Please try again." << std::endl;
        }
    }
}
