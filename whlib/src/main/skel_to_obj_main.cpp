#include <iostream>
#include <fstream>
#include <vector>
#include "../../include/utils/io/io_obj.h"
#include "../../include/utils/io/io_skel.h"
#include "../../include/utils/string_lib.h"
#include "../../include/basic/abstract_data_type/curve.h"
#include "../../include/basic/point3d.h"
using namespace wh::utils;
using namespace wh::basic;
using namespace std;
int main()
{
    ifstream file_list("C:/Users/Administrator/Desktop/CSCD/CSCD/experimental_data/L1/file_list.txt");
    if(!file_list.is_open())
    {
        cout << "no file_list." << endl;
        return 0;
    }
    string line;
    vector<string> line_split;
    while(getline(file_list, line))
    {
        line_split = split(line, ".");
        if("skel" == line_split[1])
        {
            vector< adt::Curve<Point3d> > curves;
            io::load_curves_skel("C:/Users/Administrator/Desktop/CSCD/CSCD/experimental_data/L1/" + line, &curves);
            io::save_curves_obj("C:/Users/Administrator/Desktop/CSCD/CSCD/experimental_data/L1/" + line_split[0] + ".obj", &curves);
        }
    }
    file_list.close();
}