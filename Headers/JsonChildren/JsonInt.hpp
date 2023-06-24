#if !defined(JSON_INT_H)
#define JSON_INT_H

#include "Json.hpp"

class JsonInt : public Json
{
public:
    /**
        @brief
            Default constructor.
    */
    JsonInt();
    /**
        @brief
            Sets the element's int value to the passed value.
    */
    JsonInt(const int _val);
    /**
        @brief
            Default copy constructor.
    */
    JsonInt(const JsonInt &rhs);
    JsonInt &operator=(const JsonInt &rhs);

    /**
        @brief
            Clone method.
    */
    Json *clone() const override;

    /**
        @brief
            Logs the current int value.
    */
    void log() const override;

    /**
      @brief
        Returns the current int value as a string.
  */
    String get_as_str() const override;
    bool contains_recursive(const String &_value, const String &_curr_key, Vector<String> &keys) const override;

    ~JsonInt() = default;

private:
    int val;
};

#endif // JSON_INT_H
