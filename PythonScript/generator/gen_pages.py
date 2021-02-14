import json
from jinja2 import Environment, FileSystemLoader


with open('./templates/config.json')as fp:
    pages = json.load(fp)
    for page in pages:
        env = Environment(loader=FileSystemLoader('./templates'))
        template = env.get_template('page.jinja2')
        content = template.render(query=page["query"],title=page["title"],buttons=page["buttons"],columns=page["columns"],data=page["data"]
        )
        print('./generated/'+page['component'])
        with open('./generated/'+page['component'],'w') as fout:
            fout.write(content)