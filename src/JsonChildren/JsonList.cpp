#include "JsonList.hpp"
#include "JsonFactory.hpp"

JsonList::JsonList() {}

JsonList::JsonList(const Vector<Json *> &_val)
{
    for (size_t i = 0; i < _val.size(); ++i)
        val.push_back(_val[i]->clone());
}

JsonList::JsonList(const JsonList &rhs)
{
    for (size_t i = 0; i < rhs.val.size(); ++i)
        val.push_back(rhs.val[i]->clone());
}

JsonList &JsonList::operator=(const JsonList &rhs)
{
    if (this == &rhs)
        return *this;
    for (size_t i = 0; i < rhs.val.size(); ++i)
        val.push_back(rhs.val[i]->clone());
    return *this;
}

void JsonList::log() const
{
    std::cout << this->get_as_str();
}

String JsonList::get_as_str() const
{
    String temp;
    for (size_t i = 0; i < format_spaces; ++i)
        temp += " ";
    temp += "[";
    format_spaces += 2;
    for (size_t i = 0; i < val.size(); ++i)
    {
        if (val[i]->log_space())
            temp += "\n";

        temp += val[i]->get_as_str();

        if (i != val.size() - 1)
            temp += ", ";
    }
    format_spaces -= 2;
    if (!val[val.back()->log_space()])
    {
        temp += "\n";
        for (size_t i = 0; i < format_spaces; ++i)
            temp += " ";
    }

    temp += "]";
    return temp;
}

const bool JsonList::search(const String &key) const
{
    for (size_t i = 0; i < val.size(); ++i)
        val[i]->search(key);
    return true;
}

bool JsonList::contains_recursive(const String &value, const String &_curr_key, Vector<String> &keys) const
{
    for (size_t i = 0; i < val.size(); ++i)
        if (val[i]->contains_recursive(value, _curr_key, keys))
            return true;
    return false;
}

void JsonList::create(const String &_path, const String &new_value, int depth)
{
    Vector<String> tokens;
    try
    {
        _path.split('/', tokens);
    }
    catch (...)
    {
        std::cerr << "JSON::CREATE::Invalid path.\n";
    }

    if (depth == tokens.size() - 1)
    {
        Json *temp;
        temp = JsonFactory::get().parse_value(new_value.c_str());
        if (temp)
            val.push_back(temp);
        else
            std::cerr << "incorrect json syntax.";
        temp = nullptr;
        return;
    }

    for (Json *value : val)
    {
        value->create(_path, new_value, ++depth);
    }
}

void JsonList::erase(const String &_path, int depth)
{
    Vector<String> tokens;
    try
    {
        _path.split('/', tokens);
    }
    catch (...)
    {
        std::cerr << "JSON::CREATE::Invalid path.\n";
    }

    for (Json *elem : val)
    {
        elem->erase(_path, ++depth);
    }
}

Json *JsonList::clone() const
{
    return new JsonList(val);
}

JsonList::~JsonList()
{
    for (auto &i : val)
        delete i;
}
