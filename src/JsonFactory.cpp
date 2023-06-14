#include "JsonFactory.hpp"

JsonFactory &JsonFactory::get()
{
    static JsonFactory instance;
    return instance;
}

void JsonFactory::register_valid_json(const JsonCreator *rhs)
{
    creators[count++] = rhs;
}

Json *JsonFactory::parse_value(const char *value) const
{
    const char *nonWhitespaceChar = value;
    while (std::isspace(*nonWhitespaceChar))
        ++nonWhitespaceChar;
    String val(value);

    const JsonCreator *crt = get_creator(val);
    if (!crt)
    {
        std::cerr << "Couldn't parse Json.\n";
        return nullptr;
    }
    try
    {
        return crt->create_json(val);
    }
    catch (...)
    {
        throw std::invalid_argument("Couldn't parse Json");
    }
}

Json *JsonFactory::parse_value(std::ifstream &ifs) const
{
    if (!ifs.is_open())
        return nullptr;

    ifs.seekg(0, std::ios::end);
    size_t file_size = ifs.tellg();
    char *buffer = new char[file_size];

    ifs.seekg(0, std::ios::beg);
    ifs.read(&buffer[0], file_size);

    String file(buffer);
    delete[] buffer;

    ifs.close();
    return parse_value(file.c_str());
}

Json *JsonFactory::parse_file(const char *_filename) const
{
    std::ifstream ifs;
    ifs.open(_filename, std::ios::in);
    if (!ifs.is_open())
        return nullptr;

    return parse_value(ifs);
}

const JsonCreator *JsonFactory::get_creator(const String &_val) const
{
    for (size_t i = 0; i < count; ++i)
        if (creators[i]->get_val(_val))
            return creators[i];
    return nullptr;
}