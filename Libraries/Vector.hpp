#ifndef VECTOR_H
#define VECTOR_H
#include <cstdio>
#include <initializer_list>

template <typename Type>
class Vector
{
public:
	class Iterator
	{
	public:
		Iterator() : ptr(nullptr), index(0) {}
		Iterator(Vector<Type> *_vec) : ptr(_vec), index(0) {}
		Iterator(Vector<Type> *_vec, int _index) : ptr(_vec), index(_index) {}

		Type &operator*() { return (*ptr)[index]; }
		Type *operator->() { return &((*ptr)[index]); }
		const Type *operator->() const { return &((*ptr)[index]); }
		Type &operator[](const int _index) { return (*ptr)[index + _index]; }

		Iterator &operator++()
		{
			++index;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator curr(*this);
			++(*this);
			return current;
		}

		bool operator!=(const Iterator &r) const { return index != r.index; }
		bool operator==(const Iterator &r) const { return index == r.index; }

	private:
		Vector<Type> *ptr;
		int index;
	};

public:
	Vector();

	Vector(std::initializer_list<Type> lst);

	explicit Vector(const int _size);

	Vector(const Vector<Type> &other);

	/* Pushes a new item in the array. */
	void push_back(const Type &new_data);
	void pop_back();

	Iterator begin();
	Iterator end();

	const Iterator cbegin() const;
	const Iterator cend() const;

	/* Returns the vector's size. */
	size_t size() const;
	/* Returns the vector's capacity. */
	size_t capacity() const;
	/* Returns true if the vector is empty. */
	bool empty() const;

	/*Returns a reference to the vector's last element. */
	Type &back() const;

	/*Returns a reference to the vector's first element. */
	Type &front() const;

	/*Returns true if the vector contains the passed element. */
	bool contains(const Type &elem) const;

	Type &at(const Type &elem) const;

	/*Clears all elements. If any memory is allocated by the user, it's also the user's responsibility to free it manually.*/
	void clear();

	void reserve(const size_t new_capacity);

	/* Removes the element at *index*. The method does not handle errors if the index is out of range. */
	void erase(const size_t index);

	/* Removes the passed element, if one is in the data array. Else throws an error. */
	void erase(const Type &elem);

	/*Returns a reference to the element at *index*. The method does not handle errors if the index is out of range.*/
	Type &operator[](const size_t index);

	const Type &operator[](const size_t index) const;

	Vector<Type> &operator=(const Vector<Type> &other);

	~Vector();

private:
	Type *data;
	size_t current;
	size_t m_capacity;
};

template <typename Type>
inline Vector<Type>::Vector()
{
	data = new Type[1];
	current = 0;
	m_capacity = 1;
}

template <typename Type>
inline Vector<Type>::Vector(const int _size)
{
	reserve(_size);
}

template <typename Type>
inline Vector<Type>::Vector(std::initializer_list<Type> lst)
	: data(new Type[lst.size()]), current(lst.size()), m_capacity(lst.size())
{
	std::copy(lst.begin(), lst.end(), data);
}

template <typename Type>
inline Vector<Type>::Vector(const Vector<Type> &other)
	: data(new Type[other.m_capacity]), current(other.current), m_capacity(other.m_capacity)
{
	for (size_t i = 0; i < current; ++i)
		data[i] = other.data[i];
}

template <typename Type>
inline void Vector<Type>::push_back(const Type &new_data)
{
	if (current == m_capacity)
	{
		Type *temp = new Type[2 * m_capacity];

		for (size_t i = 0; i < m_capacity; i++)
			temp[i] = data[i];

		delete[] data;
		m_capacity *= 2;
		data = temp;
	}
	data[current++] = new_data;
}

template <typename Type>
inline void Vector<Type>::pop_back() { current--; }

template <typename Type>
typename Vector<Type>::Iterator Vector<Type>::begin()
{
	return Vector<Type>::Iterator(this, 0);
}

template <typename Type>
const typename Vector<Type>::Iterator Vector<Type>::cbegin() const
{
	return Vector<Type>::Iterator(this, 0);
}

template <typename Type>
typename Vector<Type>::Iterator Vector<Type>::end()
{
	return Vector<Type>::Iterator(this, current);
}

template <typename Type>
const typename Vector<Type>::Iterator Vector<Type>::cend() const
{
	return Vector<Type>::Iterator(this, current);
}

template <typename Type>
inline void Vector<Type>::reserve(const size_t new_capacity)
{
	if (new_capacity <= m_capacity)
		return; // no need to reallocate if new_capacity is less than or equal to current capacity

	Type *new_data = new Type[new_capacity];
	for (size_t i = 0; i < current; ++i)
		new_data[i] = data[i];

	if (data != nullptr)
		delete[] data;

	data = new_data;
	m_capacity = new_capacity;
}

template <typename Type>
inline void Vector<Type>::erase(const size_t index)
{
	if (index >= 0 && index < current)
	{
		for (size_t i = index; i < current - 1; ++i)
			data[i] = data[i + 1];
		current--;
	}
}

template <typename Type>
inline void Vector<Type>::erase(const Type &elem)
{
	int index = -1;
	for (size_t i = 0; i < current; ++i)
	{
		if (data[i] == elem)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
		erase(index);
	else
		throw std::invalid_argument("ERASE: No such element in this vector.");
}

template <typename Type>
inline bool Vector<Type>::contains(const Type &elem) const
{
	for (size_t i = 0; i < current; ++i)
		if (data[i] == elem)
			return true;
	return false;
}

template <typename Type>
inline size_t Vector<Type>::size() const
{
	return current;
}

template <typename Type>
inline size_t Vector<Type>::capacity() const
{
	return m_capacity;
}

template <typename Type>
inline bool Vector<Type>::empty() const
{
	return (current == 0 ? true : false);
}

template <typename Type>
inline Type &Vector<Type>::back() const
{
	return data[current - 1];
}

template <typename Type>
inline Type &Vector<Type>::front() const
{
	return data[0];
}

template <typename Type>
inline Type &Vector<Type>::at(const Type &elem) const
{
	for (size_t i = 0; i < current; ++i)
		if (data[i] == elem)
			return data[i];
	throw std::invalid_argument("AT: No such element in the vector.");
}

template <typename Type>
inline void Vector<Type>::clear()
{
	if (data)
	{
		delete[] data;
		data = nullptr;
	}
	current = 0;
}

template <typename Type>
inline Type &Vector<Type>::operator[](const size_t index)
{
	return data[index];
}

template <typename Type>
const Type &Vector<Type>::operator[](const size_t index) const
{
	return data[index];
}

template <typename Type>
inline void swap(Type *&a, Type *&b)
{
	Type *temp = a;
	a = b;
	b = temp;
}

template <typename Type>
inline Vector<Type> &Vector<Type>::operator=(const Vector<Type> &other)
{
	Vector<Type> temp(other);
	swap(data, temp.data);

	size_t temp_current = current;
	current = temp.current;
	temp.current = temp_current;

	size_t temp_capacity = m_capacity;
	m_capacity = temp.m_capacity;
	temp.m_capacity = temp_capacity;

	return *this;
}

template <typename Type>
inline Vector<Type>::~Vector()
{
	delete[] data;
}

#endif //! VECTOR_H