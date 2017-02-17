#include <gtest/gtest.h>
#include "trader.hh"

using namespace std;

TEST(give_trader_is_empty, trader_test)
{
    vector<Trader> traders;
    traders.push_back(Trader("FULL", -1));
    traders.push_back(Trader("EMPTY", 0));

    EXPECT_EQ(traders, Trader("EMPTY").evolution(1));
}

TEST(give_trader_is_full, trader_test)
{
    vector<Trader> traders;
    traders.push_back(Trader("COOL", 1));
    traders.push_back(Trader("FULL", 0));

    EXPECT_EQ(traders, Trader("FULL").evolution(1));
}

TEST(give_trader_is_cool, trader_test)
{
    vector<Trader> traders;
    traders.push_back(Trader("EMPTY", 0));

    EXPECT_EQ(traders, Trader("COOL").evolution(1));
}
