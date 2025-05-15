#ifndef CORE_MATHS_FIXEDSTACK_H_
#define CORE_MATHS_FIXEDSTACK_H_

#include <array>

namespace core
{

template<typename T, std::size_t N>
class FixedStack {
private:
    std::array<T, N> data_;
    std::size_t top_;
public:
    FixedStack() : top_(0) {}

    std::size_t Capacity()
    {
        return data_.size();
    }

    [[nodiscard]] std::size_t Size() const {
        return top_;
    }

    void push(const T& value) {
        if (top_ < N) {
            data_[top_++] = value;
        }
        else {
            throw std::out_of_range("Stack overflow");
        }
    }

    void pop() {
        if (top_ > 0) {
            --top_;
        }
        else {
            throw std::out_of_range("Stack underflow");
        }
    }

    T& top() {
        if (top_ > 0) {
            return data_[top_ - 1];
        }
        else {
            throw std::out_of_range("Stack is empty");
        }
    }

    [[nodiscard]] const T& top() const {
        if (top_ > 0) {
            return data_[top_ - 1];
        }
        else {
            throw std::out_of_range("Stack is empty");
        }
    }

    [[nodiscard]] bool IsEmpty() const {
        return top_ == 0;
    }

}; // class FixedStack

} // namespace core

#endif  //CORE_MATHS_FIXEDSTACK.H_
