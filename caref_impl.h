#pragma once

#if !defined(LAUNCH_NO_THREAD_SAFE)
#include <shared_mutex>
#endif

#include <stdexcept>
#include <string>
#include <unordered_map>

namespace launch {
	class uaf_error final : public std::runtime_error {
	public:
		explicit uaf_error(const std::string& msg) : std::runtime_error(msg) {}

		const char* what() const noexcept override;
	};

	template <class T>
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
				throw std::runtime_error("Cannot discard an owner");
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
			throw uaf_error("Use-After-Free");
		}

		T* operator->() const {
			try {
				**this;
			}
			catch (uaf_error&) {
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

	template <class T>
	inline std::unordered_map<T*, bool> caref<T>::sentinel;

#if !defined(LAUNCH_NO_THREAD_SAFE)
	template <class T>
	inline std::shared_mutex caref<T>::mutex_;
#endif
}