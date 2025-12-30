#pragma once

#include <algorithm>
#include <functional>
#include <new>
#include <stdexcept>
#include <utility>
#include <vector>

namespace launch {
	namespace leisure {
		class lidevec_elemnode {
		public:
			static const size_t npos = 18446744073709551615Ui64;

			size_t next_vidx;
			signed char status;

			lidevec_elemnode() : next_vidx(npos), status(0) {}
		};
	
		template <typename T>
		class lidevec {
		private:
			static const size_t init_size = 32;
			static const size_t expand_by = 2;

			std::vector<std::pair<T*, size_t>> mem_blocks;
			std::vector<T*> vidx_map;
			std::vector<lidevec_elemnode> node_map;
			size_t head_vidx;
			size_t tail_vidx;
			size_t cached_lidx;
			size_t cached_vidx;

			size_t size_;
			size_t capacity_;
			size_t high_tide;

			void _Map() {
				for (size_t i = 0; i < mem_blocks.back().second; ++i) {
					vidx_map.push_back(mem_blocks.back().first + i);
					node_map.push_back(lidevec_elemnode());
				}
			}

			void _Expand() {
				size_t expand_size = capacity_ * (expand_by - 1);
				std::pair<T*, size_t> _Pair;
				_Pair.first = (T*)::operator new[](sizeof(T) * expand_size);
				_Pair.second = expand_size;
				mem_blocks.push_back(_Pair);
				capacity_ *= expand_by;
				_Map();
			}

			size_t _Vidx_at(size_t index) {
				if (index == cached_lidx) {
					return cached_vidx;
				}
				size_t i = 0;
				size_t vidx = head_vidx;
				if (index > cached_lidx) {
					i = cached_lidx;
					vidx = cached_vidx;
				}
				for (; i < index; ++i) {
					vidx = node_map[vidx].next_vidx;
				}
				cached_lidx = index;
				cached_vidx = vidx;
				return vidx;
			}

			size_t _Free_slot() const {
				if (high_tide < capacity_ && high_tide <= size_) {
					return high_tide;
				}
				for (size_t i = 0; i < high_tide; ++i) {
					if (node_map[i].status != 1) {
						return i;
					}
				}
				return lidevec_elemnode::npos;
			}

			void _Reset_cache() {
				cached_lidx = 0;
				cached_vidx = head_vidx;
			}

		public:
			lidevec() :
				head_vidx(lidevec_elemnode::npos),
				tail_vidx(lidevec_elemnode::npos),
				cached_lidx(0),
				cached_vidx(0),
				size_(0),
				capacity_(init_size)
			{
				std::pair<T*, size_t> _Pair;
				_Pair.first = (T*)::operator new[](sizeof(T) * init_size);
				_Pair.second = init_size;
				mem_blocks.push_back(_Pair);
				_Map();
			}

			~lidevec() {
				for (size_t i = 0; i < capacity_; ++i) {
					if (node_map[i].status != 0) {
						vidx_map[i]->~T();
					}
				}
				for (const std::pair<T*, size_t>& block : mem_blocks) {
					::operator delete[](block.first);
				}
			}

			lidevec(const lidevec<T>& other) = delete;

			lidevec<T>& operator=(const lidevec<T>& other) = delete;

			lidevec(lidevec<T>&& other) = delete;

			lidevec<T>& operator=(lidevec<T>&& other) = delete;

			T& operator[](size_t index) {
				return *vidx_map[_Vidx_at(index)];
			}

			T& at(size_t index) {
				if (index >= size_) {
					throw std::out_of_range(
						"lidevec::at: index (which is " +
						std::to_string(index) +
						") >= size_ (which is " +
						std::to_string(size_) +
						")"
					);
				}
				return (*this)[index];
			}

			T& front() const {
				return *vidx_map[head_vidx];
			}

			T& back() const {
				return *vidx_map[tail_vidx];
			}

			size_t size() const {
				return size_;
			}

			size_t capacity() const {
				return capacity_;
			}

			bool empty() const {
				return size_ == 0;
			}

			void reserve(size_t _capacity) {
				if (_capacity <= capacity_) {
					return;
				}
				size_t expand_size = _capacity - capacity_;
				std::pair<T*, size_t> _Pair;
				_Pair.first = (T*)::operator new[](sizeof(T) * (expand_size));
				_Pair.second = expand_size;
				mem_blocks.push_back(_Pair);
				capacity_ = _capacity;
				_Map();
			}

			void push_back(const T& value) {
				size_t slot = _Free_slot();
				if (slot == lidevec_elemnode::npos) {
					_Expand();
					slot = _Free_slot();
				}
				if (node_map[slot].status == -1) {
					vidx_map[slot]->~T();
				}
				new (vidx_map[slot]) T(value);
				node_map[slot].status = 1;
				if (size_ == 0) {
					head_vidx = slot;
				}
				else {
					node_map[tail_vidx].next_vidx = slot;
				}
				tail_vidx = slot;
				++size_;
				high_tide = std::max(size_, high_tide);
			}

			void pop_back() {
				if (size_ == 0) {
					return;
				}
				if (cached_vidx == tail_vidx) {
					_Reset_cache();
				}
				if (size_ == 1) {
					node_map[head_vidx].status = -1;
					head_vidx = lidevec_elemnode::npos;
					tail_vidx = lidevec_elemnode::npos;
				}
				else {
					size_t before_tail = _Vidx_at(size_ - 2);
					node_map[tail_vidx].status = -1;
					tail_vidx = before_tail;
					node_map[tail_vidx].next_vidx = lidevec_elemnode::npos;
				}
				--size_;
			}

			void insert(size_t index, const T& value) {
				if (index > size_) {
					return;
				}
				if (index == size_) {
					this->push_back(value);
					return;
				}
				size_t slot = _Free_slot();
				if (slot == lidevec_elemnode::npos) {
					_Expand();
					slot = _Free_slot();
				}
				if (node_map[slot].status == -1) {
					vidx_map[slot]->~T();
				}
				new (vidx_map[slot]) T(value);
				node_map[slot].status = 1;
				if (index == 0) {
					node_map[slot].next_vidx = head_vidx;
					head_vidx = slot;
				}
				else {
					size_t thumb = _Vidx_at(index - 1);
					size_t middle = node_map[thumb].next_vidx;
					node_map[thumb].next_vidx = slot;
					node_map[slot].next_vidx = middle;
				}
				++size_;
				if (cached_lidx >= index) {
					++cached_lidx;
				}
				high_tide = std::max(size_, high_tide);
			}

			void erase(size_t index) {
				if (index >= size_) {
					return;
				}
				if (index == size_ - 1) {
					this->pop_back();
					return;
				}
				if (index == 0) {
					node_map[head_vidx].status = -1;
					head_vidx = node_map[head_vidx].next_vidx;
				}
				else {
					size_t thumb = _Vidx_at(index - 1);
					size_t index_vidx = node_map[thumb].next_vidx;
					node_map[thumb].next_vidx = node_map[index_vidx].next_vidx;
					node_map[index_vidx].status = -1;
				}
				--size_;
				if (cached_lidx == index) {
					_Reset_cache();
				}
				else if (cached_lidx > index) {
					--cached_lidx;
				}
			}

			void clear() {
				for (lidevec_elemnode& node : node_map) {
					if (node.status == 1) {
						node.status = -1;
					}
				}
				size_ = 0;
				head_vidx = lidevec_elemnode::npos;
				tail_vidx = lidevec_elemnode::npos;
				_Reset_cache();
			}

			void for_each(const std::function<void(T&)>& func) {
				for (size_t i = head_vidx; i != lidevec_elemnode::npos; i = node_map[i].next_vidx) {
					func(*vidx_map[i]);
				}
			}
		};
	}
}