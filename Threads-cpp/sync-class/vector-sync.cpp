#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

using namespace std::literals;

// A shared object that is internally synchronized
// ensures only one thread at a time can access the vector
class Vector {
    private:
        std::vector<int> vec;
        std::mutex mut;
    public: 
        void push_back(int value) {
            // lock critical space 
            mut.lock();

            // add value stl vector
            vec.push_back(value);

            // unlock mux 
            mut.unlock();
        }

        void print(void) {
            // lock the data in to be printed 
            mut.lock();
            std::cout << "Vector Data:\n";
            for (unsigned long i = 0; i < vec.size(); i++) {
                std::cout << vec[i] << "," << std::endl; 
            }
            mut.unlock();
        }
};

void task(Vector& vec, int size) {
    for(int i = 0; i < size; i++){
        vec.push_back(i);
        std::this_thread::sleep_for(50ms);
        vec.print();
    }
}

int main(int argc, char* argv[]) {
    
    Vector isVector; // internally synced vector
    int size;

    std::cout << "Enter the size of the vector: ";
    std::cin >> size;
    
    // to match size nothing to do with multithreading
    size++;

    // start thread
    std::thread thr(task, std::ref(isVector), size);

    thr.join();

    return 0;
}