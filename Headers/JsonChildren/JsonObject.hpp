#if !defined(JSON_OBJECT_H)
#define JSON_OBJECT_H

#include "Json.hpp"

struct Item
{
    Json *value;
    String key;

    Item();
    Item(const Json *_value);
    Item(const Json *_value, const String &_key);
    Item(const Item &_rhs);
    Item &operator=(const Item &rhs);
    bool operator==(const Item &rhs);

    ~Item();
};
class JsonObject : public Json
{
public:
    JsonObject();
    JsonObject(const Vector<Item> &_val);
    JsonObject(const JsonObject &rhs);
    JsonObject &operator=(const JsonObject &rhs);

    const bool search(const String &key) const override;

    bool contains(const String &_value) const override;

    Json *clone() const override;
    const JsonType get_type() const override;
    void log() const override;

    ~JsonObject();

private:
    Vector<Item> val;
};

#endif // JSON_OBJECT_H
