#include "trader.hh"

using namespace std;

map<string, int> Trader::status_freedom {
    {"FULL", 2},
    {"EMPTY", 1},
    {"COOL", 0}
};

map<string, vector<Trader>(Trader::*)(int) const> Trader::status_opt {
    {"FULL", &Trader::opt_when_full},
    {"EMPTY", &Trader::opt_when_empty},
    {"COOL", &Trader::opt_when_cool}
};

Trader::Trader(const char* _status, int _cash)
{
    status = string(_status);
    investment = 0;
    cash = _cash;
}

Trader Trader::buy(int price) const
{
    Trader trader = *this;
    
    trader.status = string("FULL");
    trader.transaction.push_back(string("buy"));
    trader.investment = price;
    trader.cash -= trader.investment;

    return trader;
}

Trader Trader::sell(int price) const
{
    Trader trader = *this;

    trader.status = string("COOL");
    trader.transaction.push_back(string("sell"));
    trader.investment = 0;
    trader.cash += price;

    return trader;
}

Trader Trader::cool() const
{
    Trader trader = *this;

    trader.status = string("EMPTY");
    trader.transaction.push_back(string("cooldown"));

    return trader;
}

Trader Trader::pass() const
{
    Trader trader = *this;

    trader.transaction.push_back(string("pass"));

    return trader;
}

vector<Trader> Trader::opt_when_empty(int price) const {
    vector<Trader> traders;

    traders.push_back(buy(price));
    traders.push_back(pass());

    return traders;
}

vector<Trader> Trader::opt_when_full(int price) const {
    vector<Trader> traders;

    traders.push_back(sell(price));
    traders.push_back(pass());

    return traders;
}

vector<Trader> Trader::opt_when_cool(int price) const {
    vector<Trader> traders;

    traders.push_back(cool());

    return traders;
}

vector<Trader> Trader::evolution(int price) const
{
    return (this->*status_opt[status])(price);
}

bool Trader::operator==(const Trader &t) const
{
    return (cash == t.cash
            && status == t.status);
}

bool Trader::operator<(const Trader &t) const
{
    return (cash < t.cash
            && status_freedom[status] <= status_freedom[t.status]);
}

const vector<string>& Trader::get_transaction() const
{
    return transaction;
}

int Trader::get_cash() const
{
    return cash;
}
