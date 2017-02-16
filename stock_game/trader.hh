#ifndef TRADER_H
#define TRADER_H

#include <map>
#include <string>
#include <vector>

class Trader
{
  public:
    Trader(const char* _status, const char* _transaction=NULL);
    std::vector<Trader> evolution(int price);
    bool operator==(const Trader &t) const;
    bool operator<(const Trader &t) const;
    const std::string& get_status() const;
    const std::vector<std::string>& get_transaction() const;
    int get_cash() const;
    
  private:
    std::string status;
    std::map<std::string, int> status_freedom;
    int freedom;
    std::vector<std::string> transaction;
    int investment;
    int cash;

  private:
    std::vector<Trader> opt_when_empty(int price);
    std::vector<Trader> opt_when_full(int price);
    std::vector<Trader> opt_when_cool(int price);

  private:
    Trader buy(int price);
    Trader sell(int price);
    Trader cool();
    Trader pass();
};


#endif /* TRADER_H */
