#ifndef CITY_DATA_MANAGER_H
#define CITY_DATA_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>

// Stores information from a sensor
struct SensorReading {

    std::string timestamp;
    std::string sensorType;
    double metricValue;
    std::string zoneId;

    SensorReading(std::string time = "", std::string type = "",
                  double value = 0, std::string zone = "") {

        timestamp = time;
        sensorType = type;
        metricValue = value;
        zoneId = zone;
    }

    // Displays the sensor information
    void display() const {

        std::cout << "Time: " << timestamp << "\n";
        std::cout << "Sensor: " << sensorType << "\n";
        std::cout << "Value: " << metricValue << "\n";
        std::cout << "Zone: " << zoneId << "\n";
    }
};


// Stores information about city events
struct CityLog {

    int logID;
    std::string timestamp;
    std::string severity;
    std::string subsystem;
    std::string message;

    CityLog(int id = 0, std::string time = "",
            std::string sev = "", std::string system = "",
            std::string msg = "") {

        logID = id;
        timestamp = time;
        severity = sev;
        subsystem = system;
        message = msg;
    }

    // Displays the city log
    void display() const {

        std::cout << "Log ID: " << logID << "\n";
        std::cout << "Time: " << timestamp << "\n";
        std::cout << "Severity: " << severity << "\n";
        std::cout << "System: " << subsystem << "\n";
        std::cout << "Message: " << message << "\n";
    }
};


// Manages sensor readings and city logs
class CityDataManager {

private:

    // Vector stores sensor readings
    std::vector<SensorReading> readings;

    // List stores old city logs
    std::list<CityLog> logs;

    int nextID;

public:

    CityDataManager() {
        nextID = 1;
    }


    // Get the sensor readings
    std::vector<SensorReading>& getReadings() {
        return readings;
    }

    // Get the city logs
    const std::list<CityLog>& getLogs() const {
        return logs;
    }


    // Add a new sensor reading
    void addSensorReading(const SensorReading& reading) {
        readings.push_back(reading);
    }


    // Another name for adding a reading
    void addReading(const SensorReading& reading) {
        readings.push_back(reading);
    }


    // Add a new city log
    void addLog(std::string severity, std::string system,
                std::string message,
                std::string timestamp = "2026-09-20 12:00") {

        logs.push_back(
            CityLog(nextID, timestamp, severity, system, message)
        );

        nextID++;
    }


    // Remove the last sensor reading
    void removeReading() {

        if (!readings.empty()) {
            readings.pop_back();
        }
    }


    // Remove the first city log
    void removeLog() {

        if (!logs.empty()) {
            logs.pop_front();
        }
    }


    // Display all sensor readings
    void displayReadings() const {

        std::cout << "\n--- Sensor Readings ---\n";

        for (const SensorReading& reading : readings) {
            reading.display();
            std::cout << "\n";
        }
    }


    // Display all city logs
    void displayLogs() const {

        std::cout << "\n--- City Logs ---\n";

        for (const CityLog& log : logs) {
            log.display();
            std::cout << "\n";
        }
    }


    // Remove all stored data
    void clearData() {

        readings.clear();
        logs.clear();

        nextID = 1;
    }


    // Save logs to a file
    void saveLogs(std::string filename = "city_logs.dat") const {

        std::ofstream file(filename);

        for (const CityLog& log : logs) {

            file << log.logID << "|"
                 << log.timestamp << "|"
                 << log.severity << "|"
                 << log.subsystem << "|"
                 << log.message << "\n";
        }

        file.close();
    }


    // Export logs to a CSV file
    void exportLogsCSV(
        std::string filename = "exported_city_logs.csv") const {

        std::ofstream file(filename);

        file << "LogID,Timestamp,Severity,Subsystem,Message\n";

        for (const CityLog& log : logs) {

            file << log.logID << ","
                 << log.timestamp << ","
                 << log.severity << ","
                 << log.subsystem << ","
                 << "\"" << log.message << "\"\n";
        }

        file.close();
    }


    // Load logs from the saved file
    void loadLogs(std::string filename = "city_logs.dat") {

        std::ifstream file(filename);

        std::string id;
        std::string timestamp;
        std::string severity;
        std::string subsystem;
        std::string message;

        while (std::getline(file, id, '|') &&
               std::getline(file, timestamp, '|') &&
               std::getline(file, severity, '|') &&
               std::getline(file, subsystem, '|') &&
               std::getline(file, message)) {

            int number = std::stoi(id);

            logs.push_back(
                CityLog(number, timestamp, severity,
                        subsystem, message)
            );

            if (number >= nextID) {
                nextID = number + 1;
            }
        }

        file.close();
    }
};

#endif