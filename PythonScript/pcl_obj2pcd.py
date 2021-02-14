import os
if __name__ == "__main__":
    #获取obj点云文件
    path = "../ExperimentData/normalization/"
    file_list = os.listdir(path+"obj")
    obj_file_list = []
    for file in file_list:
        if file.split(".")[-1] == "obj":
            obj_file_list.append(file)
    print(obj_file_list)
    for file in obj_file_list:
        command = "pcl_obj2pcd -format 0 -use_camera 0 "+\
            path+"obj/"+file+" "+path+"pcd/"+file.split(".")[0]+".pcd"
        os.system(command)
