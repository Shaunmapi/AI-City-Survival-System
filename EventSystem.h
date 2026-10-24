#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <fstream>


// Stores normal city events
struct Event {

    int eventID;
    std::string type;
    std::string description;
    int priority;
};


// Stores emergency events
struct EmergencyEvent {

    int emergencyID;
    std::string title;
    std::string requiredAction;
};


// Handles normal events and emergencies
class EventProcessor {

private:

    // Queue = First In, First Out
    std::queue<Event> events;

    // Stack = Last In, First Out
    std::stack<EmergencyEvent> emergencies;

    int totalProcessed;

public:

    // Constructor
    EventProcessor() {
        totalProcessed = 0;
    }


    // Add a normal event to the queue
    void addEvent(const Event& event) {
        events.push(event);
    }


    // Add an emergency to the stack
    void addEmergency(const EmergencyEvent& emergency) {
        emergencies.push(emergency);
    }


    // Check if there are normal events
    bool hasEvents() const {
        return !events.empty();
    }


    // Check if there are emergencies
    bool hasEmergencies() const {
        return !emergencies.empty();
    }


    // Get number of processed events
    int getTotalProcessed() const {
        return totalProcessed;
    }


    // Process the first event in the queue
    void processNextEvent() {

        if (events.empty()) {
            std::cout << "No events to process.\n";
            return;
        }

        Event event = events.front();

        // Remove the event from the queue
        events.pop();

        totalProcessed++;

        std::cout << "\nEvent Processed\n";
        std::cout << "ID: " << event.eventID << "\n";
        std::cout << "Type: " << event.type << "\n";
        std::cout << "Description: "
                  << event.description << "\n";
        std::cout << "Priority: "
                  << event.priority << "\n";
    }


    // Resolve the most recent emergency
    void resolveEmergency() {

        if (emergencies.empty()) {
            std::cout << "No emergencies.\n";
            return;
        }

        EmergencyEvent emergency = emergencies.top();

        // Remove the emergency from the stack
        emergencies.pop();

        std::cout << "\nEmergency Resolved\n";
        std::cout << "ID: " << emergency.emergencyID << "\n";
        std::cout << "Title: " << emergency.title << "\n";
        std::cout << "Action: "
                  << emergency.requiredAction << "\n";
    }


    // Get all events still waiting in the queue
    std::vector<Event> getPendingEvents() const {

        std::queue<Event> copy = events;

        std::vector<Event> result;

        while (!copy.empty()) {

            result.push_back(copy.front());

            copy.pop();
        }

        return result;
    }


    // Save events to a file
    void saveEvents(
        std::string filename = "events.dat") const {

        std::ofstream file(filename);

        std::vector<Event> pendingEvents =
            getPendingEvents();

        for (Event event : pendingEvents) {

            file << event.eventID << "|";
            file << event.type << "|";
            file << event.description << "|";
            file << event.priority << "\n";
        }

        file.close();
    }


    // Load events from a file
    void loadEvents(
        std::string filename = "events.dat") {

        std::ifstream file(filename);

        std::string id;
        std::string type;
        std::string description;
        std::string priority;

        while (std::getline(file, id, '|') &&
               std::getline(file, type, '|') &&
               std::getline(file, description, '|') &&
               std::getline(file, priority)) {

            Event event;

            event.eventID = std::stoi(id);
            event.type = type;
            event.description = description;
            event.priority = std::stoi(priority);

            // Add the event to the queue
            addEvent(event);
        }

        file.close();
    }
};

#endif