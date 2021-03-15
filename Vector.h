#pragma once
#include <utility>
#include <cassert>
#include <new>
#include <stdint.h>

template<typename T> 
class Vector {
public:
	Vector() {
		ReAlloc(2);
	}

	~Vector() {
		Clear();
		::operator delete(m_Data, m_Capacity * sizeof(T));
	}

	void PushBack(const T& value) {
		if (m_Size >= m_Capacity) {
			ReAlloc(m_Capacity + m_Capacity / 2);
		}

		m_Data[m_Size] = value;
		m_Size++;
	}

	void PushBack(T&& value) {
		if (m_Size >= m_Capacity) {
			ReAlloc(m_Capacity + m_Capacity / 2);
		}

		new(m_Data + m_Size) T(std::move(value)); // make L value to R value
		m_Size++;
	}

	template<typename... Args>
	T& EmplaceBack(Args&&... args) {
		if (m_Size >= m_Capacity) {
			ReAlloc(m_Capacity + m_Capacity / 2);
		}
		new(m_Data + m_Size) T(std::forward<Args>(args)...); // construct object in place
		return m_Data[m_Size++];
	}

	void PopBack() {
		if (m_Size > 0) {
			m_Size--;
			m_Data[m_Size].~T();
		}
	}

	void Clear() {
		for (uint32_t i = 0; i < m_Size; i++) {
			m_Data[i].~T();
		}
		m_Size = 0;
	}

	const T& operator[](const uint32_t index) const {
		
		assert(index >= m_Size);
		return m_Data[index];
	}

	T& operator[](const uint32_t index) {
		assert(index >= m_Size);
		return m_Data[index];
	}

	uint32_t Size() const {
		return m_Size;
	}

private:
	T* m_Data = nullptr;
	uint32_t m_Size = 0;
	uint32_t m_Capacity = 0; // reduce number of reallocations


	void ReAlloc(const uint32_t newCapacity) {
		// allocate a new block of memory
		// move all existing elements into new block
		// delete old block

		if (newCapacity < m_Size) {
			m_Size = newCapacity;
		}

		T* newBlock = (T*)::operator new(newCapacity * sizeof(T));
		for (uint32_t i = 0; i < m_Size; i++) {
			new (newBlock + i) T(std::move(m_Data[i]));
		}
		for (uint32_t i = 0; i < m_Size; i++) {
			m_Data[i].~T();
		}
		::operator delete(m_Data, m_Capacity * sizeof(T));
		m_Data = newBlock;
		m_Capacity = newCapacity;
	}

};

