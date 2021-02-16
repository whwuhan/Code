'''
* 表示当成元组传入方法
** 表示当成字典传入方法
'''
def test(a,b):
    print(str(a)+" "+str(b))

def test1(*args):
    print(args)

def test2(**kargv):
    print(kargv)
if __name__ == '__main__':
    a = {"a":1,"b":2}
    test(**a)
    b=[1,2,3]
    test1(b)
    test2(**a)#注意这里test2(a)要报错，因为这里要把a当成字典传入