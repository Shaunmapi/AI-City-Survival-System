
#include <iostream>
#include <string>

// Base class for all city systems
class CityComponent {
protected:
    int componentID;
    std::string name;

public:
    CityComponent(int id, std::string n) {
        componentID = id;
        name = n;
    }

    virtual ~CityComponent() {}

    // These functions will be changed by each system
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual std::string getStatus() = 0;
    virtual void processEvent(std::string event) = 0;

    int getID() {
        return componentID;
    }

    std::string getName() {
        return name;
    }
};


// Power system
class PowerSystem : public CityComponent {
private:
    double powerLevel;

public:
    PowerSystem(int id, std::string n, double power)
        : CityComponent(id, n) {
        powerLevel = power;
    }

    void activate() override {
        std::cout << name << " is activated.\n";
    }

    void deactivate() override {
        std::cout << name << " is deactivated.\n";
    }

    std::string getStatus() override {
        return "Power Level: " + std::to_string(powerLevel) + "%";
    }

    void processEvent(std::string event) override {
        std::cout << "Power system handling: " << event << "\n";
    }

    void supplyPower() {
        std::cout << "Supplying power to the city.\n";
    }
};


// Transport system
class TransportSystem : public CityComponent {
private:
    int trafficFlow;

public:
    TransportSystem(int id, std::string n, int flow)
        : CityComponent(id, n) {
        trafficFlow = flow;
    }

    void activate() override {
        std::cout << name << " is active.\n";
    }

    void deactivate() override {
        std::cout << name << " is stopped.\n";
    }

    std::string getStatus() override {
        return "Traffic Flow: " + std::to_string(trafficFlow);
    }

    void processEvent(std::string event) override {
        std::cout << "Transport system handling: " << event << "\n";
    }

    void manageTraffic() {
        std::cout << "Managing traffic.\n";
    }
};


// Health system
class HealthSystem : public CityComponent {
private:
    int hospitalCount;

public:
    HealthSystem(int id, std::string n, int count)
        : CityComponent(id, n) {
        hospitalCount = count;
    }

    void activate() override {
        std::cout << name << " is online.\n";
    }

    void deactivate() override {
        std::cout << name << " is offline.\n";
    }

    std::string getStatus() override {
        return "Hospitals: " + std::to_string(hospitalCount);
    }

    void processEvent(std::string event) override {
        std::cout << "Health system handling: " << event << "\n";
    }

    void provideCare() {
        std::cout << "Medical teams are being sent.\n";
    }
};


// Security system
class SecuritySystem : public CityComponent {
private:
    int threatLevel;

public:
    SecuritySystem(int id, std::string n, int threat)
        : CityComponent(id, n) {
        threatLevel = threat;
    }

    void activate() override {
        std::cout << name << " is monitoring the city.\n";
    }

    void deactivate() override {
        std::cout << name << " is on standby.\n";
    }

    std::string getStatus() override {
        return "Threat Level: " + std::to_string(threatLevel) + "/5";
    }

    void processEvent(std::string event) override {
        std::cout << "Security system handling: " << event << "\n";
    }

    void monitorCity() {
        std::cout << "Monitoring city areas.\n";
    }
};

#endif