#include "Json.hpp"
Json::Json() {
	m_type = ElementType::Unknown;
}

Json::Json(bool value) {
	m_type = ElementType::Boolean;
	boolean_value = value;
}

Json::Json(std::string& key, std::string& value) {
	if (value[0] == '[') {
		list_value = new std::vector<Json>[1];
		m_get_obj(value);
		m_type = ElementType::List;
	}
	else if (value[0] == '{') {
		obj_value = new std::vector<Json>[1];
		m_get_obj(value);
		m_type = ElementType::Object;
	}
	else if (is_int(value)) {
		m_type = ElementType::Integer;
		int_value = stoi(value);
	}
	else if (is_float(value)) {
		m_type = ElementType::Float;
		float_value = stof(value);
	}
	else if (is_boolean(value)) {\
		m_type = ElementType::Boolean;
		boolean_value = stob(value);
	}
	else {
		m_type = ElementType::String;
		string_value = new std::string(remove_quotes(value));
	}
	if (is_str(key)) {
		m_key = key;
		m_key = remove_quotes(m_key);
	}
}

Json::Json(const char* key, const char* value) {
	std::string key_s = key, val_s = value;
	if (val_s[0] == '[') {
		list_value = new std::vector<Json>[1];
		m_get_obj(val_s);
		m_type = ElementType::List;
	}
	else if (val_s[0] == '{') {
		obj_value = new std::vector<Json>[1];
		m_get_obj(val_s);
		m_type = ElementType::Object;
	}
	else if (is_int(val_s)) {
		m_type = ElementType::Integer;
		int_value = stoi(val_s);
	}
	else if (is_float(val_s)) {
		m_type = ElementType::Float;
		float_value = stof(val_s);
	}
	else if (is_boolean(val_s)) {
		m_type = ElementType::Boolean;
		boolean_value = stob(val_s);
	}
	else {
		m_type = ElementType::String;
		string_value = new std::string(remove_quotes(val_s));
	}
	if (is_str(key_s)) {
		m_key = key_s;
		m_key = remove_quotes(m_key);
	}
}

Json::Json(std::string& value) {
	if (value[0] == '[') {
		list_value = new std::vector<Json>[1];
		m_get_obj(value);
		m_type = ElementType::List;
	}
	else if (value[0] == '{') {
		obj_value = new std::vector<Json>[1];
		m_get_obj(value);
		m_type = ElementType::Object;
	}
	else if (is_int(value)) {
		m_type = ElementType::Integer;
		int_value = stoi(value);
	}
	else if (is_float(value)) {
		m_type = ElementType::Float;
		float_value = stof(value);
	}
	else if (is_boolean(value)) {
		m_type = ElementType::Boolean;
		boolean_value = stob(value);
	}
	else {
		m_type = ElementType::String;
		string_value = new std::string(remove_quotes(value));
	}
}
 
Json::Json(const char* value) {
	std::string val = value;
	if (value[0] == '[') {
		list_value = new std::vector<Json>[1];
		m_get_obj(val);
		m_type = ElementType::List;
	}
	else if (value[0] == '{') {
		obj_value = new std::vector<Json>[1];
		m_get_obj(val);
		m_type = ElementType::Object;
	}
	else if (is_int(value)) {
		m_type = ElementType::Integer;
		int_value = stoi(value);
	}
	else if (is_float(value)) {
		m_type = ElementType::Float;
		float_value = stof(value);
	}
	else if (is_boolean(value)) {
		m_type = ElementType::Boolean;
		boolean_value = stob(value);
	}
	else {
		m_type = ElementType::String;
		string_value = new std::string(remove_quotes(val));
	}
}

Json::Json(const double value) {
	m_type = ElementType::Float;
	float_value = value;
}

Json::Json(const int value) {
	m_type = ElementType::Integer;
	int_value = value;
}

std::string Json::key() const {
	if (m_key == "") {
		return "";
	}
	return m_key;
}

ElementType Json::type() const {
	return m_type;
}

std::vector<Json>& Json::get_list() const {
	return this->list_value[0];
}

std::vector<Json>& Json::get_object() const {
	return this->obj_value[0];
}

std::string Json::print() const {
	switch (m_type) {
	case ElementType::Unknown: return "";
	case ElementType::Null: return "null";
	case ElementType::Boolean: return (boolean_value ? "true" : "false");
	case ElementType::String: return (*string_value);
	case ElementType::Integer: return std::to_string(int_value);
	case ElementType::Float: return std::to_string(float_value);
	case ElementType::List: return get_list_value();
	case ElementType::Object: return get_obj_value();
	default: return "???";
	}
}

size_t Json::size() const {
	if (m_type == ElementType::List) {
		if (list_value->size() > 0) {
			return list_value->size();
		}
		else {
			return 0;
		}
	}
	else if (m_type == ElementType::Object) {
		if (obj_value->size() > 0) {
			return obj_value->size();
		}
		else {
			return 0;
		}
	}
	else {
		//Returns 0 if the object does not contain a list, or if the list is empty
		return 0;
	}
}

bool Json::has(const std::string& key) const {
	size_t size = obj_value[0].size();
	if (size == 0) {
		return false;
	}
	for (size_t i = 0; i < size; ++i) {
		if (key == obj_value[0][i].key()) {
			return true;
		}
	}
	return false;
}

Json& Json::operator[](size_t index) {
	if (m_type == ElementType::List && index < list_value->size()) {
		return list_value[0][index];
	}
	else if (m_type == ElementType::Object && index < obj_value->size()) {
		return obj_value[0][index];
	}
	throw std::out_of_range("No such index exists");
}
bool Json::operator==(const Json& other) const {
	if (m_type != other.m_type) {
		return false;
	}
	else {
		switch (m_type) {
		case ElementType::Unknown: return true;
		case ElementType::Null: return true;
		case ElementType::Boolean: return (boolean_value == other.boolean_value);
		case ElementType::String: return (*string_value == *other.string_value);
		case ElementType::Integer: return (int_value == other.int_value);
		case ElementType::Float: return (float_value == other.float_value);
		case ElementType::List: return (*list_value == *other.list_value);
		default: return true;
		}
	}
}
Json& Json::operator+=(const Json& other) {
	switch (this->type()) {
	case ElementType::List:
		list_value->push_back(other);
		break;
	case ElementType::Object:
		obj_value->push_back(other);
		break;
	}
	return *this;
}
Json Json::operator=(const Json& other) {
	this->m_type = other.m_type;
	this->m_key = other.m_key;
	switch (m_type) {
	case ElementType::Boolean:
		boolean_value = other.boolean_value; break;
	case ElementType::Float:
		float_value = other.float_value; break;
	case ElementType::Integer:
		int_value = other.int_value; break;
	case ElementType::String:
		string_value = new std::string(other.string_value[0]); break;
	case ElementType::List:
		list_value = new std::vector<Json>(other.list_value[0]); break;
	case ElementType::Object:
		obj_value = new std::vector<Json>(other.obj_value[0]); break;
	}
	return *this;
}
Json::Json(const Json& other) {
 	this->m_type = other.m_type;
	this->m_key = other.m_key;
	switch (m_type) {
	case ElementType::Boolean:
		boolean_value = other.boolean_value; break;
	case ElementType::Float:
		float_value = other.float_value; break;
	case ElementType::Integer:
		int_value = other.int_value; break;
	case ElementType::String:
		string_value = new std::string(other.string_value[0]); break;
	case ElementType::List:
		list_value = new std::vector<Json>(other.list_value[0]); break;
	case ElementType::Object:
		obj_value = new std::vector<Json>(other.obj_value[0]); break;
	}
}

Json Json::m_get_obj(std::string& value) {
	if (value.empty()) {
		//the default type is ElementType::Invalid.
		return Json();
	}
	else if (value == "null") {
		return nullptr;
	}
	else if (value == "true") {
		return true;
	}
	else if (value == "false") {
		return false;
	}
	else if (is_str(value) && !value.empty()) {
		value = remove_quotes(value);
		return value;
	}
	else if (is_int(value)) {
		return int_value;
	}
	else if (is_float(value)) {
		return float_value;
	}
	else if (value[0] == '{') {
		value = remove_curly_braces(value);
		parse_obj(value);
		return Json();
	}
	else if (value[0] == '[') {
		value = remove_sqr_braces(value);
		parse_list(value);
		return Json();
	}
	else {
		return Json();
	}
}

void Json::add(std::string& value) {
	Json new_elem;
	new_elem.parse_obj(value);
	*this += new_elem;
}
void Json::add(const char* value) {
	Json new_elem;
	new_elem.parse_obj(value);
	*this += new_elem;
}
void Json::add(std::string& key, std::string& value) {
	Json new_elem(key, value);
	*this += new_elem;
}
void Json::add(const char* key, const char* value) {
	Json new_elem(key, value);
	*this += new_elem;
}

void Json::parse_list(const std::string& val) {
	std::vector<Json> list_values;
	size_t state = 0;
	size_t index = 0;
	while (index < val.length()) {
		std::string new_val = parse_value(val, index);
		if (new_val == "") {
			//->invalid element
			continue;
		}
		Json new_el(new_val);
		list_values.push_back(new_el);
	}
	list_value = new std::vector<Json>(list_values);
}
void Json::parse_obj(const std::string& val) {
	std::vector<Json> obj_values;
	size_t state = 0;
	size_t index = 0;
	while (index < val.length()) {
		std::string new_key = parse_obj_key(val, index);
		std::string new_val = parse_value(val, index);
		if (new_val == "" || new_key == "") {
			//->invalid element
			continue;
		}
		Json new_el(new_key, new_val);
		obj_values.push_back(new_el);
	}
	obj_value = new std::vector<Json>(obj_values);
}

std::string Json::parse_value(const std::string& val, size_t& index) {
	std::vector<char> stack;
	char new_value[1024] = { '\0', }, delimiter;
	std::string new_value_str;
	size_t stack_index = 0, string_index = 0;
	bool in_string = false;

	for (size_t i = index; i < val.length(); ++i) {
		if (val[i] == '\r' || val[i] == '\n') {
			if (i == val.length() - 1) {
				index = i + 1;
				break;
			}
			continue;
		}
		else if (val[i] == '\"') {
			delimiter = '\"';
			if (stack_index > 0) {
				if (stack[stack_index - 1] == delimiter) {
					in_string = false;
					stack.pop_back();
					stack_index--;
				}
				else {
					in_string = true;
					stack.push_back(delimiter);
					stack_index++;
				}
			}
			else {
				in_string = true;
				stack.push_back(delimiter);
				stack_index++;
			}
		}
		else if (val[i] == '[') {
			delimiter = '[';
			stack.push_back(delimiter);
			stack_index++;
		}

		else if (val[i] == ']') {
			delimiter = ']';
			if (stack[stack_index - 1] == '[') {
				stack.pop_back();
				stack_index--;
			}
			else {
				stack.push_back(delimiter);
				stack_index++;
			}
		}

		else if (val[i] == '{') {
			delimiter = '{';
			stack.push_back(delimiter);
			stack_index++;
		}

		else if (val[i] == '}') {
			delimiter = '}';
			if (stack[stack_index - 1] == '{') {
				stack.pop_back();
				stack_index--;
			}
			else {
				stack.push_back(delimiter);
				stack_index++;
			}
		}

		else if (val[i] == ' ' && !in_string) {
			continue;
		}

		else if (val[i] == ',' && stack.empty()) {
			index = ++i;
			break;
		}

		else {

			if (i > 0) {
				if (val[i - 1] == '"' && in_string) {
					new_value[string_index++] = '"';
				}
			}
			new_value[string_index++] = val[i];

			if (i < val.length() - 1) {
				if (val[i + 1] == '"' && in_string) {
					new_value[string_index++] = '"';
				}
			}

		}
		if (val[i] == '{') {
			new_value[string_index++] = '{';
		}
		else if (val[i] == '}') {
			new_value[string_index++] = '}';
		}
		else if (val[i] == '[') {
			new_value[string_index++] = '[';
		}
		else if (val[i] == ']') {
			new_value[string_index++] = ']';
		}

		if (i == val.length() - 1) {
			index = i + 1;
		}
	}
	if (stack.empty()) {
		new_value_str = new_value;
		return new_value_str;
	}
	else {
		// -> incorrect format, missing braces, etc
		for (size_t i = 0; i < stack.size(); ++i) {
			std::cout
				<< "Incorrect format!\nMissing delimiter(s): "
				<< stack[i] << '\n';
		}
		index = std::string::npos;
		return "";
	}
}
std::string Json::parse_obj_key(const std::string& key, size_t& index) {
	char new_key[1024] = { '\0', };
	int char_index = 0;
	for (size_t i = index; i < key.length(); ++i) {
		if (key[i] == '"') {
			new_key[char_index++] = '"';
			while (key[++i] != '"' && i < key.length()) {
				new_key[char_index++] = key[i];
			}
			new_key[char_index++] = '"';
			index = i;
			break;
		}
	}
	while (key[++index] != ':') {
		continue;
	}
	index++;
	std::string new_key_str(new_key);
	return new_key_str;
}

size_t Json::spaces = 0;
std::string Json::get_list_value() const {
	std::string values = "[";
	spaces += 2;
	size_t size = list_value[0].size();

	bool in_obj = false;
	for (size_t i = 0; i < size; ++i) {
		if (list_value[0][i].type() == ElementType::Object) {
			values += '\n';
			in_obj = true;
			break;
		}
		else if (list_value[0][i].type() == ElementType::List) {
			values += '\n';
			in_obj = true;
			break;
		}
	}

	for (size_t i = 0; i < size; ++i) {
		if (list_value[0][i].type() == ElementType::Object) {
			for (size_t i = 0; i < spaces; ++i) {
				values += ' ';
			}
			values += get_obj_inside_list_val(list_value[0][i]);
		}
		else if (in_obj) {
			for (size_t i = 0; i < spaces; ++i) {
				values += ' ';
			}
			values += list_value[0][i].print();
		}
		else {
			values += list_value[0][i].print();
		}
		if (i != size - 1) {
			values += ", ";
		}
		if (in_obj) {
			values += '\n';
		}
	}
	spaces -= 2;
	if (in_obj) {
		for (size_t i = 0; i < spaces; ++i) {
			values += ' ';
		}
	}
	values += "]";
	return values;
}
std::string Json::get_obj_value() const {
	std::string values;
	size_t size = obj_value[0].size();
	values += "{\n";
	spaces += 2;
	for (int i = 0; i < (int)size; ++i) {
		if (obj_value[0][i].type() == ElementType::Unknown) {
			obj_value[0].erase(obj_value[0].begin() + i);
			size--; i--;
			continue;
		}
		for (size_t i = 0; i < spaces; ++i) {
			values += ' ';
		}
		values += obj_value[0][i].key();
		values += ": ";
		values += obj_value[0][i].print();
		if (i != size - 1) {
			values += ",\n";
		}
	}
	values += '\n';
	spaces -= 2;
	for (size_t i = 0; i < spaces; ++i) {
		values += ' ';
	}
	values += "}";
	return values;
}
std::string Json::get_obj_inside_list_val(const Json& obj) const {
	std::string values;
	if (obj.type() != ElementType::Object) {
		values += "{ ";
		if (obj.key() != "") {
			values += obj.key();
			values += ": ";
		}
		for (size_t i = 0; i < obj.obj_value[0].size(); ++i) {
			values += obj.obj_value[0][i].key();
			values += obj.obj_value[0][i].print();
		}
		values += " }";
	}
	else {
		values += obj.print();
	}
	return values;
}

void Json::set_type(const ElementType new_type) {
	m_type = new_type;
}
void Json::set_bool_value(const bool new_val) {
	this->boolean_value = new_val;
}
void Json::set_string_value(const std::string& new_val) {
	this->string_value = new std::string(new_val);
}
void Json::set_int_value(const int new_val) {
	this->int_value = new_val;
}
void Json::set_float_value(const double new_val) {
	this->float_value = new_val;
}
void Json::set_list_value(const std::vector<Json> new_val) {
	this->list_value = new std::vector<Json>(new_val);
}
void Json::set_object_value(const std::vector<Json> new_val) {
	this->obj_value = new std::vector<Json>(new_val);
}

bool Json::get_bool_value() const {
	return boolean_value;
}
std::string Json::get_string_value() const {
	return string_value[0];
}
int Json::get_int_value() const {
	return int_value;
}
double Json::get_float_value() const {
	return float_value;
}

std::string Json::remove_curly_braces(std::string val) {
	size_t first_brace = val.find_first_of('{') + 1;
	size_t last_brace = val.find_last_of('}');
	std::string temp = val.substr(first_brace, last_brace - first_brace);
	return temp;
}
std::string Json::remove_sqr_braces(std::string val) {
	size_t first_brace = val.find_first_of('[') + 1;
	size_t last_brace = val.find_last_of(']');
	std::string temp = val.substr(first_brace, last_brace - first_brace);
	return temp;
}
std::string Json::remove_quotes(std::string& val) {
	size_t first_brace = val.find_first_of('"') + 1;
	size_t last_brace = val.find_last_of('"');
	std::string temp = val.substr(first_brace, last_brace - first_brace);
	return temp;
}

bool Json::is_int(const std::string& val) const {
	for (int i = 0; i < val.length(); ++i) {
		if (!isdigit(val[i]) && val[i] != '-' && val[i] != '+') {
			return false;
		}
	}
	return true;

}
bool Json::is_float(const std::string& val) const {
	for (int i = 0; i < val.length(); ++i) {
		if (!isdigit(val[i]) && val[i] != '-' && val[i] != '+' && val[i] != '.' && val[i] != 'e' && val[i] != 'E') {
			return false;
		}
	}
	return true;

}
bool Json::is_boolean(const std::string& val) const {
	return (val == "true" || val == "false" ? true : false);
}
bool Json::is_str(const std::string& val) const {
	if (val[0] == '"' && val[val.length() - 1] == '"') {
		return true;
	}
	return false;
}

float Json::stof(const std::string& val) {
	double temp = ::atof(val.c_str());
	return temp;
}
int Json::stoi(const std::string& val) {
	int temp = ::atoi(val.c_str());
	return temp;
}
bool Json::stob(const std::string& val) {
	return (val == "true" ? true : false);
}

Json::~Json() {
	if (m_type == ElementType::String) {
		delete string_value;
	}
	else if (m_type == ElementType::List) {
		delete list_value;
	}
	else if (m_type == ElementType::Object) {
		delete obj_value;
	}
}