c++锁的简单复习
总体为
  source对象
  producer对象
  consumer对象
在main函数中实现了分别4个生成者，4个消费者来对资源进行生产和消耗


unlock：为无锁版本、会因为线程竞争而触发崩溃

mutex：为最简单的mutex控制，但是任然会导致cpu空转，无法成功生产、以及成功消费的现象

condition：加入了条件变量，可以避免cpu空转；即空满则阻塞等待，并条件唤醒生产者和消费者

template:使用模板类来实现resource，则可接受任意资源类型，包括大体积对象。并且引入shared_ptr来缓冲弹出栈；
