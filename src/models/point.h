#ifndef ___POINT___
#define ___POINT___

struct cPoint
{
    float x;
    float y;
    float z;

    bool operator==(const cPoint &other) const
    {
        return this == &other || (this->x == other.x && this->y == other.y && this->z == other.z);
    }
};

#endif /* __POINT__ */
