import os
import sys
'''
    罗列目录文件
    使用方法
    python3 list_files.py [file_path]
'''

# 罗列文件并且写入对应文件夹
def list_files(file_path):
    files = os.listdir(file_path)
    file_path = file_path + r'/file_list.txt'
    with open(file_path, 'w') as destination:
        for file in files:
            if file != ".DS_Store":
                destination.write(file + '\n')
    return files


if __name__ == "__main__":
    if len(sys.argv) == 1:
        print("没有输入文件路径")
        hint = "使用方法：\npython3 list_files.py [file_path]"
        print(hint)
        sys.exit(0)
    else:
        files = list_files(sys.argv[1])
        print("目录文件为：",files)
    


