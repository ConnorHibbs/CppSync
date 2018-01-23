#include <iostream>
#include <thread>
#include <cmath>
//#include <random>
#include <queue>
#include <mutex>

using namespace std;

typedef enum OP {PLUS, MINUS, MULTIPLY, DIVIDE};

typedef struct Equation {
    int a;
    int b;
    OP op;
};

queue pool;

mutex created_lock, consumed_lock;

int operations_created = 0;
int operations_consumed = 0;

void producer_thread() {
    int created = 0;

    while(true) {
        int a = rand();
        int b = rand();
        OP op = (OP) rand() % 4;

        Equation eq = Equation{a, b, op};


        created_lock.lock();
        created++;
        operations_created++;
        created_lock.unlock();
    }
}

void consumer_thread(Equation* eq) {

}

void producer_manager(int producers) {
    cout << "Producer Manager" << endl;
}

void consumer_manager(int consumers) {
    cout << "Consumer Manager" << endl;
}






int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;

    int queue_size = atoi(argv[1]);
    int operations = atoi(argv[2]);
    int num_producers = atoi(argv[3]);
    int num_consumers = atoi(argv[4]);

    pool = queue(queue_size);



    std::thread producer(producer_manager, num_producers);
    std::thread consumer(consumer_manager, num_consumers);

    producer.join();
    consumer.join();


    return 0;
}