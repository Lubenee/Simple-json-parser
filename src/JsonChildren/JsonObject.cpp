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

const bool JsonObject::search(const String &key) const
{
    static Vector<Pair> matches;
    for (size_t i = 0; i < val.size(); ++i)
    {
        if (val[i].key.includes(key))
        {
            matches.push_back(val[i]);
        }
        val[i].value->search(key);
    }

    if (matches.empty())
        return false;

    for (size_t i = 0; i < matches.size(); ++i)
    {
        matches[i].value->log();
        std::cout << '\n';
    }
    return true;
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
    std::cout << "{\n";
    format_spaces += 2;

    JsonType prev_elem = JsonType::Null;
    for (size_t i = 0; i < val.size(); ++i)
    {
        for (size_t i = 0; i < format_spaces; ++i)
            std::cout << ' ';

        std::cout << Quote << val[i].key << Quote << " : ";
        val[i].value->log();
        if (i != val.size() - 1)
            std::cout << ",\n";
        prev_elem = val[i].value->get_type();
    }
    format_spaces -= 2;

    std::cout << '\n';
    for (size_t i = 0; i < format_spaces; ++i)
        std::cout << ' ';
    std::cout << '}';
}

JsonObject::~JsonObject() {}

/*==========================================================================*/
/*==========================================================================*/
/*=============================Pair Definitions=============================*/
/*==========================================================================*/
/*==========================================================================*/

Pair::Pair() : value(nullptr), key("") {}

Pair::Pair(const Json *_value) : key("")
{
    value = _value->clone();
}

Pair::Pair(const Json *_value, const String &_key)
{
    value = _value->clone();
    key = _key;
}

Pair::Pair(const Pair &rhs) : value(rhs.value->clone()), key(rhs.key) {}

Pair &Pair::operator=(const Pair &rhs)
{
    if (this == &rhs)
        return *this;

    key = rhs.key;
    if (value)
        delete value;
    value = rhs.value->clone();
    return *this;
}

bool Pair::operator==(const Pair &rhs)
{
    return false; // TODO?
}

Pair::~Pair() { delete value; }
