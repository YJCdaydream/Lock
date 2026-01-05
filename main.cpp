#include "lock.h"
#include <thread>

using namespace std;

int main()
{

    Producer p1(Source::get_Instance_());
    Consumer c1(Source::get_Instance_());

    thread producer_tds[100];
    thread consume_tds[100];

    for (int i = 0; i < 100; i++)
    {
        producer_tds[i] = thread(&Producer::produce_, &p1, i); 
        consume_tds[i] = thread(&Consumer::consume_, &c1); 
    }

    for(int i = 0; i < 100; i++)
    {
        producer_tds[i].join();
        consume_tds[i].join();
    }
    return 0;
}