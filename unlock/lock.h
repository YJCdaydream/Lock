#include <queue>

class Source
{
private:
    std::queue<int> q;
    int capacity_ = 30;

public:
    void push_(int val);
    int pop_();
    static Source &get_Instance_();

public:
    Source() = default;
    Source(const Source &) = delete; // 拷贝构造
    Source &operator=(const Source &) = delete;
};

class Consumer
{
private:
    Source &source_;
    

public:
    Consumer(Source &src) : source_(src) {};
    void consume_();
};

class Producer
{
private:
    Source &source_;

public:
    Producer(Source &src) : source_(src) {}; 
    void produce_();
};