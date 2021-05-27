from ctypes import *
class Point(Structure):
    _fields_ = \
    [
        ("_x", c_float),
        ("_y", c_float),
        ("_z", c_float),
    ]
if __name__ == "__main__":
    p1 = Point(1.0, 2.0, 3.0)
    p2 = Point(4.0, 5.0, 6.0)
    testDll = cdll.LoadLibrary("./libtest.dll")
    # testDll.add.argtypes = [Point, Point]
    # testDll.add.restype = [Point]
    # p3 = testDll.add(p1, p2)