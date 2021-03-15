#include "Vector.h"
#include <string>
#include <iostream>
#include <string>

struct Vector3 {
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int* m_memory_block = nullptr;

	Vector3() {
		m_memory_block = new int[5];
	}
	Vector3(float scalar) 
		: x(scalar), y(scalar), z(scalar) {
		m_memory_block = new int[5];
	}
	Vector3(float x, float y, float z)
		: x(x), y(y), z(z){
		m_memory_block = new int[5];
	}

	Vector3(const Vector3& other)
		: x(other.x), y(other.y), z(other.z) {
		m_memory_block = other.m_memory_block;
		std::cout << "Copy\n";
	}

	Vector3(Vector3&& other) 
		: x(other.x), y(other.y), z(other.z) {
		m_memory_block = other.m_memory_block;
		other.m_memory_block = nullptr;
		std::cout << "Move\n";
	}

	~Vector3() {
		std::cout << "Destroy\n";
		delete[] m_memory_block;
	}

	Vector3& operator=(const Vector3& other) {
		std::cout << "Copy\n";

		m_memory_block = other.m_memory_block;
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vector3& operator=(Vector3&& other) {
		m_memory_block = other.m_memory_block;
		other.m_memory_block = nullptr;
		std::cout << "Move\n";

		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}
};

// printing the vector using an iterator
template<typename T>
void print_vector(const Vector<T>& vector) {
	std::cout << "Printing the vector using an iterator:\n";
	for (auto it = vector.begin(); it != vector.end(); ++it) {
		std::cout << *it << std::endl;
	}
		
	std::cout << "------------------\n\n";
	std::cout << "Size: " << vector.size() << " Capacity: " << vector.capacity() << std::endl << std::endl;
}

// printing the vector using an iterator
template<>
void print_vector(const Vector<Vector3>& vector) {
	std::cout << "Printing the vector using an iterator:\n";
	for (auto it = vector.begin(); it != vector.end(); ++it) {
		std::cout << it->x << ", " << it->y << ", " << it->z << std::endl;
	}

	std::cout << "------------------\n\n";
	std::cout << "Size: " << vector.size() << " Capacity: " << vector.capacity() << std::endl << std::endl;
}

// printing the vector from raw pointer
template<typename T>
void print_as_array(Vector<T>& vector) {	
	std::cout << "Printing the vector from raw pointer:\n";
	for (uint32_t i = 0; i < vector.size(); i++) {
		std::cout << *(vector.as_array() + i) << std::endl;
	}

	std::cout << "------------------\n\n";
	std::cout << "Size: " << vector.size() << " Capacity: " << vector.capacity() << std::endl << std::endl;
}

int main() {
	std::cout << "Creating string vector and adding some elements:\n";
	Vector<std::string> vector;
	std::string s = "Blaaa";
	vector.push_back("Bla0");
	vector.push_back("Bla1");
	vector.push_back("Bla2");
	vector.push_back(s);
	vector.push_back("Bla3");
	vector.push_back("Bla4");
	vector.push_back("Bla5");
	vector.push_back("Bla6");
	print_vector(vector);

	std::cout << "Removing element on 3 by swap:\n";
	vector.erase_by_swap(3);
	print_as_array(vector);

	std::cout << "Removing element on 3:\n";
	vector.erase(3);
	print_as_array(vector);

	std::cout << "Removing elements between 2 and 5:\n";
	vector.erase(2, 5);
	print_as_array(vector);

	std::cout << "Adding some elements:\n";
	vector.push_back("Bla2");
	vector.push_back("Bla3");
	vector.push_back("Bla4");
	vector.push_back("Bla5");
	vector.push_back("Bla6");
	print_as_array(vector);

	std::cout << "Removing elements between 3 and 5:\n";
	vector.erase(3, 5);
	print_as_array(vector);

	std::cout << "Adding some elements:\n";
	vector.push_back("Bla12");
	vector.push_back("Bla13");
	vector.push_back("Bla14");
	vector.push_back("Bla15");
	vector.push_back("Bla16");
	print_as_array(vector);

	std::cout << "Removing elements between 0 and 3:\n";
	vector.erase(0, 3);
	print_as_array(vector);

	std::cout << "Removing elements between 2 and 2:\n";
	vector.erase(2, 2);
	print_as_array(vector);

	std::cout << "Reserving a capacity of 14:\n";
	vector.reserve(14);
	std::cout << "Size: " << vector.size() << " Capacity: " << vector.capacity() << std::endl << std::endl;

	std::cout << "Resizing Vector to size 2:\n";
	vector.resize(2);
	print_as_array(vector);

	{
		std::cout << "Creating vector3 vector and adding some elements; printing copy, move and delete behaviour:\n";
		Vector<Vector3> vector3;
		vector3.push_back(Vector3(1.0f));
		vector3.push_back(Vector3(1, 2, 3));
		vector3.push_back(Vector3());

		std::cout << std::endl;
		print_vector(vector3);

		std::cout << "Removing an object from the back:\n";
		vector3.pop_back();
		std::cout << std::endl;
		print_vector(vector3);

		std::cout << "Adding some elements:\n";
		vector3.push_back(Vector3(1.0f));
		vector3.push_back(Vector3(1, 2, 3));
		vector3.push_back(Vector3());
		print_vector(vector3);

		std::cout << "Removing elements on 3:\n";
		vector3.erase(3);
		print_vector(vector3);

		std::cout << "Resizing Vector to size 8:\n";
		vector3.resize(8);
		print_vector(vector3);

		std::cout << "Leaving scope of vector3 vector:\n";
	}
}