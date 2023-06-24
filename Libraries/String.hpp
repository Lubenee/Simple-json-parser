#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>
#include "Vector.hpp"

class String
{
public:
	/**
	 * @brief Construct a new String object. The string is empty.
	 */
	String();

	/**
	 * @brief Construct a new String object
	 * Creates a string object from a null-terminated C-style string.
	 * @param new_string New string.
	 */
	String(const char *new_string);
	/**
	 * @brief Construct a new String object
	 * 	Copy constructor.
	 * @param other
	 */
	String(const String &other);

	/**
	 * @brief Construct a new String object
	 * 	Move constructor.
	 * @param other
	 */
	String(String &&other) noexcept;
	~String();

	/**
	 * @brief Returns the string as a C-style string.
	 * @return const char*
	 */
	const char *c_str() const;

	/**
	 * @brief Returns the number of characters in the string.
	 *
	 * @return const size_t
	 */
	const size_t size() const;

	/**
	 * @brief Returns the number of characters in the string.
	 * @return size_t
	 */
	size_t length() const;

	/**
	 * @brief Returns true if the string contains the passed string.
	 *
	 * @param search_value
	 */
	const bool includes(const String &search_value) const;

	/**
	 * @brief Returns true if the string contains the passed character.
	 *
	 * @param search_character
	 */
	const bool includes(const char search_character) const;

	/**
	 * @brief If the current string includes the search value, it is replaced with the replace value.
	 *
	 * @param search_value
	 * @param replace_value
	 */
	void replace(const String &search_value, const String &replace_value);

	/**
	 * @brief Returns a new string in which each letter is made uppercase. Does not modify the original string
	 * @return String
	 */
	String to_upper_case();

	/**
	 * @brief Returns a new string in which each letter is made lowercase. Does not modify the original string.
	 *
	 * @return String
	 */
	String to_lower_case();

	/**
	 * @brief Erases the letter at the passed index, if the index is valid. Else it does nothing.
	 * @param index
	 */
	void erase(const int index);

	/**
	 * @brief Splits the string into different tokens and pushes them into the "returned" Vector.
	 * 	EXAMPLE:
	 * 		"An Interesting sentence". If the split character is ' ', then the Vector will have
	 * 		the following elements:
	 * 			0.An
	 * 			1.Interesting
	 * 			3.sentence
	 *
	 * @param split_character
	 * @param returned
	 */
	void split(const char split_character, Vector<String> &returned) const;

	/**
	 * @brief Returns the index of the last time the passed character is seen in the string.
	 *
	 * @param value
	 * @return size_t
	 */
	size_t last_index_of(const char &value) const;

	/**
	 * @brief Returns the index of the first time the passed character is seen in the string.
	 *
	 * @param value
	 * @return size_t
	 */
	size_t first_index_of(const char &value) const;

	bool empty() const;

	/**
	 * @brief Returns a newly constructed string object with its value initialized to a copy of a substring of this object.
	 *
	 * @param pos
	 * @param len
	 * @return String
	 */
	String substr(const size_t pos, const size_t len) const;

	/**
	 * @brief Returns the character at a specific index in the string.
	 *
	 * @param index
	 * @return const char
	 */
	const char at(const size_t &index) const;

	/**
	 * @brief Returns a reference to the character at a specific index in the string.
	 *
	 * @param index
	 * @return char&
	 */
	char &operator[](const size_t index) const;

	/**
	 * @brief Returns true if the strings are the same.
	 * @param other
	 */
	bool operator==(const String &other) const;

	/**
	 * @brief Returns false if the strings are the same.
	 *
	 * @param other
	 * @return true
	 * @return false
	 */
	bool operator!=(const String &other) const;

	/**
	 * @brief Concatenates *this* string to the passed one.
	 * @param rhs
	 * @return String&
	 */
	String &operator+=(const String &rhs);

	/**
	 * @brief Assigns a new value to the string.
	 *
	 * @param other
	 * @return String&
	 */
	String &operator=(const String &other);

	friend std::ostream &operator<<(std::ostream &os, const String &string);
	friend std::istream &operator>>(std::istream &input, String &str);

	/**
	 * @brief  Represents a special value typically used to indicate
	 * 	the absence or failure of a specific position or substring
	 *	within a string.
	 */
	static const size_t npos = static_cast<size_t>(-1);

private:
	char *str;
	size_t m_size;

private:
	bool compare_str(const String &str1, const String &str2) const;
};

#endif //! STRING_H