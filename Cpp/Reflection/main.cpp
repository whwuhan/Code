/**
 * 编写反射的大致思路：
 * 1.让你的类继承某个接口（该接口继承自 ReflectObject 类）
 * 2.编写一个对应的工厂类，并实例化一个工厂类对象
 * 3.调用反射器的 registerFactory 接口，将你的类名和工厂类对象保存到反射器中
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

//-------------------反射器实现-------------------

//所有需要反射的类需要继承ReflectObject
class ReflectObject{
public:
    virtual ~ReflectObject(){}
};

//对象工厂抽象类（也就是基类），用来生成对象实例
class ObjectFactory{
public:
    //构造函数
    ObjectFactory(){
        cout << "ObjectFactory()" << endl;
    }
    //虚析构函数
    virtual ~ObjectFactory(){
        cout << "~ObjectFactory()" << endl;
    }
    //纯虚函数，获得实例的接口
    virtual ReflectObject* newInstance() = 0;
};

//反射器，用来管理（对象名，对象工厂）的映射关系
class Reflector{
public:
    Reflector(){}

    //析构函数，释放new的内存
    ~Reflector(){
        for(auto it = objectFactories.begin(); it != objectFactories.end(); it++){
            delete it->second;
        }
        objectFactories.clear();
    }

    //将需要反射的类的对象工厂注册到Reflector中
    void registerFactory(const string& className, ObjectFactory* of){
        auto it = objectFactories.find(className);
        if(it != objectFactories.end()){
            cout << "该类的生产工厂已经存在..." << endl;
        }else{
            objectFactories[className] = of;
        }
    }

    //通过类名获取对象实例
    ReflectObject* getNewInstance(const string className){
        auto it = objectFactories.find(className); 
        //有对应的工厂（已经注册）
        if(it != objectFactories.end()){
            return it->second->newInstance();
        }else{//没有注册返回空指针
            cout << "还没有注册生产工厂" << endl;
            return nullptr;
        }
    }
private:
    //存储类名和生产工厂
    map<string, ObjectFactory*> objectFactories;
};

//生成反射器的函数，保证全局只有一个反射器
Reflector& reflector(){
    static Reflector reflector;//static只会在程序初始化时生成反射器
    return reflector;
}

//利用宏定义将需要反射的类，注册到Reflector的objectFactories中
//宏定义中##表示拼接，#表示将后面的参数变成字符串
#define REFLECT(className) \
class ObjectFactory_##className : public ObjectFactory{ \
public: \
    /* 对应工厂的构造函数 */ \
    ObjectFactory_##className(){ \
        cout << "ObjectFactory_" << #className << "()" << endl; \
    } \
    /* 对应工厂的析构函 */ \
    virtual ~ObjectFactory_##className(){ \
        cout << "~ObjectFactory_" << #className << "()" << endl; \
    } \
    /* 重写ObjectFactory中的 newInstance()函数 */ \
    ReflectObject* newInstance(){ \
        return new className(); \
    } \
}; \
/* 注册类的生产工厂 */ \
class Register_##className{ \
public: \
    Register_##className(){ \
        reflector().registerFactory(#className, new ObjectFactory_##className()); \
    } \
}; \
/* 利用构造函数注册生产工厂到 reflector 对象当中 */ \
Register_##className register_##className; \
/* 这里之所以使用构造函数来完成类的注册，是因为保证可以在main函数之前完成注册 */
//宏定义完成

//添加通过类名获取对象实例的模板方法
template<typename T>
T* getNewInstance(const string& className){
    return dynamic_cast<T*>(reflector().getNewInstance(className));
}

//Person基类继承ReflectObject
class Person : public ReflectObject{
public:
    Person(){
        cout << "Person()" << endl;
    }
    virtual ~Person(){
        cout << "~Person()" << endl;
    }
    virtual void show(){
        cout << "Hello, I'm Person" << endl;
    }
};

class Wuhan : public Person{
public:
    Wuhan(){
        cout << "Wuhan()" << endl;
    }
    virtual ~Wuhan(){
        cout << "~Wuhan()" << endl;
    }
    virtual void show(){
        cout << "Hello, I'm Wuhan" << endl;
    }
};
//将Wuhan注册
REFLECT(Wuhan)

int main(){
    Person* wuhan = getNewInstance<Person>("Wuhan");
    wuhan->show();
    delete wuhan;
}