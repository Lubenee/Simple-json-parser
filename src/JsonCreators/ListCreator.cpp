#include "ListCreator.hpp"
#include "JsonFactory.hpp"

ListCreator::ListCreator() : JsonCreator("List") {}

Json *ListCreator::create_json(const String &val) const
{
    String temp = remove_square_braces(val);
    try
    {
        return parse_list(temp);
    }
    catch (...)
    {
        std::cout << "parse unsuccessfull.\n"; // todo
    }
    return nullptr;
}

bool ListCreator::get_val(const String &_obj) const
{
    if (_obj[0] == '[')
        return true;
    return false;
}

static ListCreator __;

String ListCreator::remove_square_braces(const String &val) const
{
    size_t first_brace = val.first_index_of('[') + 1;
    size_t last_brace = val.last_index_of(']');
    String temp = val.substr(first_brace, last_brace - first_brace);
    return temp;
}

Json *ListCreator::parse_list(const String &value) const
{
    size_t index = 0;
    Vector<Json *> temp_val;
    while (index < value.length())
    {
        String new_element = JsonParse::parse_value(value, index);
        if (new_element == "") // Invalid json syntax
            continue;
        Json *temp = JsonFactory::get().parse_value(new_element.c_str());
        temp_val.push_back(temp->clone());
        delete temp;
    }

    Json *_json = new JsonList(temp_val);
    for (size_t i = 0; i < temp_val.size(); ++i)
        delete temp_val[i];
    return _json;
}