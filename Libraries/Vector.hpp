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
	/**
	 * @brief Construct a new Vector object
	 */
	Vector();
	/**
	 * @brief Construct a new Vector object with an initializer list.
	 * @param lst
	 */
	Vector(std::initializer_list<Type> lst);

	/**
	 * @brief Construct a new Vector object and reserve a given ammount of space.
	 * @param _size
	 */
	explicit Vector(const int _size);

	/**
	 * @brief Construct a new Vector object
	 * 	Copy constructor. It requires that the objects have a defined operator=.
	 * @param other
	 */
	Vector(const Vector<Type> &other);

	/**
	 * @brief Pushes a new item to the back of the array.
	 * @param new_data
	 */
	void push_back(const Type &new_data);

	/**
	 * @brief Removes the last element from the array.
	 * 	It's the user's responsibility to free any memory, if the object
	 * 	requires it.
	 */
	void pop_back();

	/**
	 * @brief Returns an iterator to the start of the vector.
	 * @return Iterator
	 */
	Iterator begin();
	/**
	 * @brief Returns an iterator to the end of the vector.
	 * @return Iterator
	 */
	Iterator end();

	/**
	 * @brief Returns a const iterator to the start of the vector.
	 * @return Iterator
	 */
	const Iterator cbegin() const;
	/**
	 * @brief Returns a const iterator to the end of the vector.
	 * @return Iterator
	 */
	const Iterator cend() const;

	/**
	 * @brief Returns the vector's size.
	 * @return size_t
	 */
	size_t size() const;

	/**
	 * @brief Returns the vector's capacity.
	 * @return size_t
	 */
	size_t capacity() const;
	/**
	 * @brief Returns true if the vector is empty.
	 */
	bool empty() const;

	/**
	 * @brief Returns a reference to the vector's last element.
	 * @return Type&
	 */
	Type &back() const;

	/**
	 * @brief Returns a reference to the vector's first element.
	 * @return Type&
	 */
	Type &front() const;

	/**
	 * @brief Returns true if the vector contains the passed element.
	 *
	 * @param elem
	 */
	bool contains(const Type &elem) const;

	/**
	 * @brief Returns a reference to the passed element, if one is in the vector.
	 * 	This method requires that the objects have a valid operator==.
	 * 	If such an element isn't found, the method throws invalid_argument.
	 *
	 * @param elem
	 * @return Type&
	 */
	Type &at(const Type &elem) const;

	/**
	 * @brief Clears all elements. If any memory is allocated by the user,
	 * it's also the user's responsibility to free it manually.
	 */
	void clear();

	/** @brief
	 * Reserves memory to accommodate a specified capacity for the Vector.
	 *
	 * This method ensures that the Vector has enough memory allocated to hold
	 * at least the specified number of elements. If the requested capacity is
	 * less than or equal to the current capacity, this method has no effect.
	 * Otherwise, it allocates additional memory to accommodate the requested
	 * capacity, potentially increasing the Vector's capacity.
	 *
	 * @param new_capacity The desired capacity for the Vector.
	 *
	 * NOTE: This method does not modify the Vector's size or change the actual
	 *       number of elements stored in it. To add elements to the Vector,
	 *       use the `push_back` method after reserving
	 *       sufficient capacity.
	 */
	void reserve(const size_t new_capacity);

	/**
	 * @brief Removes the element at *index*. The method does not handle errors if the index is out of range.
	 * @param index
	 */
	void erase(const size_t index);

	/**
	 * @brief Removes the passed element, if one is in the data array.
	 * Else throws invalid_argument.
	 * @param elem
	 */
	void erase(const Type &elem);

	/**
	 * @brief Returns a reference to the element at *index*.
	 * The method does not handle errors if the index is out of range
	 *
	 * @param index
	 * @return Type&
	 */
	Type &operator[](const size_t index);

	/**
	 * @brief Returns a const reference to the element at *index*.
	 * The method does not handle errors if the index is out of range
	 *
	 * @param index
	 * @return Type&
	 */
	const Type &operator[](const size_t index) const;

	/** @brief
	 * Assigns the contents of another Vector to this Vector.
	 *
	 * This operator assigns the elements of the specified Vector to the current
	 * Vector, replacing its current contents. The size and capacity of this Vector
	 * may change to match the size of the assigned Vector. The assignment operator
	 * performs a deep copy of the elements, so each element is individually copied
	 * to the destination Vector. This requires that the elements in have a defined operator=.
	 *
	 * @param other The Vector whose elements are to be assigned.
	 * @return A reference to the modified Vector after the assignment.
	 *
	 * NOTE: The assignment operator ensures that the current Vector is self-assignment
	 *       safe. That is, assigning a Vector to itself has no effect and does not
	 *       result in undefined behavior.
	 */
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
		delete[] data;
	data = new Type[1];
	m_capacity = 1;
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
	if (this == &other)
		return *this;
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