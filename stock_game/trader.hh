#ifndef TRADER_H
#define TRADER_H

#include <map>
#include <string>
#include <vector>

class Trader
{
  public:
    Trader(const char* _status="EMPTY", int _cash=0);
    bool operator==(const Trader &t) const;
    bool operator<(const Trader &t) const;
    std::vector<Trader> evolution(int price) const;
    int get_cash() const;
    const std::vector<std::string>& get_transaction() const;
    
  private:
    std::string status;
    std::vector<std::string> transaction;
    int investment;
    int cash;
    static std::map<std::string, int> status_freedom;
    static std::map<std::string, std::vector<Trader>(Trader::*)(int) const> status_opt;

  private:
    std::vector<Trader> opt_when_empty(int price) const;
    std::vector<Trader> opt_when_full(int price) const;
    std::vector<Trader> opt_when_cool(int price) const;

  private:
    Trader buy(int price) const;
    Trader sell(int price) const;
    Trader cool() const;
    Trader pass() const;
};


#endif /* TRADER_H */
