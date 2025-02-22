
/*      Bu takımımız tarafından geliştirilen bir dizgi kütüphanesidir.         
                Bu kütüphane YABAN projesi için geliştirilmiştir.                    */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <condition_variable>
#include <deque>
#include <mutex>

template <typename Type>
class Queue
{
    private:
        std::mutex mutex;
        std::condition_variable condition;
        std::deque<Type> queue;

    public:
        void addValue(Type const& value) // Diziye eleman ekle.
        {
            std::unique_lock<std::mutex> lock(this->mutex);
            queue.push_front(value);
            this->condition.notify_one();
        }
        Type pop_Back() // Diziden elemen sil.
        {
            std::unique_lock<std::mutex> lock(this->mutex);
            this->condition.wait(lock, [=] { return !this->queue.empty(); });
            Type rc(std::move(this->queue.back()));
            this->queue.pop_back();
            return rc;
        }
};

#endif