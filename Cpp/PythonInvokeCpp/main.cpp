#include <iostream>

extern "C"
{
    typedef class __declspec(dllexport) Point
    {
    public:
        Point():_x(0.0f), _y(0.0f), _z(0.0f){}
        Point(float x, float y, float z):
        _x(x), _y(y), _z(z)
        {}
        float _x;
        float _y;
        float _z;
    } POINT;


    __declspec(dllexport) POINT add(POINT p1, POINT p2)
    {
        return POINT(p1._x + p2._x, p1._y + p2._y, p1._z + p2._z);
    }
}



int main()
{

    return 0;
}