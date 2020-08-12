#include <iostream>
#include "../../include/basic/point_cloud.h"
using namespace std;
using namespace Eigen;
using namespace wh::basic;
int main()
{   
    MatrixXd mat(4, 3);
    mat << 
    1, 2, 3,
    4, 5, 6,
    7, 8, 9,
    10, 11, 12;
    POINT_CLOUD pc(mat);
    cout << pc << endl;
    cout << pc[0] << endl;
    cout << pc * pc[0].data.transpose() << endl;
}