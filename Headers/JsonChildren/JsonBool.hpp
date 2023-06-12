#if !defined(JSON_BOOL_H)
#define JSON_BOOL_H

#include "Json.hpp"

class JsonBool : public Json
{
public:
    JsonBool();
    JsonBool(bool _val);
    JsonBool(const JsonBool &rhs);

    JsonBool &operator=(const JsonBool &rhs);
    const JsonType get_type() const override;
    Json *clone() const override;

    void log() const override;
    String get_as_str() const override;

    ~JsonBool() = default;

private:
    bool val;
};

#endif // JSON_BOOL_H
