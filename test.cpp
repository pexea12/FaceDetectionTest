#include <iostream>
#include <thread>

void call_from_thread(int i) {
    std::cout << "Hello, World " << i << std::endl;
}

int main() {
    std::thread t[10];

    for (int i = 0; i < 10; ++i) 
        t[i] = std::thread(call_from_thread, i);

    std::cout << "From main" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << "Joining " << i << std::endl;
        t[i].join();
    }

    return 0;
}