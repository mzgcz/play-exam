#include <algorithm>
#include "stock.hh"

using namespace std;

Stock::Stock()
{
    max_profit = 0;
}

int Stock::get_max_profit(vector<int> prices)
{
    vector<Trader> traders = {Trader("EMPTY")};
    
    for_each(begin(prices), end(prices), [&traders](int price) {
            vector<Trader> tmps = traders;
            traders.clear();
            for (Trader tmp : tmps) {
                vector<Trader> next = tmp.evolution(price);
                traders.insert(traders.end(), next.begin(), next.end());
            }
        });

    std::vector<Trader>::iterator it = max_element(traders.begin(), traders.end(), [](Trader &a, Trader &b) {
            return (a.get_profit() < b.get_profit());
        });
    max_profit = it->get_profit();
    
    traders.erase(remove_if(traders.begin(), traders.end(), [this](Trader &trader) {
                if ("FULL" != trader.get_status()
                    && trader.get_profit() < this->max_profit) {
                    return true;
                }

                return false;
            }),
        traders.end());
    
    for (Trader trader : traders) {        
        auto transaction = trader.get_transaction();
        if (transaction.size() > 0
            && trader.get_status() != string("FULL")) {
            transactions.push_back(transaction);
        }
    }
    
    return max_profit;
}

const vector<vector<string>>& Stock::get_transactions() const
{
    return transactions;
}
