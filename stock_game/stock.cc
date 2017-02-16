// 每天所做的事：
// 1. 操作：buy, sell, pass, cooldown
// 2. 剪枝：排除其中必然无法获取最大利润的组合

// 最后一天所做的事：
// 1. 操作：buy, sell, pass, cooldown
// 2. 剪枝：排除其中比如无法获取最大利润的组合
// 3. 清算：清点当前所有组合中的利润最大者，且状态不是满仓

// 剪枝依据：
// 1. 现额：当前利润-当前投资额
// 2. 状态自由度：满仓[FULL](2)、空仓可操作[EMPTY](1)、空仓不可操作[COOL](0)
// --------------------------------------------
// A\B         满仓    空仓可操作    空仓不可操作
// 满仓          >         >            >
// 空仓可操作               >            >
// 空仓不可操作                          >
// --------------------------------------------
// 表述：当A的现额 > B的现额，且A的状态自由度 >= B的状态自由度，
//          则最大利润组合将出现在A中，B可以剪去

#include <algorithm>
#include "stock.hh"

using namespace std;

Stock::Stock()
{
    max_profit = 0;
}

void Stock::evolution_every_day(vector<Trader> &traders, int price) const {
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
