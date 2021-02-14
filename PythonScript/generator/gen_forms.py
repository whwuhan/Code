import json
from jinja2 import Environment, FileSystemLoader


with open('./templates/form_config.json')as fp:
    forms = json.load(fp)
    for form in forms:
        env = Environment(loader=FileSystemLoader('./templates'))
        template = env.get_template('form.jinja2')
        content = template.render(props=form["props"],labels=form["labels"],submitURL=form["submitURL"])
        with open('./generated/'+form['name']+'Form.vue','w') as fout:
            fout.write(content)