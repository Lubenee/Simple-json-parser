#ifndef NULL_CREATOR_H
#define NULL_CREATOR_H

#include "JsonCreator.hpp"
#include "JsonNull.hpp"

class NullCreator : public JsonCreator
{
public:
    NullCreator();
    Json *create_json(const String &val) const override;
    bool get_val(const String &_obj) const override;
    ~NullCreator() = default;
};

#endif //! NULL_CREATOR_H