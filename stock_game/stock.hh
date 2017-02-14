#ifndef STOCK_H
#define STOCK_H

#include "trader.hh"

class Stock
{
  public:
    Stock();
    int get_max_profit(std::vector<int> prices);
    const std::vector<std::vector<std::string>>& get_transactions() const;

  private:
    int max_profit;
    std::vector<std::vector<std::string>> transactions;
};


#endif /* STOCK_H */
