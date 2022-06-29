#pragma once
#include "Json.hpp"
class JsonOperations : public Json {
public:
	/**
	* @brief
	* Utilizes a default constructor.
	*/
	JsonOperations() = default;
	
	/**
	* @brief
	* Searches the target Json element for the passed key.
	* If the target's type is either a list or object, the list's and object's values are also searched for the given key.
	* \param[in] Json& target         Searches through this Json element's keys
	* \param[in] std::string& key     
	*/
	void search(const Json& target, const std::string& key);
	/**
	* @brief
	* Logs any elements that are found in the search function, if any.
	*/
	void log_search() const;
	/**
	* @brief
	* Returns an element *index* from the search vector, if one exists.
	* \param[in] index        if the search vector doesn't have an element on that index, an exception is thrown.
	* \retval Json& elem
	*/
	const Json& get_search_elem(const size_t index);

	/**
	* @brief
	* Changes the passed element's value with new_value.
	* If the new value's type does not match the passed element's type, the first element's type is changed to the type of the new value.
	* \param[in]   Json& element         The element whose value is being edited.
	* \param[in]   std::string& new_val  The new value gets parsed to a Json object and is then set to the target's 
	*/
	void edit(Json& element, std::string& new_value);
	/**
	* @brief
	* Changes the passed element's value with new_value.
	* If the new value's type does not match the passed element's type, the first element's type is changed to the type of the new value.
	* \param[in]   Json& element         The element whose value is being edited.
	* \param[in]   const char* new_val   The new value gets parsed to a Json object and is then set to the target's
	*/
	void edit(Json& element, const char* new_value);

	/**
	* @brief
	* Creates a new Json element from the passed string reference, and adds it to the target element's objectives vector or list vector.
	* \param[in] Json& target           The new element is added to the target's object or list's vector.
	* \param[in] std::string& value     The value gets parsed to a new Json element.
	*/
	void create(Json& target, std::string& value);
	/**
	* @brief
	* Creates a new Json element from the passed string reference, and adds it to the target element's objectives vector or list vector.
	* \param[in] Json& target           The new element is added to the target's object or list's vector.
	* \param[in] const char* value      The value gets parsed to a new Json element.
	*/
	void create(Json& target, const char* value);
	/**
	* @brief
	* Creates a new Json element from the passed string reference, and adds it to the target element's objectives vector or list vector.
	* \param[in] Json& target           The new element is added to the target's object or list's vector.
	* \param[in] std::string& key       The key gets parsed to a new Json element.
	* \param[in] std::string& value	   The value gets parsed to the same Json element.
	*/
	void create(Json& target, std::string& key, std::string& value);
	/**
	* @brief
	* Creates a new Json element from the passed string reference, and adds it to the target element's objectives vector or list vector.
	* \param[in] Json& target           The new element is added to the target's object or list's vector.
	* \param[in] const char* key        The key gets parsed to a new Json element.
	* \param[in] const char* value      The value gets parsed to the same Json element.
	*/
	void create(Json& target, const char* key, const char* value);

	/**
	* @brief
	* Sets the targeted element's type to Unknown. Later,  when printed, elements with Unknown type get deleted.
	* \param[in] Json& target
	*/
	void remove(Json& target);

	/**
	* @brief
	* The first element's value (and key, if one exists) get added to the second element's list or object vector.
	* The first element's type is then set to Unknown.
	* \param[in] Json& from
	* \param[in] Json& to
	*/
	void move(Json& from, Json& to);

	/**
	* @brief
	* The passed element is written to a new json file "Json_saved_element_file.json", presumably making it a valid .json file.
	* The target file must be availible in the search vector for that to happen, else a message is displayed.
	* param[in] Json& target
	*/
	void write_element_to_file(const Json& target) const;
	/**
	* @brief
	* The whole search vector is written to a new json file "Json_saved_file.json", presumably making it a valid .json file.
	*/
	void write_to_file() const;

	/**
	* @brief
	* The Json Operations class utilizes a default destructor.
	*/
	~JsonOperations() = default;
private:
	std::vector<Json> search_vector;
};