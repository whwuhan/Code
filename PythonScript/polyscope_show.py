import numpy as np
import polyscope as ps
import io_obj as io
# polyscope 显示 曲线 点云 骨架线

# 初始化
def init():
    ps.init()

# 显示
def show():
    ps.show()

# 添加点云
def add_point_cloud(points, name = "my_point_cloud", color = (0.109,0.388,0.890), radius = 0.001):
    my_point_cloud = ps.register_point_cloud(name, points)
    my_point_cloud.set_color(color)
    my_point_cloud.set_radius(radius)
    return my_point_cloud

# 添加网状结构
def add_net_work(nodes, edges, name = "my_net_work", color = (0.89,0.69,0.1), radius = 0.00200):
    edges = edges - np.ones(edges.shape)#obj文件坐标索引从1开始，polyscope要求从0开始
    my_net_work = ps.register_curve_network(name, nodes, edges)
    my_net_work.set_color(color)
    my_net_work.set_radius(radius)
    return my_net_work

# 添加骨架线
def add_skeleton(nodes, edges, \
        name = "my_skeleton", \
        point_color = (1,0,0), \
        line_color = (0.89,0.69,0.1), \
        point_radius = 0.00424, \
        line_radius = 0.00146):
    skeleton_points = add_point_cloud(nodes, name + "_points", point_color, point_radius)
    skeleton_line = add_net_work(nodes, edges, name + "_line", line_color, line_radius)
    return skeleton_points,skeleton_line
def screenshot():
    ps.screenshot("test.tga",True)

if __name__ == "__main__":
    # 初始化
    init()
    # 点云
    point_cloud_dir = r"/Users/wuhan/wuhan/研究生/研一/研一下/CSCD论文/CSCD/CSCD/experimental_data/point_cloud/generated/obj/"
    point_cloud_file = r"tree5_missing_3.obj"
    point_cloud_path = point_cloud_dir + point_cloud_file
    point_cloud = io.load_point_cloud_obj(point_cloud_path)
    add_point_cloud(point_cloud)
    # 骨架线
    skeleton_dir = r"/Users/wuhan/wuhan/研究生/研一/研一下/CSCD论文/CSCD/CSCD/experimental_data/skeleton/my_skeleton/"
    skeleton_file = r"tree5_missing_down_sampling_con_rep_smooth_3.obj"
    skeleton_path = skeleton_dir + skeleton_file
    points,edges = io.load_curves_obj(skeleton_path)
    add_skeleton(points,edges)
    # 显示
    show()

   
