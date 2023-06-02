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
    std::cout << "[";

    bool nested_objects = (val[0]->get_type() == JsonType::Object);
    if (nested_objects)
        std::cout << '\n';

    format_spaces += 2;
    for (size_t i = 0; i < val.size(); ++i)
    {
        if (nested_objects)
            for (size_t i = 0; i < format_spaces; ++i)
                std::cout << ' ';

        val[i]->log();

        bool last_elem = (i != val.size() - 1);
        if (last_elem)
            std::cout << ", ";
        if (nested_objects)
            std::cout << std::endl;
    }
    format_spaces -= 2;

    if (nested_objects)
        for (size_t i = 0; i < format_spaces; ++i)
            std::cout << ' ';

    std::cout << ']';
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
