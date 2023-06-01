#if !defined(JSON_OBJECT_H)
#define JSON_OBJECT_H

#include "Json.hpp"

struct Pair
{
    Json *value;
    String key;

    Pair();
    Pair(const Json *_value);
    Pair(const Json *_value, const String &_key);
    Pair(const Pair &_rhs);
    Pair &operator=(const Pair &rhs);
    bool operator==(const Pair &rhs);

    ~Pair();
};
class JsonObject : public Json
{
public:
    JsonObject();
    JsonObject(const Vector<Pair> &_val);
    JsonObject(const JsonObject &rhs);
    JsonObject &operator=(const JsonObject &rhs);

    const bool search(const String &key) const override;

    bool contains(const String &_value) const override;

    Json *clone() const override;
    const JsonType get_type() const override;
    void log() const override;

    ~JsonObject();

private:
    Vector<Pair> val;
};

#endif // JSON_OBJECT_H
