#include <iostream>
#include <string>
#include <vector>
#include "../../include/utils/string_lib.h"
#include "../../include/basic/point3d.h"
int main()
{
    std::string s = "a,b*c*d,e";
    std::vector<std::string> v = wh::utils::split(s, ",*"); //可按多个字符来分隔;
    for(std::vector<std::string>::size_type i = 0; i != v.size(); ++i)
    {
        std::cout << v[i] << " " << std::endl;
    }
}