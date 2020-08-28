#include <iostream>
#include <string>
#include <vector>
#include "../../include/utils/string_lib.h"
#include "../../include/basic/point3d.h"
using namespace std;
using namespace Eigen;
using namespace wh::basic;
int main()
{   
    POINT3D p(1,2,3);
    cout << p.data << endl;
    cout << p << endl;
    cout << p * 3 << endl;
    cout << 3.1 * p << endl;
}