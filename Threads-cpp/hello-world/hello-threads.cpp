#include <iostream>
#include <thread>



int main(int argc, char* argv[]) {
    
    std::cout << "Hello World!\n";

    std::thread hi([](){

        auto uid = std::this_thread::get_id();
        std::cout << "Hello thread " << uid << "!\n";
    });
    
    std::cout << "Thread UID: " << hi.get_id() << std::endl;
    hi.join();
    
    std::cout << "Completed Execution\n";
    return 0;
}