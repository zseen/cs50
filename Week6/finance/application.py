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


def getTotalSharesValue(stocks):
    totalSharesValue = 0
    for stock in stocks:
        symbol = stock["symbol"]
        shares = stock["shares"]
        quote = lookup(symbol)
        sharesValue = shares * quote["price"]
        totalSharesValue += sharesValue
        transactionsPriceTotalUpdateQuery = "UPDATE transactions SET price=:price,total=:total WHERE id=:id AND symbol=:symbol"
        db.execute(transactionsPriceTotalUpdateQuery,
                   price=usd(quote["price"]),
                   total=usd(sharesValue),
                   id=session["user_id"],
                   symbol=symbol)
    return totalSharesValue


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    sharesSymbolSelectionQuery = "SELECT shares, symbol FROM transactions WHERE id=:id"
    stocks = db.execute(sharesSymbolSelectionQuery,
                        id=session["user_id"])
    totalSharesValue = getTotalSharesValue(stocks)

    wholeUsersSelectionQuery = "SELECT name, symbol, shares, price, total FROM transactions WHERE id=:id"
    updatedTransactions = db.execute(wholeUsersSelectionQuery,
                                     id=session["user_id"])

    usersCashSelectionQuery = "SELECT cash FROM users WHERE id=:id"
    moneyAvailable = db.execute(usersCashSelectionQuery,
                                id=session["user_id"])
    cash = moneyAvailable[0]["cash"]
    grandTotal = cash + totalSharesValue

    return render_template("index.html", stocks=updatedTransactions, cash=usd(cash), total=usd(totalSharesValue), grandTotal=usd(grandTotal))


def handleBuyingProcess(stock, numSharesToBuy, totalPurchasePrice):
    usersCashUpdateQuery = "UPDATE users SET cash = cash - :purchase WHERE id = :id"
    db.execute(usersCashUpdateQuery,
               id=session["user_id"],
               purchase=totalPurchasePrice)

    transactionsSharesSelectionQuery = "SELECT shares FROM transactions WHERE id = :id AND symbol=:symbol"
    acquiredShares = db.execute(transactionsSharesSelectionQuery,
                                id=session["user_id"],
                                symbol=stock["symbol"])

    if not acquiredShares:
        wholeTransactionsInsertionQuery = "INSERT INTO transactions (name, shares, price, total, symbol, date, id)" \
                                          "VALUES(:name, :shares, :price, :total, :symbol, datetime('now'), :id)"
        db.execute(wholeTransactionsInsertionQuery,
                   name=stock["name"],
                   shares=numSharesToBuy,
                   price=usd(stock["price"]),
                   total=usd(totalPurchasePrice),
                   symbol=stock["symbol"],
                   id=session["user_id"])
    else:
        sharesTotalNum = acquiredShares[0]["shares"] + int(numSharesToBuy)
        transactionsSharesUpdateQuery = "UPDATE transactions SET shares=:shares, total=:total WHERE id=:id AND symbol=:symbol"
        db.execute(transactionsSharesUpdateQuery,
                   shares=sharesTotalNum,
                   total=usd(sharesTotalNum * (stock["price"])),
                   id=session["user_id"],
                   symbol=stock["symbol"])



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("must provide symbol", 400)

        numSharesToBuy = request.form.get("shares")
        if (not numSharesToBuy) or (not numSharesToBuy.isdigit()) or int(numSharesToBuy) <= 0:
            return apology("invalid number", 400)

        usersCashSelectionQuery = "SELECT cash FROM users WHERE id=:id"
        money = db.execute(usersCashSelectionQuery,
                           id=session["user_id"])

        cashAvailable = float(money[0]["cash"])
        totalPurchasePrice = stock["price"] * int(numSharesToBuy)
        if cashAvailable < totalPurchasePrice:
            return apology("not enough money to purchase", 400)

        handleBuyingProcess(stock, numSharesToBuy, totalPurchasePrice)

        action = "bought"
        historyWholeInsertionQuery = "INSERT INTO history (name, shares, price, total, symbol, date, action, id)" \
                                     "VALUES(:name, :shares, :price, :total, :symbol, datetime('now'), :action, :id)"

        db.execute(historyWholeInsertionQuery,
                   name=stock["name"],
                   shares=numSharesToBuy,
                   price=usd(stock["price"]),
                   total=usd(totalPurchasePrice),
                   symbol=stock["symbol"],
                   action=action,
                   id=session["user_id"],)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide a username", 400)
        elif not request.form.get("password"):
            return apology("must provide a password", 400)
        elif not request.form.get("confirmation"):
            return apology("must confirm your password", 400)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password mismatch", 400)

        hashedPW = generate_password_hash(request.form.get("password"))
        newRegisteredUser = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                                        username=request.form.get("username"),
                                        hash=hashedPW)
        if not newRegisteredUser:
            return apology("username already taken", 400)

        session["user_id"] = newRegisteredUser
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        stock = request.form.get("symbol")
        if not stock:
            return apology("Please choose a valid symbol", 400)

        numSharesToSell = request.form.get("shares")
        if (not numSharesToSell) or (not numSharesToSell.isdigit()) or (int(numSharesToSell) <= 0):
            return apology("Invalid transaction", 400)

        transactionsSharesSelectionQuery = "SELECT shares FROM transactions WHERE id = :id AND symbol= :symbol"

        acquiredShares = db.execute(transactionsSharesSelectionQuery,
                                    id=session["user_id"],
                                    symbol=stock)
        acquiredSharesNum = acquiredShares[0]["shares"]

        if int(numSharesToSell) > acquiredSharesNum:
            return apology("not enough shares", 400)

        quote = lookup(stock)
        totalSellPrice = int(numSharesToSell) * quote["price"]

        handleSellingProcess(acquiredSharesNum, numSharesToSell, stock, totalSellPrice)
        return redirect("/")

    else:
        transactionsSharesSymbolSelectionQuery = "SELECT shares, symbol FROM transactions WHERE id = :id"
        acquiredShares = db.execute(transactionsSharesSymbolSelectionQuery,
                                    id=session["user_id"])
        return render_template("sell.html", stocks=acquiredShares)


def handleSellingProcess(acquiredSharesNum, numSharesToSell, stock, totalSellPrice):
    if acquiredSharesNum - int(numSharesToSell) > 0:
        transactionsSharesTotalUpdateQuery = "UPDATE transactions SET shares=shares - :numSold, total=total + :totalSellPrice" \
                                             " WHERE id=:id AND symbol=:symbol"
        db.execute(transactionsSharesTotalUpdateQuery,
                   numSold=int(numSharesToSell),
                   totalSellPrice=usd(totalSellPrice),
                   id=session["user_id"],
                   symbol=stock)
    else:
        transactionsTotalUpdateQuery = "UPDATE transactions SET total=total + :totalSellPrice WHERE id=:id AND symbol=:symbol"
        db.execute(transactionsTotalUpdateQuery,
                   totalSellPrice=usd(totalSellPrice),
                   id=session["user_id"],
                   symbol=stock)

        transactionsStockDeletionQuery = "DELETE FROM transactions WHERE id=:id AND symbol=:symbol"
        db.execute(transactionsStockDeletionQuery,
                   id=session["user_id"],
                   symbol=stock)

    usersCashUpdateQuery = "UPDATE users SET cash = cash + :moneyGained WHERE id = :id"
    db.execute(usersCashUpdateQuery,
               id=session["user_id"],
               moneyGained=totalSellPrice)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
