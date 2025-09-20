import yfinance as yf

ticker = "AAPL"

data = yf.download(ticker, period = "5y")

data.to_csv("./data/AAPL.csv")

print("Saved " + ticker + ".csv with"+ len(data) + " row")