#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "CityDataManager.h"
#include "EventSystem.h"

inline void runAnalytics(CityDataManager& manager,
                         const std::vector<Event>& events) {

    std::vector<SensorReading>& readings = manager.getReadings();

    std::cout << "\nANALYTICS REPORT \n";

    // Checks for readings
    if (!readings.empty()) {

        // Sort the readings from lowest to highest
        std::sort(readings.begin(), readings.end(),
            [](SensorReading a, SensorReading b) {
                return a.metricValue < b.metricValue;
            });

        std::cout << "\nSensor Readings:\n";

        // Displays all readings
        for (SensorReading reading : readings) {
            reading.display();
        }

        // Finds lowest reading
        auto lowest = std::min_element(readings.begin(), readings.end(),
            [](SensorReading a, SensorReading b) {
                return a.metricValue < b.metricValue;
            });

        // Finds  highest reading
        auto highest = std::max_element(readings.begin(), readings.end(),
            [](SensorReading a, SensorReading b) {
                return a.metricValue < b.metricValue;
            });

        std::cout << "Lowest Value: " << lowest->metricValue << "\n";
        std::cout << "Highest Value: " << highest->metricValue << "\n";

        // Counts readings above 80
        int critical = std::count_if(readings.begin(), readings.end(),
            [](SensorReading reading) {
                return reading.metricValue > 80;
            });

        std::cout << "Critical Readings: " << critical << "\n";

        // Look for a PowerGrid sensor
        auto powerGrid = std::find_if(readings.begin(), readings.end(),
            [](SensorReading reading) {
                return reading.sensorType == "PowerGrid";
            });

        if (powerGrid != readings.end()) {
            std::cout << "PowerGrid found in: "
                      << powerGrid->zoneId << "\n";
        }
        else {
            std::cout << "PowerGrid sensor not found\n";
        }
    }

    // Show the number of events
    std::cout << "\nTotal Events: " << events.size() << "\n";

    // Count traffic events
    int traffic = std::count_if(events.begin(), events.end(),
        [](Event event) {
            return event.type == "Traffic";
        });

    // Count power events
    int power = std::count_if(events.begin(), events.end(),
        [](Event event) {
            return event.type == "Power";
        });

    std::cout << "Traffic Events: " << traffic << "\n";
    std::cout << "Power Events: " << power << "\n";

    // Big-O for the algorithms used
    std::cout << "\n===== BIG-O =====\n";
    std::cout << "sort: O(n log n)\n";
    std::cout << "find_if: O(n)\n";
    std::cout << "min_element: O(n)\n";
    std::cout << "max_element: O(n)\n";
    std::cout << "count_if: O(n)\n";
}

#endif
