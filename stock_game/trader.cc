#include "trader.hh"

using namespace std;

map<string, int> Trader::status_freedom {
    {"FULL", 2},
    {"EMPTY", 1},
    {"COOL", 0}
};

Trader::Trader(const char* _status, int _cash)
{
    status = string(_status);
    investment = 0;
    cash = _cash;
}

int Trader::get_cash() const
{
    return cash;
}

const vector<string>& Trader::get_transaction() const
{
    return transaction;
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
