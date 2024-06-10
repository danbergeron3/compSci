#include <iostream>
#include <thread>
#include <stdexcept>
#include <string>

void greeting1(std::thread&& thr) {
    std::cout << "Thread " << thr.get_id() << " is executing.\n";
    thr.join();

    return;
}

std::thread greeting2(void) {
    auto hello = []() {
        using namespace std::literals;
        std::this_thread::sleep_for(1s);
        std::cout << "Hello, thread!\n";
    };

    std::thread thr(hello);
    std::cout << "Thread " << thr.get_id() << " is executing.\n";
    std::cout << "Passing thread " << thr.get_id() << " to main.\n";
    return thr;
}

void excepTest(void) {
    auto hello = []() {
        std::string str = "Thread exception";
        throw str;
    };
    std::thread thr(hello);

    thr.join();
}

int main(int argc, char* argv[]) {
    auto hello = []() {
        using namespace std::literals;
        std::this_thread::sleep_for(1s);
        std::cout << "Hello, thread!\n";
    };

    std::thread thr1(hello);
    greeting1(std::move(thr1));

    std::thread thr2 = greeting2();
    std::cout << "Thread " << thr2.get_id() << " is now in main.\n";

    thr2.join();

    // try {
    //     excepTest();    
    // } catch (std::string err) {
    //     std::cout << "Exception caught: " << err << std::endl;
    // }
    
    return 0;
}