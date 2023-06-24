#ifndef JSON_STRING_H
#define JSON_STRING_H

#include "Json.hpp"

/**
    @brief
        Publicly inherits the Json class.
        Holds string values.
*/
class JsonString : public Json
{
public:
  /**
      @brief
         Default constructor.
    */
  JsonString();
  /**
    @brief
      Sets the current element's string value to the passed string.
*/
  JsonString(const String _val);
  /**
    @brief
      Default copy constructor.
*/
  JsonString(const JsonString &rhs);
  JsonString &operator=(const JsonString &rhs);

  /**
    @brief
      Clone method.
*/
  Json *clone() const override;
  /**
    @brief
      Logs the current string.
*/
  void log() const override;

  /**
    @brief
      Returns the current string.
  */
  String get_as_str() const override;

  bool contains_recursive(const String &_value, const String &_curr_key, Vector<String> &keys) const override;

  /**
    @brief
      Default destructor.
  */
  ~JsonString() = default;

private:
  String val;
};
#endif // JSON_STRING_H