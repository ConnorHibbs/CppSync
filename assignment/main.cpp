#include <iostream>
#include <thread>
#include <cmath>
//#include <random>
#include <queue>
#include <mutex>

#include <semaphore.h>

using namespace std;

typedef enum OP {PLUS, MINUS, MULTIPLY, DIVIDE};

typedef struct Equation {
    int a;
    int b;
    OP op;
    long answer;
};

queue<Equation> pool;

mutex created_lock, consumed_lock;

sem_t enqueue_semaphore;

int operations_created = 0;
int operations_consumed = 0;


// Function Definitions
void evaluate(Equation*);
char get_symbol(OP);

void producer_thread() {
    int created = 0;

    while(true) {
        int a = rand();
        int b = rand();
        OP op = (OP) rand() % 4;

        // Create a new equation
        Equation eq = Equation{a, b, op};

        // Wait for an opening in the queue
        sem_wait(&enqueue_semaphore);

        // Add the equation to the work queue
        pool.push(eq);

        // Increment the global scope variables
        created_lock.lock();
        created++;
        operations_created++;
        created_lock.unlock();
    }
}

void consumer_thread() {
    int consumed = 0;

    while(true) {
        Equation eq = pool.front();
        sem_post(&enqueue_semaphore);

        char c = get_symbol(eq.op);
        evaluate(&eq);
        printf("%d %c %d = %d", eq.a, c, eq.b, eq.answer);
        // TODO stuff

        consumed_lock.lock();
        consumed++;
        operations_consumed++;
        consumed_lock.unlock();
    }
}

void producer_manager(int producers) {
    cout << "Producer Manager" << endl;
}

void consumer_manager(int consumers) {
    cout << "Consumer Manager" << endl;
}

char get_symbol(OP op) {
    switch(op) {
        case PLUS:     return '+';
        case MINUS:    return '-';
        case MULTIPLY: return '*';
        case DIVIDE:   return '/';
    }
}

void evaluate(Equation* eq) {
    switch(eq->op) {
        case PLUS: eq->answer = eq->a + eq->b;
            break;
        case MINUS: eq->answer = eq->a - eq->b;
            break;
        case MULTIPLY: eq->answer = eq->a * eq->b;
            break;
        case DIVIDE: eq->answer = eq->a / eq->b;
    }
}




int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;

    auto queue_size = static_cast<unsigned int>(atoi(argv[1]));
    int operations = atoi(argv[2]);
    int num_producers = atoi(argv[3]);
    int num_consumers = atoi(argv[4]);

    sem_init(&enqueue_semaphore, 0, queue_size);

    std::thread producer(producer_manager, num_producers);
    std::thread consumer(consumer_manager, num_consumers);

    producer.join();
    consumer.join();


    return 0;
}