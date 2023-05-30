#if !defined(JSON_BOOL_H)
#define JSON_BOOL_H

#include "Json.hpp"

class JsonBool : public Json
{
public:
    JsonBool();
    JsonBool(bool _val);
    JsonBool(const JsonBool &rhs);

    bool contains(const bool &_value) const override;

    JsonBool &operator=(const JsonBool &rhs);
    const JsonType get_type() const override;
    Json *clone() const override;

    void log() const override;

    ~JsonBool() = default;

private:
    bool val;
};

#endif // JSON_BOOL_H
