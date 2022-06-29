
/*! \mainpage Documentation
 *
 * \section intro_sec Introduction
 *
 * This program represents a simple Json parser, including some basic commands for the user to work with, located in the Json operations class.
 */

#pragma once 
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
#include <stdexcept>
    /**
	* @brief
	* That Enum describes what element types might be used for a Json element.
	*/
enum class ElementType {
	Unknown,
	Null,
	Boolean,
	String,
	Float,
	Integer,
	List,
	Object
};
class Json {
public:
	/**
	* @brief
	* The default constructor initalizes the element with an Unknown type.
	*/
	Json();
	/**
	* @brief
	* Initializes the element with Boolean Element type and sets the value with the given parameter.
	*/
	Json(bool value);
	/**
	* @brief
	* Initializes a new element with the given key and value.
	* The value is then parsed as any of the given  Element types.
	* Used to parse an object with C++ string.
	*/
	Json(std::string& key, std::string& value);
	/**
	* @brief
	* Initializes a new element with the given key and value.
	* The value is then parsed as any of the given Element types.
	* Used to parse an object with C strings.
	* \param[in]    key    The Json object's key. It gets parsed and set as the element's key.
	* \param[in]    value  The Json object's value. It gets parsed and set as the elements's value.
	*/
	Json(const char* key, const char* value);
	/**
	* @brief
	* Initializes a new element with the given value.
	* The value is then parsed as any of the given Element types.
	* Used to parse an object with C++ strings.
	*/
	Json(std::string& value);
	/**
	* @brief
	* Initializes a new element with the given value.
	* The value is then parsed as any of the given Element types.
	* Used to parse an object with C strings.
	*/
	Json(const char* value);
	/**
	* @brief
	* Initializes the element with Float Element type and sets the value with the given parameter.
	*/
	Json(const double value);
	/**
	* @brief
	* Initializes the element with Integer Element type and sets the value with the given parameter.
	*/
	Json(const int value);
	/**
	* @brief
	* Standard copy constructor.
	*/
	Json(const Json& other);
	/**
	* @brief
	* Makes the Json class MoveAssignable.
	*/
	Json operator=(const Json& other);
	/**
	* @brief
	* Compares two Json objects.
	*/
	bool operator==(const Json& other) const;
	/**
	* @brief
	* Merges two Json elements together.
	* Only valid if *this* is either a List or an Object.
	* Else it simply returns *this without modifying it.
	*/
	Json& operator+=(const Json& other);

	//returns the element at the given index, if the value is a list or object
	/**
	* @brief
	* Only works if *this* is either a List or an Object.
	* Takes a size_t index and returns a reference to the Json element in the List/Object from the list_value vector or the obj_value vector.
	* If the index is invalid, it throws and exception.
	* \param[in]    index        A number index representing an Json Element in a List or Object.
	* \retval       Json& elem   If the index is valid.
	* \retval       *this        If the index is invalid.
	* \retval       *this        If *this is not a List or Object.
	*/
	Json& operator[](size_t index);
public:
	/**
	* @brief
	* Returns the element's type.
	* \retval ElementType type.
	*/
	ElementType type() const;
	/**
	* @brief
	* Returns the element's key, if one exists.
	* \retval std::string key.
	* \retval "", if a key doesn't exist.
	*/
	std::string key() const;

	/**
	* @brief
	* Returns the element's array list, if the element has Element type List.
	* \retval std::vector<Json>& list_value;
	*/
	std::vector<Json>& get_list() const;

	/**
	* @brief
	* Returns the element's array list, if the element has Element type List.
	* \retval std::vector<Json>& obj_value;
	*/
	std::vector<Json>& get_object() const;

	/**
	* @brief
	* Returns the element's array list size or object list size if the element has Element type List or Object.
	* \retval size, if Element type is List or Object and has more than one element.
	*/
	size_t size() const;

	/**
	* @brief
	* Returns a parsed string with the element's value, fully formatted.
	* \retval std::string value;
	*/
	std::string print() const;

	/**
	* @brief
	* Returns whether the value is an obj with the key specified.
	* \retval TRUE   An element with such key exists.
	* \retval FALSE  An element with such key does not exist.
	* \retval FALSE  *this does not have a type Object.
	*/
	bool has(const std::string& key) const;

	/**
	* @brief
	* Adds the value to *this's obj_value or list_value.
	* \param[in] std::string& value    The value is parsed into a new Json object.
	*/
	void add(std::string& value);
	/**
	* @brief
	* Adds the value to *this's obj_value or list_value.
	* \param[in] const char* value    The value is parsed into a new Json object.
	*/
	void add(const char* value);
	/**
	* @brief
	* Adds the key and value to *this's obj_value or list_value.
	* \param[in] std::string& key      The key is parsed into a new Json object.
	* \param[in] std::string& value    The value is parsed into the same Json object.
	*/
	void add(std::string& key, std::string& value);
	/**
	* @brief
	* Adds the key and value to *this's obj_value or list_value.
	* \param[in] const char* key      The key is parsed into a new Json object.
	* \param[in] const char* value    The value is parsed into the same Json object.
	*/
	void add(const char* key, const char* value);

	//setters
	/**
	* @brief
	* Sets the Element's type.
	* param[in] const ElementType new_type   The element's current type is set to new_type.
	*/
	void set_type(const ElementType new_type);
	/**
	* @brief
	* Sets the Boolean value.
	* \param[in] const bool new_val   The element's current boolean_value is set to new_val.
	*/
	void set_bool_value(const bool new_val);
	/**
	* @brief
	* Sets the String value.
	* \param[in] const std::string& new_val   The element's current string_value is set to new_val.
	*/
	void set_string_value(const std::string& new_val);
	/**
	* @brief
	* Sets the Integer value.
	* \param[in] const int new_val   The element's current int_value is set to new_val.
	*/
	void set_int_value(const int new_val);
	/**
	* @brief
	* Sets the Float value.
	* \param[in] const double new_val   The element's current float_value is set to new_val.
	*/
	void set_float_value(const double new_val);
	/**
	* @brief
	* Sets the list value.
	* \param[in] const std::vector<Json> new_val   The element's current list_value is set to new_val.
	*/
	void set_list_value(const std::vector<Json> new_val);
	/**
	* @brief
	* Sets the object value.
	* \param[in] const std::vector<Json> new_val   The element's current obj_value is set to new_val.
	*/
	void set_object_value(const std::vector<Json> new_val);

	//getters
	/**
	* @brief
	* Gets the object's boolean value.
	* \retval TRUE     The object's boolean value is true.
	* \retval FALSE    The object's boolean value is false.
	*/
	bool get_bool_value() const;
	/**
	* @brief
	* Gets the object's string value.
	*/
	std::string get_string_value() const;
	/**
	* @brief
	* Gets the object's int value.
	*/
	int get_int_value() const;
	/**
	* @brief
	* Gets the object's float value.
	*/
	double get_float_value() const;

	~Json();
protected:
	/**
	* @brief
	* Returns the list's parsed values as a string.
	*/
	std::string get_list_value() const;
	/**
	* @brief
	* Returns the object's parsed values as a string.
	*/
	std::string get_obj_value() const;
	/**
	* @brief
	* Returns the object's parsed values as a string, while it's inside a list.
	*/
	std::string get_obj_inside_list_val(const Json& obj) const;

	//checks if the passed string is int/float/bool/string
	/**
	* @brief
	* Checks if the passed string reference is an integer.
	* \retval TRUE   The passed string reference can be parsed as an integer.
	* \retval FALSE  The passed string reference can not be parsed as an integer.
	*/
	bool is_int(const std::string& val) const;
	/**
	* @brief
	* Checks if the passed string reference is a floating point.
	* \retval TRUE   The passed string reference can be parsed as a double.
	* \retval FALSE  The passed string reference can not be parsed as a double.
	*/
	bool is_float(const std::string& val) const;
	/**
	* @brief
	* Checks if the passed string reference is a boolean.
	* \retval TRUE   The passed string reference can be parsed as a boolean.
	* \retval FALSE  The passed string reference can not be parsed as a boolean.
	*/
	bool is_boolean(const std::string& val) const;
	/**
	* @brief
	* Checks if the passed string reference is enclosed with quotes '"', and is therefore a valid key or string value.
	* \retval TRUE   The passed string reference is enclosed with quotes.
	* \retval FALSE  The passed string reference is not enclosed with quotes.
	*/
	bool is_str(const std::string& val) const;

protected:
	ElementType m_type;
	std::string m_key;
	union {
		bool boolean_value;
		std::string* string_value;
		int int_value;
		double float_value;

		std::vector<Json>* list_value;
		std::vector<Json>* obj_value;
	};

private:
	/**
	* @brief
	* Parses the passed string reference value.
	*/
	Json m_get_obj(std::string& value);

	//splits the list/obj into Json objects
	/**
	* @brief
	* Splits the passed string reference into different Json objects.
	* The new Json objects are pushed into the List vector.
	*/
	void parse_list(const std::string& val);
	/**
	* @brief
	* Splits the passed string reference into different Json objects.
	* The new Json objects are pushed into the Object vector.
	*/
	void parse_obj(const std::string& val);

	/**
	* @brief
	* parses the next Json value in the specified string, and modifies the 
	* index to tell us where this particular value ends, or whether the value 
	* was invalid or not.
	* \param[in]     string& val      Splits the passed value into a new Json element, until a comma delimiter is found.If the value contains a new list or object, it gets parsed later. If the list/object's brackets are missing, the index is set to npos.
	* \param[in]     size_t index     The current index where we're located in the val string reference. When a new Json element is created, the index is set to that character's location.
	*/
	std::string parse_value(const std::string& val, size_t& index);
	/**
	* @brief
	* Checks if the passed string reference is a valid Json key, meaning that it checks if it's enclosed with quotes.
	*/
	std::string parse_obj_key(const std::string& key, size_t& index);

	//removes brackets/quotes from array/object/string values
	/**
	* @brief
	* Removes the square brackets from the passed string value.
	*/
	std::string remove_sqr_braces(std::string val);
	/**
	* @brief
	* Removes the square brackets from the passed object value.
	*/
	std::string remove_curly_braces(std::string val);
	/**
	* @brief
	* Removes the square brackets from the passed key/string value.
	*/
	std::string remove_quotes(std::string& val);

	//string to float, string to int, string to bool
	/**
	* @brief
	* String to float. Makes a float from a string value.
	* \param[in]   val
	* \retval float val
	*/
	float stof(const std::string& val);
	/**
	* @brief
	* String to int. Makes an int from a string value.
	* \param[in]   val
	* \retval int val
	*/
	int stoi(const std::string& val);
	/**
	* @brief
	* String to bool. Makes a bool from a string value.
	* \param[in]   val
	* \retval bool val
	*/
	bool stob(const std::string& val);

private:
	static size_t spaces;
};
