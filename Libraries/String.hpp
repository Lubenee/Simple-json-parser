#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>
#include "Vector.hpp"

class String
{
public:
	/* Default constructor, creates an empty string. */
	String();
	/* Creates a string object from a null-terminated C-style string. */
	String(const char *new_string);
	/* Copy constructor, creates a string object by copying another string object.*/
	String(const String &other);

	String(String &&other) noexcept;
	~String();

	/* Returns the string as a C-style string. */
	const char *c_str() const;

	/*Returns the number of characters in the string.*/
	const size_t size() const;

	/*Returns the number of characters in the string.*/
	size_t length() const;

	/*Returns true if the string contains the passed string. */
	const bool includes(const String &search_value) const;

	/*Returns true if the string contains the passed character. */
	const bool includes(const char search_character) const;

	/* If the current string includes the search value, it is replaced with the replace value.  */
	void replace(const String &search_value, const String &replace_value);

	/* Returns the character at a specific index in the string.*/
	const char at(const size_t &index) const;

	/* Returns a new string in which each letter is made uppercase. Does not modify the original string.*/
	String to_upper_case();

	/* Returns a new string in which each letter is made lowercase. Does not modify the original string.*/
	String to_lower_case();

	/* Erases the letter at the passed index, if the index is valid. */
	void erase(const int index);

	void split(const char split_character, Vector<String> &returned) const;

	/* Returns the index of the last time the passed character is seen in the string. */
	size_t last_index_of(const char &value) const;

	/* Returns the index of the first time the passed character is seen in the string. */
	size_t first_index_of(const char &value) const;

	/* Returns a newly constructed string object with its value initialized to a copy of a substring of this object. */
	String substr(const size_t pos, const size_t len) const;

	/* Returns true if the strings are the same. */
	bool operator==(const String &other) const;

	/* Returns false if the strings are the same.*/
	bool operator!=(const String &other) const;

	String &operator+=(const String &rhs);

	/* Assigns a new value to the string. */
	String &operator=(const String &other);

	/* Returns a reference to the character at a specific index in the string.*/
	char &operator[](const size_t index) const;

	friend std::ostream &operator<<(std::ostream &os, const String &string);
	friend std::istream &operator>>(std::istream &input, String &str);

	static const size_t npos = static_cast<size_t>(-1);

private:
	char *str;
	size_t m_size;

private:
	bool compare_str(const String &str1, const String &str2) const;
};

#endif //! STRING_H