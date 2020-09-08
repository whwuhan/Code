import os
# 罗列文件并且写入对应文件夹
def list_files(file_path):
    files = os.listdir(file_path)
    file_path = file_path + r'\file_list.txt'
    with open(file_path, 'w') as destination:
        for file in files:
            destination.write(file + '\n')
    return files



if __name__ == "__main__":
    files = list_files(r'G:\研究生\研究生入学前\View_skel\L1')
    print(files)
    


