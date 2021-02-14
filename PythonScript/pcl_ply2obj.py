import os
if __name__ == "__main__":
    #获取ply点云文件
    path = "../ExperimentData/normalization/"
    file_list = os.listdir(path+"ply")
    ply_file_list = []
    for file in file_list:
        if file.split(".")[-1] == "ply":
            ply_file_list.append(file)


    for file in ply_file_list:
        command = "pcl_ply2obj "+\
            path+"ply/"+file+" "+path+"down_sampled/"+file.split(".")[0]+".1.obj"
        os.system(command)