import os
'''
    调用PCL库栅格化采样
'''

if __name__ == "__main__":
    #获取pcd点云文件
    path = "../ExperimentData/normalization/"
    file_list = os.listdir(path+"pcd")
    pcd_file_list = []
    for file in file_list:
        if file.split(".")[-1] == "pcd":
            pcd_file_list.append(file)
    # print(pcd_file_list)
    
    for pcd_file in pcd_file_list:
        command = r"pcl_voxel_grid -leaf 0.1,0.1,0.1 "+ path+\
            "pcd/"+pcd_file +" "+ path+"pcd/"+pcd_file.split(".")[0] +"_down_sampled_0.1.pcd"
        os.system(command)