#ifndef CORE_MATHS_FIXEDQUEUE_H_
#define CORE_MATHS_FIXEDQUEUE_H_
#include <array>

namespace core
{

	template<typename T, std::size_t N>
	class FixedQueue {
	private:
		std::array<T, N> data_;
		std::size_t front_, rear_, size_;
	public:
		FixedQueue() : front_(0), rear_(N - 1), size_(0) {}

		std::size_t Capacity() const
		{
			return data_.size();
		}

		auto Size() const
		{
			return size_;
		}

		void enqueue(const T& value) {
			if (size_ < N) {
				rear_ = (rear_ + 1) % N;
				data_[rear_] = value;
				++size_;
			}
			else {
				throw std::out_of_range("Queue overcapacity");
			}
		}

		void dequeue() {
			if (size_ > 0) {
				front_ = (front_ + 1) % N;
				--size_;
			}
			else {
				throw std::out_of_range("Queue is empty");
			}
		}

		T& front() {
			if (size_ > 0) {
				return data_[front_];
			}
			else {
				throw std::out_of_range("Queue is empty");
			}
		}


		[[nodiscard]] const T& front() const
		{
			if (size_ > 0) {
				return data_[front_];
			}
			else {
				throw std::out_of_range("Queue is empty");
			}
		}

		[[nodiscard]] bool IsEmpty() const {
			return size_ == 0;
		}

	}; // class FixedQueue

} // namespace core

#endif  //CORE_MATHS_FIXEDQUEUE.H_

