import os
if __name__ == "__main__":
    #获取obj点云文件
    path = "../ExperimentData/normalization/"
    file_list = os.listdir(path+"pcd")
    pcd_file_list = []
    for file in file_list:
        if file != ".DS_Store":
            if file.split(".")[-2][-1] == "1":
                pcd_file_list.append(file)

    for file in pcd_file_list:
        command = "pcl_pcd2ply -format 0 -use_camera 0 "+\
            path+"pcd/"+file+" "+path+"ply/"+file.split(".")[0]+".1.ply"
        os.system(command)