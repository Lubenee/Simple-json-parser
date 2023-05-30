#if !defined(JSON_FLOAT_H)
#define JSON_FLOAT_H

#include "Json.hpp"

class JsonFloat : public Json
{
public:
    JsonFloat();
    JsonFloat(const float _val);
    JsonFloat(const JsonFloat &rhs);
    JsonFloat &operator=(const JsonFloat &rhs);

    bool contains(const float &_value) const override;

    Json *clone() const override;
    const JsonType get_type() const override;
    void log() const override;

    ~JsonFloat() = default;

private:
    float val;
};

#endif // JSON_FLOAT_H
