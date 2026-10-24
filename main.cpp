#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include "Engineer.h"
#include "CityDataManager.h"
#include "EventSystem.h"
#include "CityArchitecture.h"
#include "Analytics.h"

using namespace std;


// Save the system settings
void saveConfig(string filename = "config.txt") {

    ofstream file(filename);

    file << "NeoVerse AI City Survival System\n";
    file << "Version=1.0\n";
    file << "SensorCriticalThreshold=80\n";

    file.close();
}


// Show the Big-O
void displayBigO() {

    cout << "\nBig-O Information\n";

    cout << "Engineer search: O(n)\n";
    cout << "Vector access: O(1)\n";
    cout << "Vector add at end: O(1)\n";
    cout << "Vector remove at end: O(1)\n";
    cout << "List add/remove: O(1)\n";
    cout << "List traversal: O(n)\n";
    cout << "Queue add/remove: O(1)\n";
    cout << "Stack add/remove: O(1)\n";
}


int main() {

    cout << "NeoVerse AI City System\n";
    cout << "=======================\n";


    // Engineer login

    cout << "\nEngineer Login\n";

    vector<Engineer> engineers;

    engineers.push_back(
        Engineer("ENG001", "Shaun", "1234", High)
    );

    engineers.push_back(
        Engineer("ENG002", "Alex", "pass567", Medium)
    );

    engineers.push_back(
        Engineer("ENG003", "Sam", "secure890", Low)
    );

    saveEngineers(engineers);

    vector<Engineer> loadedEngineers =
        loadEngineers();

    string username;
    string password;

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;


    // Find the engineer

    auto engineer = find_if(
        loadedEngineers.begin(),
        loadedEngineers.end(),

        [username](const Engineer& e) {
            return e.getUsername() == username;
        }
    );


    if (engineer == loadedEngineers.end()) {

        cout << "Username not found.\n";
        return 0;
    }

    if (!engineer->login(password)) {

        cout << "Wrong password.\n";
        return 0;
    }

    cout << "Login successful!\n";

    engineer->display();


    // City data

    cout << "\nCity Data\n";

    CityDataManager data;


    // Add sensor readings

    data.addSensorReading(
        {"12:00", "Temperature", 38.5, "Zone-A"}
    );

    data.addSensorReading(
        {"12:01", "PowerGrid", 92.4, "Zone-B"}
    );

    data.addSensorReading(
        {"12:02", "TrafficDensity", 45.0, "Zone-A"}
    );

    data.addSensorReading(
        {"12:03", "AirQuality", 15.2, "Zone-C"}
    );


    // Add logs

    data.addLog(
        "WARN",
        "Power",
        "Grid frequency problem"
    );

    data.addLog(
        "CRITICAL",
        "Security",
        "Unauthorized access"
    );


    data.displayReadings();
    data.displayLogs();


    // Event processing

    cout << "\nEvent Processing\n";

    EventProcessor eventSystem;

    vector<Event> events;

    events.push_back(
        {101, "Traffic", "Traffic on Highway 4", 2}
    );

    events.push_back(
        {102, "Weather", "High wind warning", 1}
    );

    events.push_back(
        {103, "Power", "Power failure", 4}
    );


    // Add events to the queue

    for (Event event : events) {
        eventSystem.addEvent(event);
    }


    // Add emergencies to the stack

    eventSystem.addEmergency(
        {501, "Power Outage", "Reroute generator lines"}
    );

    eventSystem.addEmergency(
        {502, "Fire Hazard", "Send emergency responders"}
    );


    // Process events in FIFO order

    eventSystem.processNextEvent();
    eventSystem.processNextEvent();


    // Resolve emergencies in LIFO order

    eventSystem.resolveEmergency();
    eventSystem.resolveEmergency();


    // City architecture

    cout << "\nCity Architecture\n";

    vector<CityComponent*> systems;

    systems.push_back(
        new PowerSystem(1, "Power System", 88.5)
    );

    systems.push_back(
        new TransportSystem(2, "Transport System", 120)
    );

    systems.push_back(
        new HealthSystem(3, "Health System", 5)
    );

    systems.push_back(
        new SecuritySystem(4, "Security System", 3)
    );


    // Run each system

    for (CityComponent* system : systems) {

        system->activate();

        cout << system->getStatus() << "\n";

        system->processEvent("System Check");

        cout << "\n";
    }


    // STL analytics

    runAnalytics(data, events);


    // System report

    cout << "\nSystem Report\n";

    cout << "Total events: "
         << events.size() << "\n";

    cout << "Emergency events: 2\n";

    cout << "Sensor readings: "
         << data.getReadings().size() << "\n";


    // Save files

    data.saveLogs("city_logs.dat");

    data.exportLogsCSV(
        "exported_city_logs.csv"
    );

    eventSystem.saveEvents("events.dat");

    saveConfig("config.txt");


    cout << "\nFiles Saved\n";

    cout << "engineers.dat\n";
    cout << "events.dat\n";
    cout << "city_logs.dat\n";
    cout << "config.txt\n";
    cout << "exported_city_logs.csv\n";


    displayBigO();


    // Turn off the systems

    for (CityComponent* system : systems) {

        system->deactivate();

        delete system;
    }


    cout << "\nSystem completed successfully.\n";

    return 0;
}