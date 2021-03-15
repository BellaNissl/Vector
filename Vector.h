#pragma once
#include <utility>
#include <cassert>
#include <new>
#include <stdint.h>
#include <algorithm>
#include <iostream>

template<typename T> 
class Vector {
public:
	Vector() : m_data(nullptr), m_size(0), m_capacity(0){
	}

	~Vector() {
		clear();
		::operator delete(m_data, m_capacity * sizeof(T));
	}

	void push_back(const T& value) {
		uint32_t new_size = m_size + 1;
		if (new_size >= m_capacity) {
			re_alloc(new_size);
		}

		new(m_data + m_size) T(value);
		m_size = new_size;
	}

	void push_back(T&& value) {
		uint32_t new_size = m_size + 1;
		if (new_size >= m_capacity) {
			re_alloc(new_size); 
		}

		new(m_data + m_size) T(std::move(value)); // make L value to R value
		m_size = new_size;
	}

	void pop_back() {
		if (m_size > 0) {
			m_size--;
			m_data[m_size].~T();
		}
	}

	void erase_by_swap(const uint32_t index) {
		m_size--;
		if (index != m_size) {
			m_data[index] = std::move(m_data[m_size]);
		}
		m_data[m_size].~T();
	}

	void erase(const uint32_t index) {
		erase(index, index);
	}

	void erase(const uint32_t from, const uint32_t to) {
		uint32_t start = to + 1;
		uint32_t diff = m_size - start;
		
		for (uint32_t i = 0; i < diff; i++) {
			m_data[from + i] = std::move(m_data[start + i]);
		}

		diff = start - from;
		uint32_t old_size = m_size;
		for (uint32_t i = old_size - 1; i >= old_size - diff; i--) {
			m_data[i].~T();
			m_size--;
		}
	}

	void clear() {
		for (uint32_t i = 0; i < m_size; i++) {
			m_data[i].~T();
		}
		m_size = 0;
	}

	const T& operator[](const uint32_t index) const {
		return m_data[index];
	}

	T& operator[](const uint32_t index) {
		return m_data[index];
	}

	uint32_t size() const {
		return m_size;
	}

	uint32_t capacity(void) const { 
		return m_capacity; 
	}

	T* as_array(void) const { 
		return m_data; 
	}

	T* begin() const {
		return m_data;
	}

	T* end() const {
		return m_data + m_size;
	}

	T& at(uint32_t index) {
		// at is [] with range check
		assert(index >= 0 && index < m_size);
		return (*this)[index];
	}

	const T& at(const uint32_t index) const {
		// at is [] with range check
		assert(index >= 0 && index < m_size);
		return (*this)[index];
	}

	void reserve(const uint32_t new_capacity) {
		if (new_capacity <= m_capacity) {
			return;
		}
		re_alloc(new_capacity, true);
	}

	void resize(const uint32_t new_size, const T& t) {
		if (new_size == m_size) {
			return;
		}
		if (new_size < m_size) {
			erase(new_size, m_size - 1);
			return;
		}
		
		for (uint32_t i = m_size; i < new_size; i++) {
			push_back(t);
		}
		m_size = new_size;
	}

	void resize(const uint32_t new_size) {
		resize(new_size, T());
	}

private:
	T* m_data;
	uint32_t m_size;
	uint32_t m_capacity; 

	void re_alloc(const uint32_t new_size, bool absolute = false) {
		uint32_t new_capacity = new_size;
		if (new_size < m_size) {
			m_size = new_size;
		}
		else if (absolute) { // true if we want the new capacity to equal exatly the new size
			new_capacity = new_size;
		} 
		else {
			// reducing number of reallocations by increasing capacity in bigger steps
			new_capacity = m_size + (m_size / 2); 
			new_capacity = new_capacity >= new_size ? new_capacity : new_size;
		}

		// allocating new block of memory
		T* new_block = (T*)::operator new(new_capacity * sizeof(T));

		// moving all existing elements into new block
		for (uint32_t i = 0; i < m_size; i++) {
			new (new_block + i) T(std::move(m_data[i]));
		}

		// deleting old block
		for (uint32_t i = 0; i < m_size; i++) {
			m_data[i].~T();
		}
		::operator delete(m_data, m_capacity * sizeof(T));


		m_data = new_block;
		m_capacity = new_capacity;
	}
};

