#include "Vector.h"
#include <string>
#include <iostream>
#include <string>

struct Vector3 {
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int* m_MemoryBlock = nullptr;

	Vector3() {
		m_MemoryBlock = new int[5];
	}
	Vector3(float scalar) 
		: x(scalar), y(scalar), z(scalar) {
		m_MemoryBlock = new int[5];
	}
	Vector3(float x, float y, float z)
		: x(x), y(y), z(z){
		m_MemoryBlock = new int[5];
	}

	Vector3(const Vector3& other)
		: x(other.x), y(other.y), z(other.z) {
		m_MemoryBlock = other.m_MemoryBlock;
		std::cout << "Copy\n";
	}

	Vector3(Vector3&& other) 
		: x(other.x), y(other.y), z(other.z) {
		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;
		std::cout << "Move\n";
	}

	~Vector3() {
		std::cout << "Destroy\n";
		delete[] m_MemoryBlock;
	}

	Vector3& operator=(const Vector3& other) {
		std::cout << "Copy\n";

		m_MemoryBlock = other.m_MemoryBlock;
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vector3& operator=(Vector3&& other) {
		m_MemoryBlock = other.m_MemoryBlock;
		other.m_MemoryBlock = nullptr;
		std::cout << "Move\n";

		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}
};

template<typename T>
void PrintVector(const Vector<T>& vector) {
	for (uint32_t i = 0; i < vector.Size(); i++) {
		std::cout << vector[i] << std::endl;
	}

	std::cout << "------------------\n";
}
template<>
void PrintVector(const Vector<Vector3>& vector) {
	for (size_t i = 0; i < vector.Size(); i++) {
		std::cout << vector[i]. x << ", " << vector[i].y << ", " << vector[i].z << std::endl;
	}

	std::cout << "------------------\n";
}

int main() {

	Vector<std::string> vector;
	std::string s = "Blaaa";
	vector.PushBack("Bla");
	vector.PushBack("Bla2");
	vector.PushBack("Bla3");
	vector.PushBack("Bla3");
	vector.PushBack("Bla3");
	vector.PushBack("Bla3");
	vector.PushBack("Bla3");
	vector.PushBack("Bla3");

	//PrintVector(vector);
	//{
	//	Vector<Vector3> vector3;
	//	vector3.EmplaceBack(1.0f);
	//	vector3.EmplaceBack(1, 2, 3);
	//	vector3.EmplaceBack();

	//	PrintVector(vector3);
	//}
}