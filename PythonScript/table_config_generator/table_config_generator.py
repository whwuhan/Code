# table_config代码生成器
import re
import json

# 解析sql文件
def resolve_sql(sql_file_path):
    # 模式串
    # 表字段模式串
    field_pattern = r"[\s]*`([a-zA-Z]+)` .* '([a-zA-Z0-9_\u4e00-\u9fa5\（\）]*)'.*"
    # 英文表名模式串
    table_name_pattern = r"CREATE TABLE `([a-zA-Z]*)` \("
    # 中文表名模式串
    table_name_pattern_cn = r"\) .* COMMENT='([a-zA-Z0-9_\u4e00-\u9fa5\s\（\）]*)'.*"
    # 编译模式串
    field_pattern_compiled = re.compile(field_pattern, re.I)
    table_name_pattern_compiled = re.compile(table_name_pattern, re.I)
    table_name_pattern_cn_compiled = re.compile(table_name_pattern_cn, re.I)
    with open(sql_file_path) as sql_file:
        line = sql_file.readline()
        table_names = []# 表名
        table_names_cn = []# 表名 中文
        fields = {} # 字段 
        fields_res = [] # 最终返回的表的字段
        
        table_names_res =[] # 最终返回的表的名称
        while line:
            if table_name_pattern_compiled.match(line) != None :
                flag = 0
                line = table_name_pattern_compiled.match(line)
                line_split = line.group(0).split()
                table_names.append(line_split[2].split("`")[1])
                line = sql_file.readline()
                #print(line_split)
                continue
            elif field_pattern_compiled.match(line) != None :
                line = field_pattern_compiled.match(line)
                line_split = line.group(0).split()
                fields[line_split[0].split("`")[1]] = line_split[-1].split("'")[1]
                line = sql_file.readline()
                #print(line_split)
                continue
            elif table_name_pattern_cn_compiled.match(line) != None :
                line = table_name_pattern_cn_compiled.match(line)
                line_split = line.group(0).split()
                table_names_cn.append(line_split[-1].split("'")[-2])
                line = sql_file.readline()
                #print(line_split)
                fields_res.append(fields)
                fields = {}
                continue
            line = sql_file.readline()
        # print(len(res))
        # print(len(table_names))
        # print(len(table_names_cn))
        # 分别返回每张表的字段，表名和对应的中文
        tables = {}
        for table_name,table_name_cn in zip(table_names,table_names_cn):
            tables[table_name] = table_name_cn
            table_names_res.append(tables)
            tables = {}
        return table_names_res,fields_res
    
# table_config_generator.json 生成器
def table_config_generator(tables, fields):
    res_list = []
    # 开始生成对应的json对象
    for table,field in zip(tables,fields):
        table_json = {}
        table_json["name"] = str(list(table.keys())[0]) + "Management"
        table_json["title"] = str(list(table.values())[0]) + "管理"
        table_json["tableName"] = str(list(table.keys())[0])
        table_json["queryTitle"] = str(list(field.values())[0]) + "名称"
        table_json["queryName"] = str(list(field.keys())[0])
        table_json["addFormTitle"] = str(list(table.values())[0])
        table_json["editFormTitle"] = "修改" + str(list(table.values())[0])
        table_json["titles"] = list(field.values())
        table_json["keys"] = list(field.keys())
        form = {}
        form["name"] = str(list(table.keys())[0])
        form["props"] = list(field.keys())
        form["labels"] = list(field.values())
        table_json["form"] = form
        res_list.append(table_json)
        # table_json = json.dumps(table_json)
        # print(table_json)
    with open('./result/result.json', 'w',encoding='utf-8') as res:
        json.dump(res_list, res,ensure_ascii=False,indent = 4)



if __name__ == "__main__":
    tables,fields = resolve_sql("parkingv2_dev.sql")
    # print((tables))
    # print("---------------")
    # print((fields))
    table_config_generator(tables,fields)

