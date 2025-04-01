#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // Mutex to protect shared resource
int counter = 0;

void incrementCounter() {
    for (int i = 0; i < 100000; ++i) {
        mtx.lock();  // Lock before modifying shared resource
        ++counter;
        mtx.unlock(); // Unlock after modification
    }
}

int main() {
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);

    t1.join();
    t2.join();

    std::cout << "Final Counter Value: " << counter << std::endl;
    return 0;
}
