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
    
  private:
    std::string status;
    std::vector<std::string> transactions;
};


#endif /* TRADER_H */
