#include <iostream>
#include <thread>

using namespace std;

void producer_thread() {

}

void consumer_thread() {

}

void producer_manager() {
    cout << "Producer Manager" << endl;
}

void consumer_manager() {
    cout << "Consumer Manager" << endl;
}






int main() {
    std::cout << "Hello, World!" << std::endl;


    std::thread producer(producer_manager);
    std::thread consumer(consumer_manager);

    producer.join();
    consumer.join();


    return 0;
}