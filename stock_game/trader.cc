#include "trader.hh"

using namespace std;

Trader::Trader(const char* _status, const char* _transaction)
{
    status_freedom.insert(make_pair("FULL", 2));
    status_freedom.insert(make_pair("EMPTY", 1));
    status_freedom.insert(make_pair("COOL", 0));
    
    status = string(_status);
    freedom = status_freedom[status];
    if (_transaction != NULL) {
        transaction.push_back(string(_transaction));
    }
    investment = 0;
    cash = 0;
}

Trader Trader::buy(int price)
{
    Trader trader = *this;
    
    trader.status = string("FULL");
    trader.freedom = trader.status_freedom[trader.status];
    trader.transaction.push_back(string("buy"));
    trader.investment = price;
    trader.cash -= trader.investment;

    return trader;
}

Trader Trader::sell(int price)
{
    Trader trader = *this;

    trader.status = string("COOL");
    trader.freedom = trader.status_freedom[trader.status];
    trader.transaction.push_back(string("sell"));
    trader.investment = 0;
    trader.cash += price;

    return trader;
}

Trader Trader::cool()
{
    Trader trader = *this;

    trader.status = string("EMPTY");
    trader.freedom = trader.status_freedom[trader.status];
    trader.transaction.push_back(string("cooldown"));

    return trader;
}

Trader Trader::pass()
{
    Trader trader = *this;

    trader.transaction.push_back(string("pass"));

    return trader;
}

vector<Trader> Trader::opt_when_empty(int price) {
    vector<Trader> traders;

    traders.push_back(buy(price));
    traders.push_back(pass());

    return traders;
}

vector<Trader> Trader::opt_when_full(int price) {
    vector<Trader> traders;

    traders.push_back(sell(price));
    traders.push_back(pass());

    return traders;
}

vector<Trader> Trader::opt_when_cool(int price) {
    vector<Trader> traders;

    traders.push_back(cool());

    return traders;
}

vector<Trader> Trader::evolution(int price)
{
    typedef vector<Trader> (Trader::*p_vec_trader)(int);
    std::map<string, p_vec_trader> status_fun;

    status_fun.insert(make_pair("EMPTY", &Trader::opt_when_empty));
    status_fun.insert(make_pair("FULL", &Trader::opt_when_full));
    status_fun.insert(make_pair("COOL", &Trader::opt_when_cool));

    return (this->*status_fun[status])(price);
}

bool Trader::operator==(const Trader &t) const
{
    return (this->status == t.status
            && this->transaction == t.transaction);
}

bool Trader::operator<(const Trader &t) const
{
    if (cash < t.cash
        && freedom <= t.freedom) {
        return true;
    }

    return false;
}

const string& Trader::get_status() const
{
    return status;
}

const vector<string>& Trader::get_transaction() const
{
    return transaction;
}

int Trader::get_cash() const
{
    return cash;
}
