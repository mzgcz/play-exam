#include "trader.hh"

using namespace std;

Trader::Trader(const char* _status)
{
    status = string(_status);
}

Trader::Trader(const char* _status, const char* _transaction)
{
    status = string(_status);
    transactions.push_back(string(_transaction));
}

vector<Trader> Trader::evolution(int price)
{
    vector<Trader> traders;

    if (string("EMPTY") == status) {
        Trader trader_buy = *this;
        trader_buy.status = string("FULL");
        trader_buy.transactions.push_back(string("buy"));
        traders.push_back(trader_buy);

        Trader trader_pass = *this;
        trader_pass.transactions.push_back(string("pass"));
        traders.push_back(trader_pass);
    } else if (string("FULL") == status) {
        Trader trader_buy = *this;
        trader_buy.status = string("COOL");
        trader_buy.transactions.push_back(string("sell"));
        traders.push_back(trader_buy);

        Trader trader_pass = *this;
        trader_pass.transactions.push_back(string("pass"));
        traders.push_back(trader_pass);
    } else if (string("COOL") == status) {
        Trader trader_cool = *this;
        trader_cool.status = string("EMPTY");
        trader_cool.transactions.push_back(string("cooldown"));
        traders.push_back(trader_cool);
    }

    return traders;
}

bool Trader::operator==(const Trader &t) const
{
    return (this->status == t.status) && (this->transactions == t.transactions);
}
