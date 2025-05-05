#include <iostream>
#include <vector>
#include <thread>


using namespace std;

enum class DriverStatus {
    IDLE,
    DELIVERING,
    SETTLING
};


class Delivery {
private:
    time_t start_time;
    time_t end_time;

public:
    Delivery() {}

    time_t getStartTime() const {
        return start_time;
    }
    time_t getEndTime() const {
        return end_time;
    }

    void setStartTime(time_t _start_time) {
        start_time = _start_time;
    }
    void setEndTime(time_t _end_time) {
        end_time = _end_time;
    }
};

class Driver {
private:
    string name;
    float hourly;
    time_t lastSettled;
    vector<Delivery*> deliveriesSinceLastSettled;
    vector<Delivery*> settledDeliveries;
    Delivery* currentDelivery;
    DriverStatus status;


public:
    Driver(string _name, float _hourly, DriverStatus _driverStatus) : name(_name), hourly(_hourly), status(_driverStatus) {}

    string getName() const {
        return name;
    }
    float getHourly() const {
        return hourly;
    }

    DriverStatus getStatus() const {
        return status;
    }


    void deliver(Delivery* delivery) {
        status = DriverStatus::DELIVERING;
        deliveriesSinceLastSettled.push_back(delivery);
        currentDelivery = delivery;
        delivery->setStartTime(time(0));
        // finishDelivery in separate thread
        thread deliveryThread(&Driver::finishDelivery, this);
        deliveryThread.detach(); // Detach the thread to allow it to run independently
    }

    void finishDelivery() {
        // Simulate delivery time random between 1 to 5 seconds
        int deliveryTime = rand() % 5 + 1;
        this_thread::sleep_for(chrono::seconds(deliveryTime));

        currentDelivery->setEndTime(time(0));
        cout << "Delivery finished by " << name << " in " << deliveryTime << " seconds." << endl;
        currentDelivery = nullptr;
        status = DriverStatus::IDLE;

    }

    float getTotalAmountToSettle() {
        float total = 0;
        for (auto delivery : deliveriesSinceLastSettled) {
            total += hourly * difftime(delivery->getEndTime(), delivery->getStartTime()) / 3600;
        }
        return total;
    }

    float getTotalSettledAmount() {
        float total = 0;
        for (auto delivery : settledDeliveries) {
            total += hourly * difftime(delivery->getEndTime(), delivery->getStartTime()) / 3600;
        }
        return total;
    }


    void settle() {
        lastSettled = time(0);
        settledDeliveries.insert(settledDeliveries.end(), deliveriesSinceLastSettled.begin(), deliveriesSinceLastSettled.end());
        deliveriesSinceLastSettled.clear();
    }

};




class DriverAssignmentStartegy {
public:
    virtual void assignDriver(vector<Driver*> drivers, Delivery* delivery) = 0;
};

class AssignAnyFreeDriverStartegy : public DriverAssignmentStartegy {
public:
    void assignDriver(vector<Driver*> drivers, Delivery* delivery) override {
        for (auto driver : drivers) {
            if (driver->getStatus() == DriverStatus::IDLE) {
                driver->deliver(delivery);
                return;
            }
        }
        cout << "No free drivers available." << endl;
    }
};


class DeliveryManager {
private:
    vector<Driver*> drivers;
    vector<Delivery*> deliveries;
    DriverAssignmentStartegy* driverAssignmentStrategy;

public:
    DeliveryManager(DriverAssignmentStartegy* strategy) : driverAssignmentStrategy(strategy) {}

    void addDriver(Driver* driver) {
        drivers.push_back(driver);
    }

    void addDelivery(Delivery* delivery) {
        deliveries.push_back(delivery);
    }

    void settleAll() {
        for (auto driver : drivers) {
            driver->settle();
        }
    }

    float printSettledAmounts() {
        float totalSettled = 0;
        for (auto driver : drivers) {
            float settledAmount = driver->getTotalSettledAmount();
            cout << "Driver: " << driver->getName() << ", Settled Amount: " << settledAmount << endl;
            totalSettled += settledAmount;
        }
        return totalSettled;
    }

    float printTotalAmountToSettle() {
        float totalToSettle = 0;
        for (auto driver : drivers) {
            float toSettle = driver->getTotalAmountToSettle();
            cout << "Driver: " << driver->getName() << ", Amount to Settle: " << toSettle << endl;
            totalToSettle += toSettle;
        }
        return totalToSettle;
    }

    void assignDriver(Delivery* delivery) {
        driverAssignmentStrategy->assignDriver(drivers, delivery);
    }


};


int main() {
    DeliveryManager deliveryManager(new AssignAnyFreeDriverStartegy());

    Driver* driver1 = new Driver("John", 20.0, DriverStatus::IDLE);
    Driver* driver2 = new Driver("Jane", 25.0, DriverStatus::IDLE);

    deliveryManager.addDriver(driver1);
    deliveryManager.addDriver(driver2);

    Delivery* delivery1 = new Delivery();
    Delivery* delivery2 = new Delivery();

    deliveryManager.addDelivery(delivery1);
    deliveryManager.addDelivery(delivery2);

    deliveryManager.assignDriver(delivery1);
    deliveryManager.assignDriver(delivery2);

    // Wait for deliveries to finish
    this_thread::sleep_for(chrono::seconds(10));
    cout << "Total Amount to Settle: \n" << deliveryManager.printTotalAmountToSettle() << endl;
    cout << "Total Settled Amount: \n" << deliveryManager.printSettledAmounts() << endl;

    deliveryManager.settleAll();
    cout << "After Settling:" << endl;

    cout << "Total Amount to Settle: \n" << deliveryManager.printTotalAmountToSettle() << endl;
    cout << "Total Settled Amount: \n" << deliveryManager.printSettledAmounts() << endl;
    // Clean up
    delete driver1;
    delete driver2;
    delete delivery1;
    delete delivery2;
    return 0;
}