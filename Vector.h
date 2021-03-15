#pragma once
#include <utility>

template<typename T> 
class Vector {
public:
	Vector() {
		ReAlloc(2);
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

		m_Data[m_Size] = std::move(value); // make L value to R value
		m_Size++;
	}

	//template<typename... Args>
	//T& EmplaceBack(Args&&... args) {
	//	if (m_Size >= m_Capacity) {
	//		ReAlloc(m_Capacity + m_Capacity / 2);
	//	}

	//	m_Data[m_Size] = T(std::forward<Args>(args)...); // make L value to R value
	//	return m_Data[m_Size++];
	//}

	const T& operator[](size_t index) const {
		
		if (index >= m_Size) {
			//assert
		}
		return m_Data[index];
	}

	T& operator[](size_t index) {
		if (index >= m_Size) {
			//assert
		}
		return m_Data[index];
	}

	size_t Size() const {
		return m_Size;
	}

private:
	T* m_Data;
	size_t m_Size = 0;
	size_t m_Capacity = 0; // a growing function, so that not every time an element is added we have to reallocate | reduce number of reallocations


	void ReAlloc(size_t newCapacity) {
		// allocate a new block of memory
		// move all existing elements into new block
		// delete old block

		if (newCapacity < m_Size) {
			m_Size = newCapacity;
		}

		T* newBlock = new T[newCapacity];
		for (size_t i = 0; i < m_Size; i++) {
			newBlock[i] = std::move(m_Data[i]);
		}
		delete[] m_Data;
		m_Data = newBlock;
		m_Capacity = newCapacity;
	}

};

