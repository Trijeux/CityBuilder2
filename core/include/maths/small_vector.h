#ifndef CORE_MATHS_SMALL_VECTOR_H_
#define CORE_MATHS_SMALL_VECTOR_H_

#include <iostream>
#include <stdexcept>

namespace core::maths
{
	template<typename T, std::size_t Capacity>
	class SmallVector {
	public:
		// Constructor
		SmallVector() : size_(0), capacity_(Capacity) {}

		// Push back method
		void push_back(const T& value) {
			if (size_ >= capacity_) {
				throw std::overflow_error("Exceeded SmallVector capacity");
			}
			data_[size_] = value;
			++size_;
		}

		// Pop back method
		void pop_back() {
			if (size_ == 0) {
				throw std::underflow_error("Cannot pop_back from an empty SmallVector");
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
		[[nodiscard]] std::size_t size() const {
			return size_;
		}

		// Capacity method
		[[nodiscard]] std::size_t capacity() const {
			return capacity_;
		}

	private:
		T data_[Capacity];
		std::size_t size_;
		std::size_t capacity_;
	};
}

#endif  //CORE_MATHS_SMALL_VECTOR_H_