#if !defined(JSON_LIST_H)
#define JSON_LIST_H

#include "Json.hpp"

class JsonList : public Json
{
public:
    JsonList();
    JsonList(const Vector<Json *> &_val);
    JsonList(const JsonList &rhs);
    JsonList &operator=(const JsonList &rhs);

    const bool search(const String &key) const override;
    bool contains(const String &value) const override;
    Json *clone() const override;
    const JsonType get_type() const override;
    void log() const override;

    ~JsonList();

private:
    Vector<Json *> val;
};

#endif // JSON_LIST_H
