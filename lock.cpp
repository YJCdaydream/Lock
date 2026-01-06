#include "lock.h"
#include <thread>
#include <iostream>

using namespace std;

void Source::push_(int val)
{
    while (capacity_ <= q.size()){};
    
    q.push(val);
};

int Source::pop_()
{
    while(q.empty()){};
    if (!q.empty())
    {
        int val = q.front();
        q.pop();
        return val;
    }
    return -1; // or throw an exception
};

Source &Source::get_Instance_()
{
    static Source instance;
    return instance;
};

void Producer::produce_()
{
    for(int i = 0; i < 100; ++i) {
        cout << "生产者 " << this_thread::get_id() << " 生产了 :" << i << endl;
        source_.push_(i);
    }
}

void Consumer::consume_()
{
    for(int i = 0; i < 100; ++i) {
        cout << "消费者 " << this_thread::get_id() << " 消费了 :" << source_.pop_() << endl;
    
    }
}