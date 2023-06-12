#if !defined(JSON_FLOAT_H)
#define JSON_FLOAT_H

#include "Json.hpp"
#include <string.h>

class JsonFloat : public Json
{
public:
    JsonFloat();
    JsonFloat(const float _val);
    JsonFloat(const JsonFloat &rhs);
    JsonFloat &operator=(const JsonFloat &rhs);

    Json *clone() const override;
    const JsonType get_type() const override;
    void log() const override;
    String get_as_str() const override;

    ~JsonFloat() = default;

private:
    float val;
};

#endif // JSON_FLOAT_H
