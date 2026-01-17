#include "lock.h"
#include <thread>
#include <iostream>

using namespace std;

bool Source::push_(int val)
{
    unique_lock<mutex> lck(mtx_);
    cv_not_full_.wait(lck, [this](){ return q.size() < capacity_; });

    q.push(val);
    
    cv_not_empty_.notify_one();
    return true;
};

int Source::pop_()
{
    unique_lock<mutex> lck(mtx_);
    cv_not_empty_.wait(lck, [this](){ return !q.empty(); });

    int val = q.front();
    q.pop();

    cv_not_full_.notify_one();
    return val;

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