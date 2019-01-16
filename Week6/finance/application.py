import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash


from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

MIN_PW_LENGTH = 8

TRANSACTIONS_PRICE_TOTAL_UPDATE_QUERY = "UPDATE transactions SET price=:price, total=:total WHERE id=:id AND symbol=:symbol"
TRANSACTIONS_ALL_SELECTION_QUERY = "SELECT name, symbol, shares, price, total FROM transactions WHERE id=:id"
TRANSACTIONS_SHARES_SELECTION_WITH_SYMBOL_QUERY = "SELECT shares FROM transactions WHERE id = :id AND symbol=:symbol"
TRANSACTIONS_INSERTION_QUERY = "INSERT INTO transactions (name, shares, price, total, symbol, date, id)" \
                                     "VALUES(:name, :shares, :price, :total, :symbol, datetime('now'), :id)"
TRANSACTIONS_SHARES_TOTAL_UPDATE_WITH_SYMBOL_QUERY = "UPDATE transactions SET shares=:shares, total=:total WHERE id=:id AND symbol=:symbol"
TRANSACTIONS_SHARES_SYMBOL_SELECTION_QUERY = "SELECT shares, symbol FROM transactions WHERE id = :id"
TRANSACTIONS_SHARE_TOTAL_UPDATE_SELLING_QUERY = "UPDATE transactions SET shares=shares - :numSold, total=total + :totalSellPrice " \
                                                "WHERE id=:id AND symbol=:symbol"
TRANSACTIONS_DELETION_QUERY = "DELETE FROM transactions WHERE id=:id AND symbol=:symbol"

USERS_CASH_UPDATE_QUERY = "UPDATE users SET cash = cash - :purchase WHERE id = :id"
USERS_CASH_SELECTION_QUERY = "SELECT cash FROM users WHERE id=:id"
USERS_USERNAME_PW_INSERTION_QUERY = "INSERT INTO users (username, hash) VALUES(:username, :hash)"
USERS_CASH_UPDATE_GAINED_QUERY = "UPDATE users SET cash = cash + :moneyGained WHERE id = :id"
USERS_HASH_SELECTION_QUERY = "SELECT hash FROM users WHERE id=:id"
USERS_HASH_UPDATE_QUERY = "UPDATE users SET hash=:hashedNewPW WHERE id=:id"

HISTORY_INSERTION_QUERY = "INSERT INTO history (name, shares, price, total, symbol, date, action, id)" \
                                "VALUES(:name, :shares, :price, :total, :symbol, datetime('now'), :action, :id)"
HISTORY_ALL_SELECT_ORDERED_BY_DATE_QUERY = "SELECT name, symbol, shares, price, total, date, action FROM history WHERE id=:id ORDER BY date DESC"


@app.route("/")
@app.route("/displayStocksAndBalance")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute(TRANSACTIONS_SHARES_SYMBOL_SELECTION_QUERY,
                        id=session["user_id"])
    totalSharesValue = getTotalSharesValue(stocks)

    updatedTransactions = db.execute(TRANSACTIONS_ALL_SELECTION_QUERY,
                                     id=session["user_id"])
    moneyAvailable = db.execute(USERS_CASH_SELECTION_QUERY,
                                id=session["user_id"])
    cash = moneyAvailable[0]["cash"]
    grandTotal = cash + totalSharesValue

    return render_template("index.html", stocks=updatedTransactions, cash=usd(cash), total=usd(totalSharesValue), grandTotal=usd(grandTotal))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method != "POST":
        return render_template("buy.html")

    stock = lookup(request.form.get("symbol"))
    if not stock:
        return apology("must provide symbol", 400)

    numSharesToBuy = request.form.get("shares")
    if (not numSharesToBuy) or (not numSharesToBuy.isdigit()) or int(numSharesToBuy) <= 0:
        return apology("invalid number", 400)

    money = db.execute(USERS_CASH_SELECTION_QUERY,
                       id=session["user_id"])

    cashAvailable = float(money[0]["cash"])
    totalPurchasePrice = stock["price"] * int(numSharesToBuy)
    if cashAvailable < totalPurchasePrice:
        return apology("not enough money to purchase", 400)

    handleBuyingProcess(stock, numSharesToBuy, totalPurchasePrice)

    db.execute(HISTORY_INSERTION_QUERY,
               name=stock["name"],
               shares=numSharesToBuy,
               price=usd(stock["price"]),
               total=usd(totalPurchasePrice),
               symbol=stock["symbol"],
               action="bought",
               id=session["user_id"])

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute(HISTORY_ALL_SELECT_ORDERED_BY_DATE_QUERY,
                      id=session["user_id"])

    return render_template("history.html", stocks=rows)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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
    """Get stock quote."""
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        if stock is None:
            return apology("invalid symbol", 400)
        return render_template("quoted.html", stock=stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()
    if request.method != "POST":
        return render_template("register.html")

    if not request.form.get("username"):
        return apology("must provide a username", 400)
    elif not request.form.get("password"):
        return apology("must provide a password", 400)

    password = request.form.get("password")
    # min 8 chars pw length, at least 1 upper char, at least 1 lower char, no spec chars, at least 1 digit
    if not checkPasswordValid(password, MIN_PW_LENGTH):
        return apology("Your password does not meet the requirements", 400)
    elif not request.form.get("confirmation"):
        return apology("must confirm your password", 400)
    elif request.form.get("password") != request.form.get("confirmation"):
        return apology("password mismatch", 400)

    hashedPW = generate_password_hash(request.form.get("password"))
    newRegisteredUser = db.execute(USERS_USERNAME_PW_INSERTION_QUERY,
                                    username=request.form.get("username"),
                                    hash=hashedPW)
    if not newRegisteredUser:
        return apology("username already taken", 400)

    session["user_id"] = newRegisteredUser
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method != "POST":
        acquiredShares = db.execute(TRANSACTIONS_SHARES_SYMBOL_SELECTION_QUERY,
                                    id=session["user_id"])
        return render_template("sell.html", stocks=acquiredShares)

    stockSymbol = request.form.get("symbol")
    if not stockSymbol:
        return apology("Please choose a valid symbol", 400)

    numSharesToSell = request.form.get("shares")
    if (not numSharesToSell) or (not numSharesToSell.isdigit()) or (int(numSharesToSell) <= 0):
        return apology("Invalid transaction", 400)

    acquiredShares = db.execute(TRANSACTIONS_SHARES_SELECTION_WITH_SYMBOL_QUERY,
                                id=session["user_id"],
                                symbol=stockSymbol)
    acquiredSharesNum = acquiredShares[0]["shares"]

    if int(numSharesToSell) > acquiredSharesNum:
        return apology("not enough shares", 400)

    quote = lookup(stockSymbol)
    totalSellPrice = int(numSharesToSell) * quote["price"]

    handleSellingProcess(acquiredSharesNum, numSharesToSell, stockSymbol, totalSellPrice)

    db.execute(HISTORY_INSERTION_QUERY,
               name=quote["name"],
               shares=numSharesToSell,
               price=usd(quote["price"]),
               total=usd(totalSellPrice),
               symbol=stockSymbol,
               action="sold",
               id=session["user_id"])

    return redirect("/")


@app.route("/changePW", methods=["GET", "POST"])
@login_required
def changePW():
    if request.method != "POST":
        return render_template("passwordchange.html")

    presumedOldPassword = request.form.get("old_password")
    if not presumedOldPassword:
        return apology("Missing old password", 400)

    newPassword = request.form.get("new_password")
    if not newPassword:
        return apology("Missing new password", 400)

    if not checkPasswordValid(newPassword, MIN_PW_LENGTH):
        return apology("You password does not meet the requirements", 400)

    hashedOldPWRow = db.execute(USERS_HASH_SELECTION_QUERY,
                                id=session["user_id"])
    hashedOldPW = hashedOldPWRow[0]["hash"]

    isPresumedCorrect = check_password_hash(hashedOldPW, presumedOldPassword)
    if not isPresumedCorrect:
        return apology("Incorrect old password", 400)

    hashedNewPassword = generate_password_hash(newPassword)
    db.execute(USERS_HASH_UPDATE_QUERY,
               hashedNewPW=hashedNewPassword,
               id=session["user_id"])

    return render_template("pwChangeSuccesful.html")


@app.route("/addMoreCash", methods=["GET", "POST"])
@login_required
def addMoreCash():
    if request.method != "POST":
        return render_template("addMoreCash.html")

    cashToAdd = float(request.form.get("cash_to_add"))
    if not cashToAdd:
        return apology("Amount field left blank")

    db.execute(USERS_CASH_UPDATE_GAINED_QUERY,
               moneyGained=cashToAdd,
               id=session["user_id"])
    return redirect("/")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


def getTotalSharesValue(stocks):
    totalSharesValue = 0
    for stock in stocks:
        symbol = stock["symbol"]
        shares = stock["shares"]
        quote = lookup(symbol)
        sharesValue = shares * quote["price"]
        totalSharesValue += sharesValue
        db.execute(TRANSACTIONS_PRICE_TOTAL_UPDATE_QUERY,
                   price=usd(quote["price"]),
                   total=usd(sharesValue),
                   id=session["user_id"],
                   symbol=symbol)
    return totalSharesValue


def handleBuyingProcess(stock, numSharesToBuy, totalPurchasePrice):
    db.execute(USERS_CASH_UPDATE_QUERY,
               id=session["user_id"],
               purchase=totalPurchasePrice)

    acquiredShares = db.execute(TRANSACTIONS_SHARES_SELECTION_WITH_SYMBOL_QUERY,
                                id=session["user_id"],
                                symbol=stock["symbol"])

    if not acquiredShares:
        db.execute(TRANSACTIONS_INSERTION_QUERY,
                   name=stock["name"],
                   shares=numSharesToBuy,
                   price=usd(stock["price"]),
                   total=usd(totalPurchasePrice),
                   symbol=stock["symbol"],
                   id=session["user_id"])
    else:
        sharesTotalNum = acquiredShares[0]["shares"] + int(numSharesToBuy)
        db.execute(TRANSACTIONS_SHARES_TOTAL_UPDATE_WITH_SYMBOL_QUERY,
                   shares=sharesTotalNum,
                   total=usd(sharesTotalNum * (stock["price"])),
                   id=session["user_id"],
                   symbol=stock["symbol"])


def handleSellingProcess(acquiredSharesNum, numSharesToSell, stock, totalSellPrice):
    if acquiredSharesNum - int(numSharesToSell) > 0:
        db.execute(TRANSACTIONS_SHARE_TOTAL_UPDATE_SELLING_QUERY,
                   numSold=int(numSharesToSell),
                   totalSellPrice=usd(totalSellPrice),
                   id=session["user_id"],
                   symbol=stock)
    else:
        db.execute(TRANSACTIONS_DELETION_QUERY,
                   id=session["user_id"],
                   symbol=stock)

    db.execute(USERS_CASH_UPDATE_GAINED_QUERY,
               id=session["user_id"],
               moneyGained=totalSellPrice)


def checkPasswordValid(password, minLength):
    if len(password) < minLength:
        return False

    lowerCounter = 0
    upperCounter = 0
    digitCounter = 0

    for char in password:
        if char.isdigit():
            digitCounter += 1
        elif char.islower():
                lowerCounter += 1
        elif char.isupper():
                upperCounter += 1
        else:
            return False

    return digitCounter >= 1 and lowerCounter >=1 and upperCounter >= 1
