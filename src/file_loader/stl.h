#ifndef __STL__
#define __STL__

#include <string>

#include "models/3DObject.h"

class Stl
{
public:
    static C3DObject load(const std::string &strFilename);
};

#endif /* __STL__ */
