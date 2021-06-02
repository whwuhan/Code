/**
 * 可变参数练习
*/

#include <iostream>
#include <cstdarg> //支持可变参数的头文件 包含va_arg va_start va_end va_list
using namespace std;

// 求和函数 通常可变参数第一个参数要包含可变参数的个数信息
int add(int paramNumber, ...) // paramNumber 可变参数的数量
{
    va_list argPtr; // 用于接收可变参数，现在还没有接收
    int sum = 0;
    int nArgValue;
    /**
     * va_start(args,paramN) 令对可变函数参数的访问
     * 第一个参数为va_list类型的变量，va_list接收所有的可变参数
     * 第二个参数为"..."前最后一个参数，也就是可变参数前的，最后一个参数
     * 将args初始化为指向可变参数列表第一个参数
    */
    va_start(argPtr, paramNumber); // 接收可变参数
    while(paramNumber > 0)
    {
        /**
         * va_arg(args,type)  访问下一个可变函数参数。
         * 第一个参数为va_list类型的变量
         * 第二个参数是返回值的类型
         * 调用va_arg获取当前的参数，并自动更新指向下一个可变参数
        */
        nArgValue = va_arg(argPtr, int);
        sum += nArgValue;
        paramNumber--;
        cout << nArgValue << endl;
    }

    /**
     * va_end(args)  结束可变参数函数的遍历
     * 释放va_arg变量
    */
   va_end(argPtr);
   return sum;
}


int main()
{
    int result = add(3, 3, 4, 5);
    cout << result << endl;
}