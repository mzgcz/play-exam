#include "trader.hh"

using namespace std;

map<string, vector<Trader>(Trader::*)(int) const> Trader::status_opt {
    {"FULL", &Trader::opt_when_full},
    {"EMPTY", &Trader::opt_when_empty},
    {"COOL", &Trader::opt_when_cool}
};

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
