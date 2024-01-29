#ifndef ___POINT___
#define ___POINT___

struct cPoint
{
    cPoint(){};
    cPoint(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    float x;
    float y;
    float z;

    bool operator==(const cPoint &other) const
    {
        return this == &other || (this->x == other.x && this->y == other.y && this->z == other.z);
    }
};

#endif /* __POINT__ */
