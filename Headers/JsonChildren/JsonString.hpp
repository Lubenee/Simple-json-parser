#ifndef JSON_STRING_H
#define JSON_STRING_H

#include "Json.hpp"

class JsonString : public Json
{
public:
    JsonString();
    JsonString(const String _val);
    JsonString(const JsonString &rhs);
    JsonString &operator=(const JsonString &rhs);

    bool contains(const String &_value) const override;

    Json *clone() const override;
    const JsonType get_type() const override;
    void log() const override;

    ~JsonString() = default;

private:
    String val;
};
#endif // JSON_STRING_H