#include "lock.h"
#include <thread>

using namespace std;

int main()
{
    Source<int> src;
    Producer<int> p1(src);
    Consumer<int> c1(src);

    thread producer_tds[4];
    thread consume_tds[4];

    for(int i = 0; i < 4; ++i) {
        producer_tds[i] = thread(&Producer<int>::produce_, &p1); 
        consume_tds[i] = thread(&Consumer<int>::consume_, &c1); 
    }
    for(int i = 0; i < 4; ++i) {
        producer_tds[i].join();
        consume_tds[i].join();
    }
    return 0;
}