/*
Problem Statement
The program will ask the quantity of each product. The program will also ask if that product is wrapped as a gift?
*******************************************************************************
Then the program will show / output below details.
-The product name, quantity & total amount of that product.
-Subtotal
-The discount name applied & the discount amount.
-The shipping fee & the gift wrap fee.
-Total
*******************************************************************************
Discount Rules:
"flat_10_discount": If cart total exceeds $200, apply a flat $10 discount on the cart total.
"bulk_5_discount": If the quantity of any single product exceeds 10 units, apply a 5% discount on that item's total price.
"bulk_10_discount": If total quantity exceeds 20 units, apply a 10% discount on the cart total.
"tiered_50_discount": If total quantity exceeds 30 units & any single product quantity greater than 15, then apply a 50% discount on products which are above  15 quantity. The first 15 quantities have the original price and units above 15 will get a 50% discount.
Note: Only one rule can be applied per purchase. If multiple discounts are applicable, the program calculates the discount amount for each rule and applies the most beneficial one for customer.
*************************************************************************************
*/

#include<bits/stdc++.h>
using namespace std;
int main()
{

map<string,int> items;    //To store item name and quantity
map<string,int> cost;       //To store item name and price of each item

int gift_wrap_fee=0;
int shipping_fee=0;
bool greater_than_10=false;
bool greater_than_15=false;
int capacity;
cout<<"Enter the number of products you would like to add ->\n ";
cin>>capacity;
if(capacity==0)
{
cout<<"Enter a valid number";
exit(0);
} 

int cnt=0;

cout<<"******************Welcome to the shopping cart***********************\n";
cin.get();
for(int i=1;i<=capacity;i++){
    int quantity;
    string item;
    int price;
    string gift;
cout<<"Enter the name of product "<<i<<endl;
getline(cin,item);
cout<<"Enter the cost of "<<item<<endl;
cin>>price;
cost.insert({item,price});
cout<<"Enter the quantity of "<<item<<endl;
cin>>quantity;
cnt+=quantity;
if(quantity>10) greater_than_10=true;
if(quantity>15) greater_than_15=true;
items.insert({item,quantity});
cout<<"Would you like to add gift wrap as well? (yes/no) "<<endl;
cin>>gift;
if(gift=="yes") gift_wrap_fee+=quantity;
cin.get();
}


shipping_fee=ceil(float(cnt)/float(10));        //shipping fee which is 5$ per 10 items
shipping_fee*=5;

string rule;
int total_quantity=0;
float cart_total=0,original_cart;

for(auto x:items)
{
    total_quantity+=x.second;
    cart_total+=float(cost[x.first])*float(x.second);
    cost[x.first]=cost[x.first]*x.second;
}
original_cart=cart_total;


//********Applying Discounts************
if(total_quantity>30&&greater_than_15==true)
{
for(auto x:items){
    int no=0;
    float disc;
    if(x.second>15)
    {
       no=x.second-15;
       disc=float(no)*(float(cost[x.first])/float(x.second))*float(5)/float(100);
       cost[x.first]=cost[x.first]-disc;
       cart_total-=disc;     
    }
}
    rule="tiered_50_discount";
}

else if(total_quantity>20&&total_quantity<=30)
{
    cart_total=float(cart_total)*(float(90)/float(100));
    rule="bulk_10_discount";
}

else if(greater_than_10==true){

for(auto x:items)
{
    float disc;
    if(x.second>10)
    {
       disc=float(cost[x.first])*float(5)/float(100);
       cost[x.first]=cost[x.first]*float(5)/float(100);
       cart_total-=disc;     
    }
}
    rule="bulk_5_discount";
}

else if(cart_total>200)
{
    cart_total-=10;
    rule="flat_10_discount";
}
else 
{
    rule="Sorry not eligible for discounts";
}

    cout<<"*********************Bill****************************\n";

for(auto x:items)
{
    cout<<"product name: "<<x.first<<" , Quantity: "<<x.second<<" , Total Amount: "<<cost[x.first]<<"$";                //adding dollar signs for better output
    cout<<endl;
}
    cout<<"Subtotal is : "<<original_cart<<"$"<<endl;
    cout<<"Discout name: "<<rule<<" , Discount amount:  "<<original_cart-cart_total<<"$"<<endl;
    cout<<"Shipping fee: "<<shipping_fee<<"$ , Gift rap fee: "<<gift_wrap_fee<<"$"<<endl;
    cart_total=cart_total-(gift_wrap_fee+shipping_fee);
    cout<<"Total: "<<cart_total<<"$"<<endl;
    cout<<"******************************************************\n";
    cout<<"Press enter to Exit :)";
    getchar();

}