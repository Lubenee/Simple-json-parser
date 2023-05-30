#if !defined(JSON_INT_H)
#define JSON_INT_H

#include "Json.hpp"

class JsonInt : public Json
{
public:
    JsonInt();
    JsonInt(const int _val);
    JsonInt(const JsonInt &rhs);
    JsonInt &operator=(const JsonInt &rhs);

    Json *clone() const override;
    const JsonType get_type() const override;
    void log() const override;

    bool contains(const int &_value) const override;

    ~JsonInt() = default;

private:
    int val;
};

#endif // JSON_INT_H
