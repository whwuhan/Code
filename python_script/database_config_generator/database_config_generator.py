import re
from googletrans import Translator # 需要翻墙使用
# 用于解析网页表格数据
# 生成指定格式文件的脚本

# 将分割的字符串数组拼接成小驼峰
def get_format_data(data_source):
    for i in range(len(data_source)):
        if i == 0:
            data_source[i] = data_source[i].lower()
        else:
            data_source[i] = data_source[i].capitalize()
    return ''.join(data_source)

# 解析网页表格信息
def table_info_resolve(data_path = "data.txt"):
    # 表名模式串
    table_pattern = r'.*<ul class="breadcrumb">'              
    table_pattern_compiled = re.compile(table_pattern, re.I)
    table_name = ""

    # 表字段模式串
    table_fields_pattern = r'.*<th.*>.*'
    table_fields_pattern_compiled = re.compile(table_fields_pattern, re.I)
    table_fields = []
    
    with open(data_path) as data:
        line = data.readline()
        while line:
            #print(line)
            if table_pattern_compiled.match(line) != None:
                line = data.readline()
                line = line.strip()
                while len(line) == 0:
                    line = data.readline()
                    line = line.strip()
                line_split = line.split("<")
                line_split = line_split[1].split(">")
                # print(line_split)
                table_name = line_split[1]
            elif table_fields_pattern_compiled.match(line) != None:
                line = line.strip()
                line_split = line.split("<")
                line_split = line_split[1].split(">")
                table_fields.append(line_split[1])
                # print(line_split)
            line = data.readline()
        #print(table_name)
        #print(table_fields)
    table_fields_en = [] # 字段英文名称
    # google 翻译
    translator = Translator()
    # 翻译表名
    table_name_en = translator.translate(table_name).text.lower()
    table_name_en_split = table_name_en.split()
    # 表名格式化
    table_name_en = get_format_data(table_name_en_split)
    #print("table_name_en:"+table_name_en)
    for table_field in table_fields:
        trans_res = translator.translate(table_field)
        trans_res_split = trans_res.text.split()
        # 字段格式化
        concat = get_format_data(trans_res_split)
        table_fields_en.append(concat)
    #print(table_fields_en)
    return table_name,table_name_en,table_fields,table_fields_en

def generate_sql(\
    table_name, \
    table_name_en,\
    table_fields,\
    table_fields_en,\
    des_path = "sql.txt"):
    '''
    table_name :        表中文名
    table_name_en :     表英文名
    table_fields :      表字段中文名
    table_fields_en :   表字段英文名
    des_path :          存放文件位置
    '''
    with open(des_path, 'a') as sql_file:
        sql_file.write(table_name_en + ' ' + table_name + ' ' + str(len(table_fields)) + '\n')
        for table_field,table_field_en in zip(table_fields,table_fields_en):
            sql_file.write(table_field + ' ' + table_field_en + '\n')




if __name__ == "__main__":
    table_name,table_name_en,table_fields,table_fields_en = table_info_resolve()
    table_fields = [i for i in table_fields if len(i)>0]
    table_fields_en = [i for i in table_fields_en if len(i)>0]
    print("table_fields  :  " + str(table_fields))
    print("table_fields_en  :  " + str(table_fields_en))
    generate_sql(table_name,table_name_en,table_fields,table_fields_en)


