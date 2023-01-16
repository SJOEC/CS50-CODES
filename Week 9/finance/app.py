import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, have_number

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Custome iteration
app.jinja_env.filters['zip'] = zip

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():

    # delete 0 shares stocks
    db.execute("DELETE FROM stock WHERE stock_shares = 0 AND person_id = ?", session['user_id'])

    # get dato to create table

    users_stock_data = []
    users_total = []

    users_stock = db.execute("SELECT * FROM stock WHERE person_id = ?", session["user_id"])

    for i in range(len(users_stock)):
        users_stock_data.append(lookup(users_stock[i]['stock_symbol']))

    for i, j in zip(users_stock, users_stock_data):
        users_total.append(i['stock_shares'] * j['price'])

    users_cash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])
    users_cash = users_cash[0]['cash']

    grand_total = sum(users_total) + users_cash

    return render_template("index.html", foo=users_stock, bar=users_stock_data, baz=users_total, qux=grand_total, quux=users_cash, zip=zip)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # check users input
        try:
            if isinstance((int(request.form.get("shares"))), int) == False:
                return apology("Invalid amount", 400)
        except ValueError:
            return apology("Invalid amount", 400)

        if int(request.form.get("shares")) <= 0:
            return apology("Invalid amount", 400)

        if lookup(request.form.get("symbol")) == None:
            return apology("Symbol noy found", 400)

        # check if the symbols is already in the db

        buy_symbol = request.form.get("symbol")
        buy_symbol = buy_symbol.upper()

        current_stock = db.execute("SELECT * FROM stock WHERE stock_symbol = ? AND person_id = ?", buy_symbol, session["user_id"])

        # if the symbol isn't in the db, add it and set value
        if len(current_stock) == 0:
            db.execute("INSERT INTO stock(person_id,stock_symbol, stock_shares) VALUES (?,?,?)", session["user_id"], buy_symbol, 0)

        # if already in the db, just add the new shares
        stock_data = lookup(request.form.get("symbol"))
        buy_amount = request.form.get("shares")
        buy_price = stock_data['price']

        # check users cash
        users_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        users_cash = users_cash[0]['cash']

        # check if the user has enough cash
        buy_cash = float(buy_price) * float(buy_amount)

        actual_cash = users_cash - buy_cash

        if actual_cash < 0:
            return apology("Not enough cash")

        # update users cash
        db.execute("UPDATE users SET cash=? WHERE id=?", actual_cash, session["user_id"])

        # update user's stock
        tmp_shares = db.execute("SELECT stock_shares FROM stock WHERE stock_symbol = ? AND person_id = ?",
                                buy_symbol, session["user_id"])

        tmp_shares = tmp_shares[0]['stock_shares']

        tmp_shares += int(request.form.get("shares"))

        db.execute("UPDATE stock SET stock_shares=? WHERE stock_symbol=? AND person_id = ?",
                   tmp_shares, buy_symbol, session["user_id"])

        # update history
        db.execute("INSERT INTO history(record_user_id, record_symbol, record_shares,record_price,transacted) VALUES (?,?,?,?,?)",
                   session["user_id"], buy_symbol, request.form.get("shares"), buy_price, datetime.now())

        return redirect("/")

    elif request.method == "GET":
        return render_template("buy.html")


@app.route("/history", methods=["GET"])
@login_required
def history():
    """Show history of transactions"""

    history_data = db.execute("SELECT * FROM history")

    return render_template("history.html", foo=history_data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":

        symbol = request.form.get("symbol")  # save users input "symbol"

        if lookup(symbol) == None:
            return apology("Symbol not found", 400)  # error mesage if symbol doesnt found

        else:
            stock_data = lookup(symbol)
            return render_template("quoted.html", stock_data=stock_data)  # return the search in a new html page with the result

    elif request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":  # if the user submit the forum, create the user

        symbols = [";", ".", ",", "+", "*", "&", "!", ":", "-", "?", "¡", "|"]
        usersnames = []
        password_check = False

        # locate the users in a tmp variable
        users = db.execute("SELECT username FROM users")
        users = users[0]['username']

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # check if username is already taken

        users = db.execute("SELECT username FROM users")

        for i in range(len(users)):
            usersnames.append(users[i]['username'])

        if request.form.get("username") in usersnames:
            return apology("Username already taken", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        if not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        # check password requirements
        if len(request.form.get("password")) < 8:
            return apology("password does not have enough characters", 400)

        for i in range(len(symbols)):
            if symbols[i] in request.form.get("password"):
                password_check = True
                break

        if have_number(request.form.get("password")) == False:
            return apology("password need a number", 400)

        # check both passwords
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password do not match", 400)

        if password_check == False:
            return apology("password need special character", 400)

        # register user
        db.execute("INSERT INTO users (username, hash) VALUES (?,?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    elif request.method == "GET":  # If the use isn't register yet, render register page
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    users_stock_data = db.execute("SELECT stock_symbol FROM stock WHERE person_id = ?", session['user_id'])

    if request.method == "POST":

        # check users input
        if not request.form.get("symbol"):
            return apology("Need sell symbol", 400)

        if not request.form.get("shares"):
            return apology("Need shares amount", 400)

        if int(request.form.get("shares")) <= 0:
            return apology("Invalid amount", 400)

        # get users data
        sell_symbol = request.form.get("symbol")

        stock_data = lookup(request.form.get("symbol"))
        sell_amount = request.form.get("shares")
        sell_price = stock_data['price']
        sell_shares = int(request.form.get("shares"))

        # check  user's stock
        tmp_shares = db.execute("SELECT stock_shares FROM stock WHERE stock_symbol = ? AND person_id = ?",
                                sell_symbol, session["user_id"])

        tmp_shares = tmp_shares[0]['stock_shares']

        tmp_shares -= sell_shares

        if tmp_shares < 0:
            return apology("Not enough shares")

        # update users cash
        users_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        users_cash = users_cash[0]['cash']

        sell_cash = float(sell_price) * float(sell_amount)

        actual_cash = users_cash + sell_cash

        # update users cash
        db.execute("UPDATE users SET cash=? WHERE id=?", actual_cash, session["user_id"])

        db.execute("UPDATE stock SET stock_shares=? WHERE stock_symbol=? AND person_id = ?",
                   tmp_shares, sell_symbol, session["user_id"])

        # update history
        db.execute("INSERT INTO history(record_user_id, record_symbol, record_shares,record_price,transacted) VALUES (?,?,?,?,?)", session["user_id"], sell_symbol,
                   (sell_shares - (sell_shares * 2)), sell_price, datetime.now())

        return redirect("/")

    elif request.method == "GET":

        return render_template("sell.html", foo=users_stock_data)
