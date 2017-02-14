#ifndef TRADER_H
#define TRADER_H

#include <string>
#include <vector>

class Trader
{
  public:
    Trader(const char* _status);
    Trader(const char* _status, const char* _transaction);
    std::vector<Trader> evolution(int price);
    bool operator==(const Trader &t) const;
    const std::string& get_status() const;
    const std::vector<std::string>& get_transaction() const;
    int get_profit() const;
    
  private:
    std::string status;
    std::vector<std::string> transaction;
    int profit;
    int investment;
    
    Trader buy(int price);
    Trader sell(int price);
    Trader cool();
    Trader pass();
};


#endif /* TRADER_H */
