#ifndef JSON_NULL_H
#define JSON_NULL_H

#include "Json.hpp"

class JsonNull : public Json
{
public:
    JsonNull();
    JsonNull(const String &_key);
    JsonNull(const JsonNull &rhs);
    JsonNull &operator=(const JsonNull &rhs);

    bool contains(const String& _value )const override;

    void log() const override;
    const JsonType get_type() const override;
    Json *clone() const override;

    ~JsonNull() = default;
};

#endif //! JSON_NULL_H