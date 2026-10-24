#ifndef ENGINEER_H
#define ENGINEER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

// Different levels of clearance
enum ClearanceLevel {
    Low,
    Medium,
    High
};


// Changes the clearance level into text
std::string clearanceToString(ClearanceLevel level) {

    if (level == Low) {
        return "Low";
    }

    if (level == Medium) {
        return "Medium";
    }

    return "High";
}


// Changes text back into a clearance level
ClearanceLevel stringToClearance(std::string value) {

    if (value == "High") {
        return High;
    }

    if (value == "Medium") {
        return Medium;
    }

    return Low;
}


// Engineer class
class Engineer {

private:

    std::string engineerID;
    std::string username;
    std::string password;
    ClearanceLevel clearance;

public:

    // Constructor
    Engineer(std::string id, std::string user,
             std::string pass, ClearanceLevel level) {

        engineerID = id;
        username = user;
        password = pass;
        clearance = level;
    }


    // Get engineer ID
    std::string getEngineerID() const {
        return engineerID;
    }


    // Get username
    std::string getUsername() const {
        return username;
    }


    // Get password
    std::string getPassword() const {
        return password;
    }


    // Get clearance level
    ClearanceLevel getClearanceLevel() const {
        return clearance;
    }


    // Check if the password is correct
    bool login(std::string inputPassword) const {

        if (inputPassword == password) {
            return true;
        }

        return false;
    }


    // Display engineer information
    void display() const {

        std::cout << "Engineer ID: " << engineerID << "\n";
        std::cout << "Username: " << username << "\n";
        std::cout << "Clearance: "
                  << clearanceToString(clearance) << "\n";

        std::cout << "------------------------\n";
    }
};


// Save engineers to a file
void saveEngineers(std::vector<Engineer>& engineers,
                   std::string filename = "engineers.dat") {

    std::ofstream file(filename);

    for (Engineer& engineer : engineers) {

        file << engineer.getEngineerID() << "|";
        file << engineer.getUsername() << "|";
        file << engineer.getPassword() << "|";
        file << clearanceToString(
            engineer.getClearanceLevel()
        );

        file << "\n";
    }

    file.close();
}


// Load engineers from a file
std::vector<Engineer> loadEngineers(
    std::string filename = "engineers.dat") {

    std::vector<Engineer> engineers;

    std::ifstream file(filename);

    std::string id;
    std::string username;
    std::string password;
    std::string clearance;

    // Read each engineer from the file
    while (std::getline(file, id, '|') &&
           std::getline(file, username, '|') &&
           std::getline(file, password, '|') &&
           std::getline(file, clearance)) {

        Engineer engineer(
            id,
            username,
            password,
            stringToClearance(clearance)
        );

        engineers.push_back(engineer);
    }

    file.close();

    return engineers;
}

#endif