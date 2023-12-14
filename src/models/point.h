#ifndef ___POINT___
#define ___POINT___

class cPoint {
    public:
        cPoint(float x, float y, float z);
        ~cPoint();

    private:
        float m_x, m_y, m_z;
};

#endif /* __POINT__ */
