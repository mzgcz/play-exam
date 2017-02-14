#include <gtest/gtest.h>
#include "../stock.hh"

using namespace std;

TEST(give_prices_empty, stock_test)
{
    Stock stock;
    
    vector<int> prices;
    EXPECT_EQ(0, stock.get_max_profit(prices));

    vector<vector<string>> transactions;
    EXPECT_EQ(transactions, stock.get_transactions());
}

TEST(give_prices_is_1, stock_test)
{
    Stock stock;
    
    vector<int> prices = {1};
    EXPECT_EQ(0, stock.get_max_profit(prices));

    vector<vector<string>> transactions;
    vector<string> transaction = {"pass"};
    transactions.push_back(transaction);
    EXPECT_EQ(transactions, stock.get_transactions());
}

TEST(give_prices_is_1_2, stock_test)
{
    Stock stock;
    
    vector<int> prices = {1, 2};
    EXPECT_EQ(1, stock.get_max_profit(prices));

    vector<vector<string>> transactions;
    vector<string> transaction = {"buy", "sell"};
    transactions.push_back(transaction);
    EXPECT_EQ(transactions, stock.get_transactions());
}

TEST(give_prices_is_2_1, stock_test)
{
    Stock stock;
    
    vector<int> prices = {2, 1};
    EXPECT_EQ(0, stock.get_max_profit(prices));

    vector<vector<string>> transactions;
    vector<string> transaction = {"pass", "pass"};
    transactions.push_back(transaction);
    EXPECT_EQ(transactions, stock.get_transactions());
}

TEST(give_prices_is_1_1, stock_test)
{
    Stock stock;
    
    vector<int> prices = {1, 1};
    EXPECT_EQ(0, stock.get_max_profit(prices));

    vector<vector<string>> transactions;
    vector<string> transaction_1 = {"buy", "sell"};
    transactions.push_back(transaction_1);
    vector<string> transaction_2 = {"pass", "pass"};
    transactions.push_back(transaction_2);
    EXPECT_EQ(transactions, stock.get_transactions());
}

TEST(give_prices_is_1_2_3_1_3, stock_test)
{
    Stock stock;
    
    vector<int> prices = {1, 2, 3, 1, 3};
    EXPECT_EQ(3, stock.get_max_profit(prices));

    vector<vector<string>> transactions;
    vector<string> transaction = {"buy", "sell", "cooldown", "buy", "sell"};
    transactions.push_back(transaction);
    EXPECT_EQ(transactions, stock.get_transactions());
}

TEST(give_prices_is_1_2_3_4_1_repeat_20, stock_test)
{
    Stock stock;
    
    vector<int> prices = {1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1, 1, 2, 3, 4, 1};
    EXPECT_EQ(60, stock.get_max_profit(prices));

    vector<vector<string>> transactions;
    vector<string> transaction = {"buy", "sell", "cooldown", "buy", "sell"};
    transactions.push_back(transaction);
    EXPECT_EQ(transactions, stock.get_transactions());
}
