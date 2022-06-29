#include "JsonOperations.hpp"

void JsonOperations::search(const Json& target, const std::string& key) {
	if (target.key() == key) {
		search_vector.push_back(target);
	}
	if (target.type() == ElementType::Object) {
		for (size_t i = 0; i < target.get_object().size(); ++i) {
			search(target.get_object()[i], key);
		}
	}
	else if (target.type() == ElementType::List) {
		for (size_t i = 0; i < target.get_list().size(); ++i) {
			search(target.get_list()[i], key);
		}
	}
}
void JsonOperations::log_search() const {
	if (search_vector.size() != 0) {
		for (size_t i = 0; i < search_vector.size(); ++i) {
			std::cout
				<< search_vector[i].key()
				<< ": "
				<< search_vector[i].print()
				<< std::endl;
		}
	}
	else {
		std::cout << "Search vector is empty.\n";
	}
}

const Json& JsonOperations::get_search_elem(const size_t index) {
	if (index >= search_vector.size()) {
		throw("Invalid position\n");
	}
	return search_vector[index];
}

void JsonOperations::edit(Json& element, std::string& new_value) {
	Json new_elem(new_value);
	switch (new_elem.type()) {
	case ElementType::Boolean:
		element.set_bool_value(new_elem.get_bool_value());
		element.set_type(ElementType::Boolean);
		break;
	case ElementType::Float:
		element.set_float_value(new_elem.get_float_value());
		element.set_type(ElementType::Float);
		break;
	case ElementType::Integer:
		element.set_int_value(new_elem.get_int_value());
		element.set_type(ElementType::Integer);
		break;
	case ElementType::List:
		element.set_list_value(new_elem.get_list());
		element.set_type(ElementType::List);
		break;
	case ElementType::Object:
		element.set_object_value(new_elem.get_object());
		element.set_type(ElementType::Object);
		break;
	case ElementType::String:
		element.set_string_value(new_elem.get_string_value());
		element.set_type(ElementType::String);
		break;
	}
}
void JsonOperations::edit(Json& element, const char* new_value) {
	Json new_elem(new_value);
	switch (new_elem.type()) {
	case ElementType::Boolean:
		element.set_bool_value(new_elem.get_bool_value());
		element.set_type(ElementType::Boolean);
		break;
	case ElementType::Float:
		element.set_float_value(new_elem.get_float_value());
		element.set_type(ElementType::Float);
		break;
	case ElementType::Integer:
		element.set_int_value(new_elem.get_int_value());
		element.set_type(ElementType::Integer);
		break;
	case ElementType::List:
		element.set_list_value(new_elem.get_list());
		element.set_type(ElementType::List);
		break;
	case ElementType::Object:
		element.set_object_value(new_elem.get_object());
		element.set_type(ElementType::Object);
		break;
	case ElementType::String:
		element.set_string_value(new_elem.get_string_value());
		element.set_type(ElementType::String);
		break;
	}
}

void JsonOperations::create(Json& element, std::string& value) {
	element.add(value);
}
void JsonOperations::create(Json& element, const char* value) {
	element.add(value);
}
void JsonOperations::create(Json& element, std::string& key, std::string& value) {
	element.add(key, value);
}
void JsonOperations::create(Json& element, const char* key, const char* value) {
	element.add(key, value);
}

void JsonOperations::remove(Json& element) {
	element.set_type(ElementType::Unknown);
}

void JsonOperations::move(Json& from, Json& to) {
	to += from;
	from.set_type(ElementType::Unknown);
}

void JsonOperations::write_element_to_file(const Json& elem) const {
	if (search_vector.size() == 0) {
		std::cout << "Element not found.\n";
		return;
	}
	bool match = false;
	for (size_t i = 0; i < search_vector.size(); ++i) {
		if (elem == search_vector[i]) {
			match = 1;
			break;
		}
	}
	if (!match) {
		std::cout << "Element not found.\n";
		return;
	}

	std::ofstream file;
	file.open("Json_saved_element_file.json", std::ios::out);
	if (!file.is_open()) {
		std::cout << "Unable to write to file.\n";
		file.close();
		return;
	}
	file << "{ " << elem.key() << ": " << elem.print() << " }\n";
	file.close();
}

void JsonOperations::write_to_file() const {
	std::ofstream file;
	file.open("Json_saved_file.json", std::ios::out);
	if (!file.is_open()) {
		std::cout << "Unable to write to file.\n";
		file.close();
		return;
	}
	if (search_vector.size() != 0) {
		file << "{\n";
		for (size_t i = 0; i < search_vector.size(); ++i) {
			file
				<< search_vector[i].key()
				<< ": "
				<< search_vector[i].print()
				<< std::endl;
		}
		file << "}";
	}
	else {
		std::cout << "Search vector is empty.\n";
	}
	file.close();

}
