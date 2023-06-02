#include "ObjectCreator.hpp"
#include "JsonFactory.hpp"

ObjectCreator::ObjectCreator() : JsonCreator("Object") {}

Json *ObjectCreator::create_json(const String &val) const
{
    String temp = remove_curly_braces(val);
    try
    {
        return parse_object(temp);
    }
    catch (...)
    {
        std::cout << "parse unsuccessfull.\n"; // todo
    }
    return nullptr;
}

bool ObjectCreator::get_val(const String &_obj) const
{
    for (size_t i = 0; i < _obj.size(); ++i)
        if (_obj[i] == '{')
            return true;
    return false;
}

String ObjectCreator::remove_curly_braces(const String &val) const
{
    size_t first_brace = val.first_index_of('{') + 1;
    size_t last_brace = val.last_index_of('}');
    String temp = val.substr(first_brace, last_brace - first_brace);
    return temp;
}

String ObjectCreator::parse_obj_key(const String &value, size_t &index) const
{
    char new_key[1024] = {
        '\0',
    };
    int char_index = 0;
    for (size_t i = index; i < value.length(); ++i)
    {
        if (value[i] == '"')
        {
            while (value[++i] != '"' && i < value.length())
            {
                new_key[char_index++] = value[i];
            }
            index = i;
            break;
        }
    }
    while (value[++index] != ':' && index < value.length() - 1)
        continue;
    index++;
    return String(new_key);
}

Json *ObjectCreator::parse_object(const String &value) const
{
    size_t index = 0;
    Vector<Pair> temp;
    while (index < value.length())
    {
        String new_key(parse_obj_key(value, index));
        String new_element(JsonParse::parse_value(value, index));
        if (new_element == "")
            continue;

        Json *_json = JsonFactory::get().parse_value(new_element.c_str());
        temp.push_back({_json, new_key});
        delete _json;
    }

    return new JsonObject(temp);
}

String JsonParse::parse_value(const String &value, size_t &index)
{
    Vector<char> stack;
    char delimiter, new_value[1024] = {'\0'};
    String new_value_str;
    size_t string_index = 0;
    bool in_string = false, in_object = false, in_list = false;
    for (size_t i = index; i < value.length(); i++)
    {
        if (value[i] == '\r' || value[i] == '\n')
        {
            if (i == value.length() - 1)
            {
                index = i + 1;
                break;
            }
            continue;
        }
        else if (value[i] == '\"')
        {
            if (in_object || in_list)
            {
                new_value[string_index++] = '\"';
                continue;
            }
            delimiter = '\"';
            if (stack.size() > 0)
            {
                if (stack.back() == delimiter)
                {
                    in_string = false;
                    new_value[string_index++] = '\"';
                    stack.pop_back();
                }
                else
                {
                    in_string = true;
                    stack.push_back(delimiter);
                }
            }
            else
            {
                in_string = true;
                new_value[string_index++] = '\"';
                stack.push_back(delimiter);
            }
        }
        else if (value[i] == ' ' && !in_string && !in_object)
        {
            continue;
        }
        else if (value[i] == ',' && stack.empty())
        {
            index = ++i;
            break;
        }
        else if (value[i] == '[')
        {
            delimiter = '[';
            stack.push_back(delimiter);
            new_value[string_index++] = delimiter;
            in_list = true;
        }
        else if (value[i] == ']')
        {
            delimiter = ']';
            if (stack.back() == '[')
            {
                in_list = false;
                stack.pop_back();
            }
            else
                stack.push_back(delimiter);
            new_value[string_index++] = delimiter;
        }
        else if (value[i] == '{')
        {
            delimiter = '{';
            stack.push_back(delimiter);
            new_value[string_index++] = delimiter;
            in_object = true;
        }
        else if (value[i] == '}')
        {
            delimiter = '}';
            if (stack.back() == '{')
            {
                in_object = false;
                stack.pop_back();
            }
            else
                stack.push_back(delimiter);
            new_value[string_index++] = delimiter;
        }
        else
            new_value[string_index++] = value[i];

        if (i == value.length() - 1)
            index = i + 1;
    }
    if (stack.empty())
    {
        new_value_str = new_value;
        return new_value_str;
    }
    else
    {
        // -> incorrect format, missing braces, etc
        for (size_t i = 0; i < stack.size(); ++i)
        {
            std::cout
                << "Incorrect format!\nMissing delimiter(s): "
                << stack[i] << '\n';
        }
        index = String::npos;
        return "";
    }
}

static ObjectCreator __;