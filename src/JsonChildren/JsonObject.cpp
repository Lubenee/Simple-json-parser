#include "JsonFactory.hpp"
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
            std::cout << val[i].key << '\n';
            found = true;
        }
    }
    return found;
}

void JsonObject::create(const String &_path, const String &new_value, int depth)
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
        for (Pair &pair : val)
        {
            if (pair.key == tokens.back())
            {
                std::cerr << "Such an element already exists within this path.\n";
                return;
            }
        }
        JsonObject::Pair temp;
        temp.key = tokens.back();
        temp.value = JsonFactory::get().parse_value(new_value.c_str());
        if (temp.value)
        {
            val.push_back(temp);
        }
        else
        {
            std::cerr << "Invalid json syntax.";
        }
        return;
    }

    for (Pair &pair : val)
    {
        if (pair.key == tokens[depth])
        {
            pair.value->create(_path, new_value, depth + 1);
        }
    }
}

void JsonObject::set(const String &_path, const String &new_value, int depth)
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
        for (Pair &pair : val)
        {
            if (pair.key == tokens.back())
            {
                delete pair.value;
                Json *temp = JsonFactory::get().parse_value(new_value.c_str());
                if (temp)
                    pair.value = temp;
                else
                    std::cerr << "Invalid json syntax.\n";
                temp = nullptr;
                return;
            }
        }
        std::cerr << "Invalid path.\n";
    }

    for (Pair &pair : val)
    {
        if (pair.key == tokens[depth])
        {
            pair.value->set(_path, new_value, ++depth);
        }
    }
}

void JsonObject::erase(const String &_path, int depth)
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
        for (size_t i = 0; i < val.size(); ++i)
            if (val[i].key == tokens.back())
            {
                val.erase(i);
                return;
            }
        std::cerr << "Invalid path.\n";
    }

    for (Pair &pair : val)
        if (pair.key == tokens[depth])
            pair.value->erase(_path, ++depth);
}

void JsonObject::move(const String &_from, String &_to,
                      int depth)
{
    Vector<String> tokens_from;
    try
    {
        _from.split('/', tokens_from);
    }
    catch (...)
    {
        std::cerr << "JSON::CREATE::Invalid path.\n";
    }

    if (depth == tokens_from.size() - 1)
    {
        bool found = false;
        for (size_t i = 0; i < val.size(); ++i)
            if (val[i].key == tokens_from.back())
            {
                found = true;
                if (_to != "")
                    if (_to[_to.size() - 1] != '/')
                        _to += "/";
                _to += val[i].key;
                _to += "\\";
                _to += val[i].value->get_as_str();
                val.erase(i);
                break;
            }
        if (!found)
            std::cerr << "Invalid path.\n";
    }

    for (Pair &pair : val)
        if (pair.key == tokens_from[depth])
            pair.value->move(_from, _to, depth + 1);

    if (depth == 0)
    {
        Vector<String> tokens;
        _to.split('\\', tokens);
        create(tokens[0], tokens[1]);
    }
}

Json *JsonObject::clone() const { return new JsonObject(val); }
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