#include <algorithm>
#include "stock.hh"

using namespace std;

Stock::Stock()
{
    max_profit = 0;
}

void Stock::evolution_every_day(vector<Trader> &traders, int price) {
    vector<Trader> tmp_traders = traders;
    
    traders.clear();
    for (Trader trader : tmp_traders) {
        vector<Trader> next_traders = trader.evolution(price);
        traders.insert(traders.end(), next_traders.begin(), next_traders.end());
    }

    vector<Trader>::iterator it = max_element(traders.begin(), traders.end());
    traders.erase(remove_if(traders.begin(), traders.end(), [it](Trader &trader) {
                return (trader < *it) ? true : false;
            }),
        traders.end());
}

int Stock::get_max_profit(vector<int> prices)
{
    vector<Trader> traders = {Trader()};
    
    for_each(begin(prices), end(prices), [this, &traders](int price) {
            evolution_every_day(traders, price);
        });

    vector<Trader>::iterator it = max_element(traders.begin(), traders.end(), [](Trader &a, Trader &b) {
            return a.get_cash() < b.get_cash();
        });
    max_profit = it->get_cash();
    
    traders.erase(remove_if(traders.begin(), traders.end(), [it](Trader &trader) {
                return (trader.get_cash() < it->get_cash()) ? true : false;
            }),
        traders.end());
    
    for (Trader trader : traders) {
        vector<string> transaction = trader.get_transaction();
        if (transaction.size() > 0) {
            transactions.push_back(transaction);
        }
    }
    
    return max_profit;
}

const vector<vector<string>>& Stock::get_transactions() const
{
    return transactions;
}
