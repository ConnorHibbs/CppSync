#include <iostream>
#include <thread>

using namespace std;

typedef struct Equation {
    int a;
    int b;
    char op;
};

void producer_thread() {

}

void consumer_thread() {

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





    std::thread producer(producer_manager, num_producers);
    std::thread consumer(consumer_manager, num_consumers);

    producer.join();
    consumer.join();


    return 0;
}