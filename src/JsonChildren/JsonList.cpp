#include "JsonList.hpp"

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
    temp += "\n";

    for (size_t i = 0; i < format_spaces; ++i)
        temp += " ";
    temp += "]";
    return temp;
}

const bool JsonList::search(const String &key) const
{
    for (size_t i = 0; i < val.size(); ++i)
        val[i]->search(key);
    return true;
}

bool JsonList::contains(const String &value) const
{
    for (size_t i = 0; i < val.size(); ++i)
    {
        if (val[i]->contains(value))
        {
            return true;
        }
    }
    return false;
}

const JsonType JsonList::get_type() const { return JsonType::List; }

Json *JsonList::clone() const
{
    return new JsonList(val);
}

JsonList::~JsonList()
{
    for (auto &i : val)
        delete i;
}
