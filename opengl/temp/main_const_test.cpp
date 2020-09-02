#include <iostream>
int test(int a)
{
    std::cout << "normal" << std::endl;
    return a;
}
// int test(const int a)
// {
//     std::cout << "const" << std::endl;
//     return a;
// }
class Test
{
private:
    const int a;
public:
    Test():a(0){}
    void show()const
    {
        std::cout << "const " << a << std::endl;
    }
    void show()
    {
        std::cout << "normal " << a << std::endl;
    }
};
int main()
{
    // const int a = 1;
    // std::cout << test(a) << std::endl;
    const Test t;
    t.show();
}
