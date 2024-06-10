#include <iostream> 
#include <thread>

// To Follow RAII we create a class wrapper around the thread
// Resource acquisition is initilization (RAII)

// this class raps the thread and ensures that a thread is joined or detatched before the 
// destructor is called

// also ensures mo copies are made 
class thread_guard {
    private: 
        std::thread thr;
    public:
        // constructor uses rvalue 
        explicit thread_guard(std::thread&& thr) : thr(std::move(thr)) { 
        }

        ~thread_guard(){
            if(thr.joinable()) {
                thr.join();
            }
        }

        // delete all copy constructor and copy asignment operator
        thread_guard(const thread_guard&) = delete;
        thread_guard& operator=(const thread_guard&) = delete;
};

void hello(int i) {
    std::cout << "Thread " << i << " Created!" << std::endl;
}

int main(int argc, char* argv[]) {

    // create thread
    
    std::thread thr1(hello, 1);

    // detach thread from main thread
    // note main thread doesn not wait for detached thread
    // if both using cout for example text can show up jumbled
    thr1.detach();

    // create thread and pass it to the guard
    try {
        std::thread thr2(hello, 2);
        thread_guard tguard{std::move(thr2)};

        throw std::exception();
    } catch (std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    std::cout << "All threads finished running \n";

    return 0;
}