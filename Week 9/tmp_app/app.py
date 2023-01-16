from flask import Flask, render_template, request


app = Flask(__name__)

@app.route("/")

def index():
    name = request.args.get("name", "world") # .get verify if "name" exists in args, if it doesnt, return the second argument

    return render_template("index.html", name = name)




