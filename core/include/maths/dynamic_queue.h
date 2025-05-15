#ifndef CORE_MATHS_DYNAMICQUEUE_H_
#define CORE_MATHS_DYNAMICQUEUE_H_

#include <vector>
#include <stdexcept>

namespace core {

template<typename T>
class DynamicQueue {
private:
    std::vector<T> data_;
    std::size_t front_;
    std::size_t back_;
    std::size_t size_;

public:
    DynamicQueue() : front_(0), back_(0), size_(0) {}

    void enqueue(const T& value) {
        if (size_ == data_.size()) {
            data_.push_back(value);
        }
        else {
            data_[back_] = value;
        }
        back_ = (back_ + 1) % data_.capacity();
        size_++;
    }

    void dequeue() {
        if (IsEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        front_ = (front_ + 1) % data_.capacity();
        size_--;

        // Update back_ to reflect the new size of the queue
        back_ = front_ + size_;

        // Reduce capacity to fit the size
        std::vector<T>(data_.begin() + front_, data_.begin() + back_).swap(data_);
        back_ -= front_; // Adjust back_ to start from 0
        front_ = 0;
    }

    T& front() {
        if (IsEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data_[front_];
    }

    [[nodiscard]] const T& front() const {
        if (IsEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data_[front_];
    }

    [[nodiscard]] std::size_t Capacity() const {
        return data_.capacity();
    }

    [[nodiscard]] std::size_t Size() const {
        return size_;
    }

    [[nodiscard]] bool IsEmpty() const {
        return size_ == 0;
    }

}; // class DynamicQueue

} // namespace core

#endif  // CORE_MATHS_DYNAMICQUEUE_H_
