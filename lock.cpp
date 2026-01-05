#include "lock.h"
#include <thread>
#include <iostream>

using namespace std;

void Source::push_(int val)
{
    q.push(val);
};

int Source::pop_()
{
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

void Producer::produce_(int val)
{
    cout << "生产者 " << this_thread::get_id() << " 生产了 :" << val << endl;
    source_.push_(val);
}

void Consumer::consume_()
{
    cout << "消费者 " << this_thread::get_id() << " 消费了 :" << source_.pop_() << endl;
}