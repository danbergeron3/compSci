#include <thread>
#include <iostream>
#include <chrono>

void thread_callback(int i, std::chrono::seconds sleep) {
    using namespace std::literals;
    std::this_thread::sleep_for(sleep);
    std::cout << "\nThread " << i << " created." << std::endl;
    std::cout << "Thread uid: " << std::this_thread::get_id() << "\n" << std::endl;
} 

int main(int argc, char* argv[]) {
    
    using namespace std::literals;

    // create threads and pass args to callback
    std::thread thr1(thread_callback, 1, 1s);
    std::thread thr2(thread_callback, 2, 2s);
    std::thread thr3(thread_callback, 3, 3s);
    
    // join threads
    thr1.join();
    thr2.join();
    thr3.join();

    return 0;
}