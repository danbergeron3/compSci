#include <thread>
#include <iostream>
#include <mutex>
#include <string>

// global object in charge of restricting threads from entering critical section 
std::mutex task_mutex;

void task1(std::string str) {
    
    // lock mutex
    task_mutex.lock();

    std::cout << str[0] << str[1] << str[2] << std::endl;

    task_mutex.unlock();
}

int main(int argc, char* argv[]) {
    // excute threads
    std::thread thr1(task1, "abc");
    std::thread thr2(task1, "dan");
    std::thread thr3(task1, "sam");
    std::thread thr4(task1, "ale");

    // join threads
    thr1.join();
    thr2.join();
    thr3.join();
    thr4.join();

    return 0;
}