import json
from jinja2 import Environment, FileSystemLoader


with open('./templates/table_config.json')as fp:
    tables = json.load(fp)
    for table in tables:
        env = Environment(loader=FileSystemLoader('./templates'))
        template = env.get_template('table.jinja2')
        content = template.render(name=table["name"],
                                title=table["title"],
                                tableName=table["tableName"],
                                queryName=table["queryName"],
                                queryTitle=table["queryTitle"],
                                addFormTitle=table["addFormTitle"],
                                editFormTitle=table["editFormTitle"],
                                titles=table["titles"],
                                keys=table["keys"],
                                form=table["form"])
        with open('./generated/'+table['name']+'.vue','w') as fout:
            fout.write(content)
        form=table["form"]
        template = env.get_template('form.jinja2')
        content = template.render(props=form["props"],labels=form["labels"])
        with open('./generated/'+form['name']+'Form.vue','w') as fout:
            fout.write(content)