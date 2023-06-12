#if !defined(JSON_OBJECT_H)
#define JSON_OBJECT_H

#include "Json.hpp"

class JsonObject : public Json
{
public:
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
    void log_search_results() const override;
    String get_as_str() const override;

    bool log_space() const override { return true; }

    ~JsonObject();

private:
    Vector<Pair> val;
    static Vector<Pair> search_matches;
};

#endif // JSON_OBJECT_H
