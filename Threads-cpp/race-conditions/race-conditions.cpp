#include <thread>
#include <iostream>
#include <vector>

int counter {0};

void task(int thread) {
    int i = 0;
    for(i = 0; counter < 100000; i++ ) {
        counter++;
    }

    std::cout << "Thread #" << thread << " has counted " << i 
    << " times. With a final counter of "<< counter << std::endl;
} 
int main(int argc, char* argv[]) {
    
    using namespace std::literals;

    // create threads and pass args to callback
    // std::thread thr1(count, 1);
    // std::thread thr2(count, 2);
    // std::thread thr3(count, 3);


    // thr1.join();
    // thr2.join();
    // thr3.join();

    std::vector<std::thread> tasks;
    for (int i = 0; i < 10; ++i) tasks.push_back(std::thread{task});
    for (auto& t: tasks) t.join();
    std::cout << counter << std::endl;
    return 0;
}