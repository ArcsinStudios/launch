#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>

#if !defined(LAUNCH_NO_THREAD_SAFE)
#include <shared_mutex>
#endif

namespace launch {
	template <typename T>
	class caref {
	private:
		static std::unordered_map<T*, bool> sentinel;
#if !defined(LAUNCH_NO_THREAD_SAFE)
		static std::shared_mutex mutex_;
#endif
		T* ptr = nullptr;
		bool owner = false;

	public:
		caref() = default;

		explicit caref(T* _ptr) : ptr(_ptr), owner(true) {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock<std::shared_mutex> lock(mutex_);
#endif
			sentinel[ptr] = true;
		}

		caref(const caref<T>& other) : ptr(other.ptr), owner(false) {}

		caref(caref<T>&& other) noexcept : ptr(other.ptr), owner(true) {
			other.ptr = nullptr;
			other.owner = false;
		}

		~caref() {
			if (owner) {
#if !defined(LAUNCH_NO_THREAD_SAFE)
				std::unique_lock<std::shared_mutex> lock(mutex_);
#endif
				sentinel[ptr] = false;
				delete ptr;
			}
		}

		caref<T>& operator=(const caref<T>& other) {
			if (owner) {
				throw std::runtime_error("caref::operator=: operation tries to discard the ownership");
			}
			ptr = other.ptr;
			owner = false;
			return *this;
		}

		T& operator*() const {
			if (owner) {
				return *ptr;
			}
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::shared_lock<std::shared_mutex> lock(mutex_);
#endif
			typename std::unordered_map<T*, bool>::const_iterator it = sentinel.find(ptr);
			if (it != sentinel.end() && it->second) {
				return *ptr;
			}
			throw std::runtime_error("caref::operator*: operation tries to access a freed address");
		}

		T* operator->() const {
			try {
				**this;
			}
			catch (std::runtime_error&) {
				return nullptr;
			}
			return ptr;
		}

		void move(caref<T>& dest) {
			dest = *this;
			owner = false;
			dest.owner = true;
		}
	};

	template <typename T>
	inline std::unordered_map<T*, bool> caref<T>::sentinel;

#if !defined(LAUNCH_NO_THREAD_SAFE)
	template <typename T>
	inline std::shared_mutex caref<T>::mutex_;
#endif
}