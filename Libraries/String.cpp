#define _CRT_SECURE_NO_WARNINGS
#include "String.hpp"

String::String(const char *new_string) : str(nullptr), m_size(0)
{
	this->str = new char[strlen(new_string) + 1];
	this->m_size = strlen(new_string);
	strcpy(this->str, new_string);
}

String::String(const String &other)
	: str(nullptr), m_size(0)
{
	if (other.str == nullptr)
		throw "Invalid string operation.";

	this->str = new char[strlen(other.str) + 1];
	strcpy(this->str, other.str);
	this->m_size = other.m_size;
}

String::String(String &&other) noexcept
{
	this->str = other.str;
	this->m_size = other.m_size;

	// reset other object. It's still valid but calling it's destructor won't mess with the current *this* object.
	other.str = nullptr;
	other.m_size = 0;
}

String::String() : str(nullptr), m_size(0) {}

const char *String::c_str() const
{
	return this->str;
}

const size_t String::size() const
{
	return this->m_size;
}

size_t String::length() const
{
	return this->m_size;
}

const bool String::includes(const String &search_value) const
{
	if (this->str == nullptr)
		return false;

	if (search_value.m_size > this->m_size)
		return false;

	bool match = true;
	for (size_t i = 0; i < m_size; ++i)
	{
		if (str[i] == search_value[0])
		{
			for (size_t j = 0; j < search_value.m_size; ++j)
			{
				if (str[i + j] != search_value.str[j])
				{
					match = false;
					break;
				}
			}
			if (match)
				return true;
		}
	}
	return false;
}

const bool String::includes(const char search_character) const
{
	for (size_t i = 0; i < this->m_size; ++i)
		if (this->str[i] == search_character)
			return true;

	return false;
}

void String::replace(const String &search_value, const String &replace_value)
{
	if (!(this->includes(search_value)))
		return;

	bool value_found = false;

	char first_char = search_value.str[0];
	char first_string[128] = {
		'\0',
	};
	size_t first_index = 0, second_index = 0;
	char second_string[128] = {
		'\0',
	};
	for (size_t i = 0; i < m_size; ++i)
	{
		if (str[i] == first_char)
		{
			for (size_t j = 0; j < search_value.m_size; ++j)
			{
				if (str[i++] != search_value.str[j])
				{
					i -= 2;
					break;
				}
				if (j == search_value.m_size - 1)
					value_found = true;
			}
		}
		if (!value_found)
			first_string[first_index++] = str[i];
		else
			second_string[second_index++] = str[i];
	}

	strcat(first_string, replace_value.str);
	strcat(first_string, second_string);
	delete[] str;
	m_size = strlen(first_string);
	str = new char[m_size + 1];
	strcpy(str, first_string);
}

const char String::at(const size_t &index) const
{
	if (index >= this->m_size)
		throw "Invalid string index.";
	return this->str[index];
}

String String::to_upper_case()
{
	String temp = *this;
	for (size_t i = 0; i < temp.m_size; ++i)
	{
		if (temp[i] >= 'a' && temp[i] <= 'z')
			temp[i] -= 32;
	}
	return temp;
}
String String::to_lower_case()
{
	String temp = *this;
	for (size_t i = 0; i < temp.m_size; ++i)
	{
		if (temp[i] >= 'A' && temp[i] <= 'Z')
			temp[i] += 32;
	}
	return temp;
}

void String::erase(const int index)
{
	if (index >= (int)this->m_size)
		return;

	char temp[256] = {
		'\0',
	};
	size_t j = 0;

	for (size_t i = 0; i < m_size; i++)
		if (i != (size_t)index)
			temp[j++] = str[i];

	String temp_str(temp);
	*this = temp_str;
}

size_t String::first_index_of(const char &value) const
{
	for (size_t i = 0; i < m_size; ++i)
		if (str[i] == value)
			return i;
	return 0;
}

size_t String::last_index_of(const char &value) const
{
	for (size_t i = m_size - 1; i >= 0; i--)
		if (str[i] == value)
			return i;
	return 0;
}

String String::substr(const size_t pos, const size_t len) const
{
	if (pos >= m_size || pos + len >= m_size)
		throw std::out_of_range("STRING::SUBSTR::Out of range.");
	char buff[1024] = {'\0'};
	size_t buff_pos = 0;
	for (size_t i = pos; i < len + pos; ++i)
		buff[buff_pos++] = this->str[i];
	return String(buff);
}

bool String::compare_str(const String &str1, const String &str2) const
{
	if (str1.size() != str2.size())
		return false;
	for (size_t i = 0; i < str1.size(); ++i)
	{
		if (str1.str[i] != str2.str[i])
			return false;
	}
	return true;
}
bool String::operator==(const String &other) const
{
	return strcmp(this->str, other.str) == 0;
}
bool String::operator!=(const String &other) const
{
	return !(*this == other);
}

String &String::operator=(const String &other)
{
	if (this == &other)
		return *this;

	if (other.str == nullptr)
		return *this;

	char *new_str = new char[other.m_size + 1];
	try
	{
		strcpy(new_str, other.str);
	}
	catch (...)
	{
		delete[] new_str;
		throw;
	}

	delete[] this->str;
	this->str = new_str;
	this->m_size = other.m_size;

	return *this;
}

char &String::operator[](const size_t index) const
{
	if (index >= this->m_size)
		throw "Invalid index";
	return this->str[index];
}

String &String::operator+=(const String &rhs)
{
	if (rhs == "" || rhs.str == nullptr)
		return *this;

	size_t new_len = m_size + rhs.m_size;
	char *new_str = new char[new_len + 1];

	if (str)
	{
		strcpy(new_str, str);
		delete[] str;
	}

	strcat(new_str, rhs.str);
	str = new_str;
	m_size = new_len;
	return *this;
}

std::ostream &operator<<(std::ostream &os, const String &string)
{
	os << string.str;
	return os;
}
std::istream &operator>>(std::istream &input, String &str)
{
	char read_buffer[2048];
	input.getline(read_buffer, 2048);
	str = read_buffer;
	return input;
}

String::~String()
{
	delete[] this->str;
}