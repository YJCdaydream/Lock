#include <queue>
#include <mutex>
#include <condition_variable>
#include <semaphore>
#include <thread>
#include <iostream>
using namespace std;

template <typename T>
class Source
{
private:
    std::queue<T> q;
    int capacity_ = 30;
    counting_semaphore<30> empty_{30};
    counting_semaphore<30> full_{0};

public:
    bool push_(const T &val);
    T pop_();
    std::shared_ptr<T> pop_and_wait_();
    // static Source &get_Instance_();

public:
    Source() = default;
};

template <typename T>
class Consumer
{
private:
    Source<T> &source_;

public:
    Consumer(Source<T> &src) : source_(src) {};
    void consume_();
};

template <typename T>
class Producer
{
private:
    Source<T> &source_;

public:
    Producer(Source<T> &src) : source_(src) {};
    void produce_();
};

template <typename T>
bool Source<T>::push_(const T &val)
{
    empty_.acquire();
    q.push(val);
    full_.release();
    return true;
};

template <typename T>
T Source<T>::pop_()
{
    full_.acquire();
    T val = q.front();
    q.pop();

    empty_.release();

    return val;
};

template <typename T>
std::shared_ptr<T> Source<T>::pop_and_wait_()
{
    full_.acquire();

    std::shared_ptr<T> ptr = std::make_shared<T>(q.front());
    q.pop();

    empty_.release();
    return ptr;
}

template <typename T>
void Producer<T>::produce_()
{
    for (int i = 0; i < 100; ++i)
    {
        if (source_.push_(i))
        {
            // successfully pushed
            cout << "生产者 " << this_thread::get_id() << " 放入队列 :" << i << endl;
        }
        else
        {
            // failed to push, maybe queue is full
            cout << "生产者 " << this_thread::get_id() << " 队列已满，未能放入 :" << i << endl;
        };
    }
}

template <typename T>
void Consumer<T>::consume_()
{
    for (int i = 0; i < 100; ++i)
    {
        T d = source_.pop_();
        if (d == -1)
        {
            // queue empty
            cout << "消费者 " << this_thread::get_id() << " 队列为空，未能消费" << endl;
        }
        else
        {
            // successfully popped
            cout << "消费者 " << this_thread::get_id() << " 消费了 :" << d << endl;
        }
    }
}