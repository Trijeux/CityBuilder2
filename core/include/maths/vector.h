#ifndef CORE_MATHS_VECTOR_H_
#define CORE_MATHS_VECTOR_H_

#include <vector>
#include <stdexcept>
#include <memory>

namespace core
{
    template<typename T, class Allocator = std::allocator<T>, std::size_t GrowthDividend = 3, std::size_t GrowthDivisor = 2>
    class Vector {
    private:
        std::vector<T, Allocator> data_;

        void grow_if_needed() {
            if (data_.size() == data_.capacity()) {
                std::size_t new_capacity = (data_.capacity() * GrowthDividend) / GrowthDivisor;
                data_.reserve(new_capacity);
            }
        }

    public:
        Vector() = default;

        void push_back(const T& value) {
            grow_if_needed();
            data_.push_back(value);
        }

        void pop_back() {
            if (data_.empty()) {
                throw std::out_of_range("Vector is empty");
            }
            data_.pop_back();

            // Si la taille devient zéro, réinitialiser la capacité à zéro
            if (data_.empty()) {
                data_.shrink_to_fit();
            }
        }

        T& operator[](std::size_t index) {
            return data_[index];
        }

        const T& operator[](std::size_t index) const {
            return data_[index];
        }

        std::size_t size() const {
            return data_.size();
        }

        std::size_t capacity() const {
            return data_.capacity();
        }

        void reserve(std::size_t new_cap) {
            data_.reserve(new_cap);
        }

        void resize(std::size_t new_size) {
            data_.resize(new_size);
        }

        bool IsEmpty() const {
            return data_.empty();
        }

        void clear() {
            data_.clear();
            data_.shrink_to_fit(); // Réinitialiser la capacité à zéro lorsque la taille devient zéro
        }
    };
}

#endif //CORE_MATHS_VECTOR_H_
