#include "trader.hh"

using namespace std;

Trader::Trader(const char* _status)
{
    status = string(_status);
    profit = 0;
    investment = 0;
}

Trader::Trader(const char* _status, const char* _transaction)
{
    status = string(_status);
    transaction.push_back(string(_transaction));
    profit = 0;
    investment = 0;
}

Trader Trader::buy(int price)
{
    Trader trader = *this;
    
    trader.status = string("FULL");
    trader.transaction.push_back(string("buy"));
    trader.investment = price;

    return trader;
}

Trader Trader::sell(int price)
{
    Trader trader = *this;

    trader.status = string("COOL");
    trader.transaction.push_back(string("sell"));
    trader.profit += price - trader.investment;
    trader.investment = 0;

    return trader;
}

Trader Trader::cool()
{
    Trader trader = *this;

    trader.status = string("EMPTY");
    trader.transaction.push_back(string("cooldown"));

    return trader;
}

Trader Trader::pass()
{
    Trader trader = *this;

    trader.transaction.push_back(string("pass"));

    return trader;
}

vector<Trader> Trader::evolution(int price)
{
    vector<Trader> traders;

    if (string("EMPTY") == status) {
        traders.push_back(buy(price));
        traders.push_back(pass());
    } else if (string("FULL") == status) {
        traders.push_back(sell(price));
        traders.push_back(pass());
    } else if (string("COOL") == status) {
        traders.push_back(cool());
    }

    return traders;
}

bool Trader::operator==(const Trader &t) const
{
    return (this->status == t.status
            && this->transaction == t.transaction);
}

const string& Trader::get_status() const
{
    return status;
}

const vector<string>& Trader::get_transaction() const
{
    return transaction;
}

int Trader::get_profit() const
{
    return profit;
}
