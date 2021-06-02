#include <iostream>
#include <vector>
using namespace std;
/**
 * 观察者模式：一种一对多依赖关系
 * 一个观察者只能观察一个目标
 * 一个目标可以有多个观察者
*/
class Subject;

// ============观察者基类===============
// 观察者基类，当观察的目标对象状态改变的时候
// 目标会通知观察他的所有观察者
class Observer
{
public:
    Observer(string name, Subject* subject) :
    m_name(name), m_subject(subject)
    {}
    virtual ~Observer(){}
    // 纯虚函数，接口用于打印观察者的信息和观察目标的状态
    virtual void update() = 0;
    // 设置目标
    virtual void set_subject(Subject* subject) = 0;
protected:
    string m_name;      // 观察者名称
    Subject* m_subject; // 观察的目标
};

// ============目标基类=============
// 观察目标基类，内部维护一个观察者数组
// 当状态改变后，通知所有的观察者
class Subject
{
public:
    Subject(string name, int status) :
    m_name(name), m_status(status)
    {}
    virtual ~Subject(){}
    // 添加一个观察者
    void add_observer(Observer* observer);
    // 删除一个观察者
    void delete_observer(Observer* observer);
    // 通知所有的观察者
    void notify_observers();
    // 获取当前状态
    virtual int get_status() = 0;
    // 设置状态
    virtual void set_status(int status) = 0;
protected:
    // 当前观察目标的所有观察者
    vector<Observer*> m_observers;
    // 观察目标名字
    string m_name;
    // 目标状态
    int m_status = 0;
};

// 添加一个观察者
void Subject::add_observer(Observer* observer)
{
    m_observers.push_back(observer);
    // 同时更改观察者的目标
    observer->set_subject(this);
}

// 删除一个观察者
void Subject::delete_observer(Observer* observer)
{
    for(auto it = m_observers.begin(); it != m_observers.end(); it++)
    {
        if(*it == observer)
        {
            m_observers.erase(it);
            return;
        }
    }
}

// 通知所有的观察者
void Subject::notify_observers()
{
    for(auto it = m_observers.begin(); it != m_observers.end(); it++)
    {
        (*it)->update();
    }
}

// =========具体的观察者=========
class ConcreteObserver : public Observer
{
public:
    ConcreteObserver(string name, Subject* subject) :
    Observer(name, subject)
    {}
    ~ConcreteObserver() {};
    virtual void update();
    virtual void set_subject(Subject* subject);
};

void ConcreteObserver::update()
{
    cout << "update observer[" << m_name << "] status:" << m_subject->get_status() << endl;
}

void ConcreteObserver::set_subject(Subject* subject)
{
    m_subject = subject;
}

// =============具体的目标类===========
class ConcreteSubject : public Subject
{
public:
    ConcreteSubject(string name, int status) :
    Subject(name, status)
    {}
    // 获取状态
    virtual int get_status();
    // 设置状态
    virtual void set_status(int status);
};

int ConcreteSubject::get_status()
{
    return m_status;
}

void ConcreteSubject::set_status(int status)
{
    m_status = status;
}

int main()
{
    Subject* subject_a = new ConcreteSubject("subject_a", 0);
    Subject* subject_b = new ConcreteSubject("subject_b", 0);

    Observer* observer_a = new ConcreteObserver("observer_a", subject_a);
    Observer* observer_b = new ConcreteObserver("observer_b", subject_b);

    // 目标添加观察者
    subject_a->add_observer(observer_a);
    subject_b->add_observer(observer_b);

    // 目标a改变状态，通知其观察者
    subject_a->set_status(1);
    subject_a->notify_observers();

    // 目标b改变状态，通知其观察者
    subject_b->set_status(2);
    subject_b->notify_observers();

    cout << "-----------" << endl;
    // 目标a再添加一个观察者
    subject_a->add_observer(observer_b);
    subject_a->set_status(3);
    subject_a->notify_observers();

    delete subject_a;
    delete subject_b;
    delete observer_a;
    delete observer_b;
    return 0;
}