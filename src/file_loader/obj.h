#ifndef __OBJ__
#define __OBJ__

#include <optional>
#include <string>

#include "../models/3DObject.h"

class Obj
{
public:
    static std::optional<C3DObject> load(const std::string &strFilename);
};

#endif // __OBJ__