#include <iostream>
#include <string>
using namespace std;

int main(){
    //git 命令
    string gitAdd = "git add .";
    string gitCommit = "git commit -m\"update\"";
    string gitPush = "git push";

    //执行命令
    system(gitAdd.c_str());
    system(gitCommit.c_str());
    system(gitPush.c_str());
}