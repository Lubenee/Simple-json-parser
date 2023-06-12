#include "JsonObject.hpp"

JsonObject::JsonObject() {}

JsonObject::JsonObject(const Vector<Pair> &_val)
{
    for (size_t i = 0; i < _val.size(); ++i)
        val.push_back(_val[i]);
}
JsonObject::JsonObject(const JsonObject &rhs)
{
    for (size_t i = 0; i < rhs.val.size(); ++i)
        val.push_back(rhs.val[i]);
}
JsonObject &JsonObject::operator=(const JsonObject &rhs)
{
    val = rhs.val;
    return *this;
}

Vector<JsonObject::Pair> JsonObject::search_matches;
const bool JsonObject::search(const String &key) const
{
    for (size_t i = 0; i < val.size(); ++i)
    {
        if (val[i].key.includes(key))
            search_matches.push_back(val[i]);
        val[i].value->search(key);
    }
    if (search_matches.empty())
        return false;
    return true;
}

void JsonObject::log_search_results() const
{
    for (Pair &match : search_matches)
    {
        match.value->log();
        std::cout << '\n';
    }
    search_matches.clear();
    std::cout << std::flush;
}

bool JsonObject::contains(const String &_value) const
{
    bool found = false;
    for (size_t i = 0; i < val.size(); ++i)
    {
        if (val[i].value->contains(_value))
        {
            bool nested_obj = val[i].value->get_type() == JsonType::Object;
            if (nested_obj)
                std::cout << val[i].key << '/';
            else
            {
                std::cout << "Value " << Quote << _value << Quote
                          << " found at key: ";
                std::cout << val[i].key << '/';
            }
            if (!nested_obj)
                std::cout << std::endl;
            found = true;
        }
    }
    return found;
}

Json *JsonObject::clone() const { return new JsonObject(val); }
const JsonType JsonObject::get_type() const { return JsonType::Object; }
void JsonObject::log() const
{
    std::cout << this->get_as_str();
}

String JsonObject::get_as_str() const
{
    String temp;
    for (size_t i = 0; i < format_spaces; ++i)
        temp += " ";
    temp += "{\n";
    format_spaces += 2;

    for (size_t i = 0; i < val.size(); ++i)
    {

        for (size_t i = 0; i < format_spaces; ++i)
            temp += " ";

        temp += Quote;
        temp += val[i].key;
        temp += Quote;
        temp += " : ";
        if (val[i].value->log_space())
            temp += "\n";

        temp += val[i].value->get_as_str();
        if (i != val.size() - 1)
            temp += ",\n";
    }
    format_spaces -= 2;

    temp += "\n";
    for (size_t i = 0; i < format_spaces; ++i)
        temp += " ";
    temp += "}";
    return temp;
}

JsonObject::~JsonObject() {}

/*==========================================================================*/
/*==========================================================================*/
/*=============================Pair Definitions=============================*/
/*==========================================================================*/
/*==========================================================================*/

JsonObject::Pair::Pair() : value(nullptr), key("") {}

JsonObject::Pair::Pair(const Json *_value) : key("")
{
    value = _value->clone();
}

JsonObject::Pair::Pair(const Json *_value, const String &_key)
{
    value = _value->clone();
    key = _key;
}

JsonObject::Pair::Pair(const JsonObject::Pair &rhs) : value(rhs.value->clone()), key(rhs.key) {}

JsonObject::Pair &JsonObject::Pair::operator=(const JsonObject::Pair &rhs)
{
    if (this == &rhs)
        return *this;

    key = rhs.key;
    if (value)
        delete value;
    value = rhs.value->clone();
    return *this;
}

bool JsonObject::Pair::operator==(const JsonObject::Pair &rhs)
{
    return false; // TODO?
}

JsonObject::Pair::~Pair() { delete value; }