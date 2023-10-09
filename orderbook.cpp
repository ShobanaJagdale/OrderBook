#include <iostream>
#include <vector>
#include <bits/stdc++.h>


class Order
{
    float price=0;
    int volume=0;
    char side;
public:
    Order(const float& p, const int& vol, const char s):price(p),volume(vol),side(s){}
    void setVolume(const int& v)
    {
        volume=v;
    }
    int getVolume()
    {
        return volume;
    }
    char getSide() 
    { 
        return side;
    }
    void updateQty(int fillQty)
    {
        volume=volume-fillQty;
    }
    float getPrice()
    {
        return price; 
    }
};    
bool sortPrice(Order O1, Order O2)
{
    return(O1.getPrice()<O2.getPrice());
}
class OrderBook
{
    std::vector<Order> BuyOrders;
    std::vector<Order> SellOrders;
    public:
    std::vector<Order>& getBuyOrders() {return BuyOrders;}
    std::vector<Order>& getSellOrders() {return SellOrders;}
    void updateBuyOrders(const Order& order)
    {
        BuyOrders.push_back(order);
        std::sort(BuyOrders.begin(),BuyOrders.end(),sortPrice);
    }
    void updateSellOrders(const Order& order)
    {
        SellOrders.push_back(order);
        std::sort(SellOrders.begin(),SellOrders.end(),sortPrice);
    }
}; 

OrderBook orderBook;
static int orderNumber=0;

void AddOrder(Order& order)
{
    //TODO: Refactor it using templates.
    orderNumber++;
    if(order.getSide()=='B')
    {
        std::vector<Order>& SellOrders=orderBook.getSellOrders();
        if(SellOrders.size()==0)
        {
            orderBook.updateBuyOrders(order);
            std::cout<<"\n Order #" <<orderNumber << " - No Trade";
        }  
        else
        {
            int i=0;
            bool traded=false;;
            do
            {
                Order& SellOrder = SellOrders[i]; 
                if(SellOrder.getPrice()<=order.getPrice())
                {
                    if(SellOrder.getVolume()!=0 && SellOrder.getVolume()>=order.getVolume())
                    {
                        std::cout<<"\n Order #"<< orderNumber << " - " << order.getVolume()<< " Lots trade at the price of "<< SellOrder.getPrice();
                        SellOrder.updateQty(order.getVolume());
                        order.updateQty(order.getVolume());
                        traded=true;
                    }   
                    else if(SellOrder.getVolume()!=0 && SellOrder.getVolume()<order.getVolume())
                    {
                        std::cout<<"\n Order #"<< orderNumber << " - " << SellOrder.getVolume()<< " Lots trade at the price of "<< SellOrder.getPrice();
                        order.updateQty(SellOrder.getVolume());
                        SellOrder.updateQty(SellOrder.getVolume());
                        traded=true;
                    }
                    i++;
                }
                else
                    break;
            }
            while(order.getVolume()>0 && i<SellOrders.size());    
            if(!traded)
                std::cout<<"\n Order #" << orderNumber << " - No Trade ";
            orderBook.updateBuyOrders(order);    
        }  
    }
    else if(order.getSide()=='S')
    {
        std::vector<Order>& BuyOrders=orderBook.getBuyOrders();
        if(BuyOrders.size()==0)
        {
            orderBook.updateSellOrders(order);
            std::cout<<"\n Order #" <<orderNumber << " - No Trade";
        }  
        else
        {
            int i=BuyOrders.size()-1;
            bool traded=false;
            do
            {
                Order& BuyOrder = BuyOrders[i]; 
                if(BuyOrder.getPrice()>=order.getPrice())
                {
                    if(BuyOrder.getVolume()!=0 && BuyOrder.getVolume()>=order.getVolume())
                    {
                        std::cout<<"\n Order #"<<orderNumber << " - " << order.getVolume() <<" Lots trade at the price of "<< BuyOrder.getPrice();
                        BuyOrder.updateQty(order.getVolume());
                        order.updateQty(order.getVolume());
                        traded=true;
                    }   
                    else if(BuyOrder.getVolume()!=0 && BuyOrder.getVolume()<order.getVolume())
                    {
                        std::cout<<"\n Order #"<<orderNumber << " - " << BuyOrder.getVolume() <<" Lots trade at the price of "<< BuyOrder.getPrice();
                        order.updateQty(BuyOrder.getVolume());
                        BuyOrder.updateQty(BuyOrder.getVolume());
                        traded=true;
                       
                    }    
                    i--;
                }
                else
                    break;
                }
            while(order.getVolume()>0 && i>=0);  
            if(!traded)
                std::cout<<"\n Order #" << orderNumber << " - No Trade ";
            orderBook.updateSellOrders(order);    
        }  
    }
}   

void TestCase1()
{
    std::cout<<"\n\n TestCase1 ";
    Order Order1(10.3,15,'B'); 
    Order Order2(10.2,10,'B');
    Order Order3(10,40,'S'); 
    Order Order4(10.5,50,'B'); 
    Order Order5(11,30,'S'); 
   
    AddOrder(Order1);
    AddOrder(Order2);
    AddOrder(Order3);
    AddOrder(Order4);
    AddOrder(Order5);
    /* Expected output:
    - Order #1 - no trade
    - Order #2 - no trade
    - Order #3 - 15 lots trade at the price of 10.3
            -    10 lots trade at the price of 10.2    
    - Order #4 - 15 lots trade at the price of 10  
    - Order #5 - no trades
    */
}

void TestCase2()
{
    std::cout<<"\n\n TestCase2 ";
    Order Order6(10.3,15,'B'); 
    Order Order7(10.2,10,'S');
    Order Order8(10,40,'S'); 
   
    AddOrder(Order6);
    AddOrder(Order7);
    AddOrder(Order8);
  
    /* Expected output:
    - Order #6 - no trade
    - Order #7 - 10 lots trade at the price of 10.5
    - Order #8 - 5 lots trade at the price of 10.3
    */
}

void TestCase3()
{
    //clearing orderBook and orders.
    std::cout<<"\n\n TestCase3 ";
    std::cout<<"\n\n Clearing OrderBook and orders ";
    orderBook.getBuyOrders().clear();
    orderBook.getSellOrders().clear();
    orderNumber=0;
    
    Order Order1(10.3,15,'B'); 
    Order Order2(10.2,10,'S');
    Order Order3(10,40,'S'); 
   
    AddOrder(Order1);
    AddOrder(Order2);
    AddOrder(Order3);
    
    /* Expected output:
    - Order #1 - no trade
    - Order #2 - 10 lots trade at the price of 10.3
    - Order #3 - 5 lots trade at the price of 10.3
  //  */
}
int main()
{
    TestCase1();
    TestCase2();
    TestCase3();
    std::cout<<"\n";
    return 0;
}

