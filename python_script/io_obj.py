# obj文件读取
import numpy as np
import datetime

# 读入点云
def load_point_cloud_obj(file_name):
    point_cloud = []
    # 打开文件
    with open(file_name) as file:
        # 先读一行
        line = file.readline()
        # 读到末尾
        while line:
            # 读点
            if line.startswith("v"):
                point = []
                line_split = line.split()
                point.append(float(line_split[1]))
                point.append(float(line_split[2]))
                point.append(float(line_split[3]))
                point_cloud.append(point)
                line = file.readline()
            else:
                line = file.readline()
    return np.array(point_cloud)

# 读入曲线
def load_curves_obj(file_name):
    nodes = []
    edges = []
    # 打开文件
    with open(file_name) as file:
        # 先读一行
        line = file.readline()
        # 读到末尾
        while line:
            # 读点
            if line.startswith("v"):
                node = []
                line_split = line.split()
                node.append(float(line_split[1]))
                node.append(float(line_split[2]))
                node.append(float(line_split[3]))
                nodes.append(node)
                line = file.readline()
                continue
            #读边 注意obj文件边的索引从1开始，polyscope从0开始
            elif line.startswith("l"):
                edge = []
                line_split = line.split()
                edge.append(int(line_split[1]))
                edge.append(int(line_split[2]))
                edges.append(edge)
                line = file.readline()
                continue
            else:
                line = file.readline()
    return np.array(nodes),np.array(edges)
        
def save_curves_obj(file_name, curves):
    '''
        file_name:保存的路径和文件名
        curves:骨架线数据 np.array()
    '''
    with open(file_name, 'w') as destination:
        # 写入信息
        destination.write('# whlib skeleton obj file\n')
        # 获取当前时间
        curr_time = datetime.datetime.now()
        destination.write('# ' + str(curr_time) + '\n')
        destination.write('o ' + str(curr_time) + '\n')
        
        #先写点
        point_sum = 0 # 前面的curves一共有几个点
        for curve in curves:
            #开始写入点
            for point in curve:
                destination.write('v '+ str(point[0]) + ' ' + str(point[1]) + ' ' + str(point[2]) + '\n')
        # 再写边
        for curve in curves:
            for i in range((point_sum + 1), (point_sum + len(curve))):
                destination.write('l ' + i + ' ' + (i+1) + '\n')
            point_sum = point_sum + curve.size

if __name__  == "__main__":
    point_cloud = load_point_cloud_obj("trunk_mve_scan_1.obj")
    print(point_cloud)

