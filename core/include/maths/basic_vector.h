#ifndef CORE_MATHS_BASICVECTOR_H_
#define CORE_MATHS_BASICVECTOR_H_

#include <iostream>
#include <iterator>

namespace core
{
    template<typename T, std::size_t StackSize>
    class BasicVector {
    public:
        // Constructor
        BasicVector() : size_(0), capacity_(StackSize), data_(stackData_) {}

        // Destructor
        ~BasicVector() {
            if (data_ != stackData_) {
                delete[] data_;
            }
        }

        // Push back method
        void push_back(const T& value) {
            if (size_ == capacity_) {
                reserve(std::max(capacity_ * 2, StackSize));
            }
            data_[size_] = value;
            ++size_;
        }

        void pop_back() {
            if (size_ == 0) {
                throw std::out_of_range("Vector is empty");
            }
            --size_;
        }

        // Operator[] method
        T& operator[](std::size_t index) {
            if (index >= size_) {
                throw std::out_of_range("Index out of bounds");
            }
            return data_[index];
        }

        // Const version of Operator[] method
        const T& operator[](std::size_t index) const {
            if (index >= size_) {
                throw std::out_of_range("Index out of bounds");
            }
            return data_[index];
        }


        // Reserve method
        void reserve(std::size_t new_capacity) {
            if (new_capacity <= capacity_) return;

            T* new_data = new T[new_capacity];
            for (std::size_t i = 0; i < size_; ++i) {
                new_data[i] = std::move(data_[i]);
            }

            if (data_ != stackData_) {
                delete[] data_;
            }

            data_ = new_data;
            capacity_ = new_capacity;
        }

        // Begin method
        T& begin() {
            if (size_ == 0) {
                throw std::out_of_range("Vector is empty");
            }
            return data_[0];
        }

        // Const begin method
        const T& begin() const {
            if (size_ == 0) {
                throw std::out_of_range("Vector is empty");
            }
            return data_[0];
        }

        // End method
        T& end() {
            if (size_ == 0) {
                throw std::out_of_range("Vector is empty");
            }
            return data_[size_ - 1];
        }

        // Const begin method
        const T& end() const {
            if (size_ == 0) {
                throw std::out_of_range("Vector is empty");
            }
            return data_[size_ - 1];
        }

        // Size method
        std::size_t size() const {
            return size_;
        }

        // Capacity method
        std::size_t capacity() const {
            return capacity_;
        }

    private:
        T stackData_[StackSize];   // Stack-allocated array
        T* data_;                  // Pointer to the data (either stackData_ or heap-allocated)
        std::size_t size_;         // Current size of the vector
        std::size_t capacity_;     // Current capacity of the vector
    };

}

#endif  //CORE_MATHS_BASICVECTOR.H_