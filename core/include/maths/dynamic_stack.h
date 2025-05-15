#ifndef CORE_MATHS_DYNAMICSTACK_H_
#define CORE_MATHS_DYNAMICSTACK_H_

#include <vector>

namespace core
{

template<typename T>
class DynamicStack {
private:
    std::vector<T> data_;
public:

    [[nodiscard]] std::size_t Capacity() const {
        return data_.capacity();
    }

    [[nodiscard]] std::size_t Size() const {
        return data_.size();
    }

    void push(const T& value) {
        data_.push_back(value);
    }

    void pop() {
        if (!data_.empty()) {
            data_.pop_back();
            data_.shrink_to_fit();
        }
        else {
            throw std::out_of_range("Stack underflow");
        }
    }


    T& top() {
        if (!data_.empty()) {
            return data_.back();
        }
        else {
            throw std::out_of_range("Stack is empty");
        }
    }

    [[nodiscard]] const T& top() const {
        if (!data_.empty()) {
            return data_.back();
        }
        else {
            throw std::out_of_range("Stack is empty");
        }
    }

    [[nodiscard]] bool IsEmpty() const {
        return data_.empty();
    }

}; // class DinamicStack

} // namespace core

#endif  //CORE_MATHS_DYNAMICSTACK.H_
