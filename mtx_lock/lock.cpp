#include "lock.h"
#include <thread>
#include <iostream>

using namespace std;

bool Source::push_(int val)
{
    lock_guard<mutex> lck(mtx_);

    // while(q.size() >= capacity_){};
    if(q.size() >= capacity_){
        this_thread::sleep_for(chrono::milliseconds(1)); // avoid busy waiting
        return false; // queue full
    }
    q.push(val);
    return true;
};

int Source::pop_()
{
    lock_guard<mutex> lck(mtx_);

    // while(q.empty()){};

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
        if(source_.push_(i)) {
            // successfully pushed
            cout << "生产者 " << this_thread::get_id() << " 放入队列 :" << i << endl;
        } else {
            // failed to push, maybe queue is full
            cout << "生产者 " << this_thread::get_id() << " 队列已满，未能放入 :" << i << endl;
        };
    }
}

void Consumer::consume_()
{
    for(int i = 0; i < 100; ++i) {
        int d = source_.pop_();
        if(d == -1) {
            // queue empty
            cout << "消费者 " << this_thread::get_id() << " 队列为空，未能消费" << endl;
        } else {
            // successfully popped
            cout << "消费者 " << this_thread::get_id() << " 消费了 :" << d << endl;
        }
    }
}