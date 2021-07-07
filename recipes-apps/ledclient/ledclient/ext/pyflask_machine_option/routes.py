import os
import glob
from main import app

from flask import Flask, render_template, send_from_directory, request, redirect, url_for, Response, json
from global_def import *
import traceback
from flask_wtf import Form
from wtforms import validators, RadioField, SubmitField, IntegerField
import jlog
log = jlog.logging_init("flask_plugin")
import os
SECRET_KEY = os.urandom(32)
app.config['SECRET_KEY'] = SECRET_KEY
config_file = open(config_file_uri, 'r')

if "Server" in config_file.read():
    LED_Role = "Server"
else:
    LED_Role = "Client"
log.debug("LED_Role : ", LED_Role)
config_file.close()


class TestForm(Form):

    style = {'class': 'ourClasses', 'style': 'font-size:32px;'}
    role_switcher = RadioField(
        'Led Role',
        [validators.Required()],
        choices=[('Server', 'Server'), ('Client', 'Client')],
        default=LED_Role,
        render_kw=style
    )
    submit = SubmitField('Set', render_kw=style)



@app.route("/")
def index():
    testform = TestForm()
    return render_template("index.html", form=testform)

@app.route('/select_role',methods=['POST','GET'])
def select_role():
    try:
        global LED_Role
        log.debug(request.form)
        option = request.form['role_switcher']
        log.debug(option)
        config_file = open(config_file_uri, "w")
        config_file.write(option)
        config_file.close()
        if "Server" in option:
            LED_Role = "Server"
        else:
            LED_Role = "Client"
        testform = TestForm()
    except Exception as e:
        log.error(e)
    finally:
        log.info("good")
    return render_template("index.html", form=testform)
    #return redirect(url_for('index'))
