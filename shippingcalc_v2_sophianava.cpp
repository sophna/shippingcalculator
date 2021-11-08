#include <iostream>
#include <iomanip> //should be included in order to use 'setprecision(n)', 'setw(n)' manipulator
#include <math.h> //in order to use the 'round' predefined function
#include <string> //to use function 'to_string'
#include <algorithm>
#include <assert.h>
#include <fstream> //use the example from: https://www.cplusplus.com/doc/tutorial/files/

using namespace std;

const int HEADER_WIDTH = 70; //total lenght of the stream to output the program data
const int HEADER_WIDTH_LEFT_ALIGN = 49; //number of chars for banner including text
const int HEADER_WIDTH_RIGHT_ALIGN = 21; //numbers of chars for the banner to complete up to 70 chars
const int RESULT_RIGHT_ALIGN_WIDTH = 10; //number of chars for the digits results
const int RESULT_LEFT_ALIGN_WIDTH =  60; //number of chars for the text part
const float SHIPPING_COST_USA_LESS_THAN_50 = 6.00;
const float SHIPPING_COST_USA_LESS_THAN_100 = 9.00;
const float SHIPPING_COST_USA_LESS_THAN_150 = 12.00;
const float SHIPPING_COST_CAN_LESS_THAN_50 = 8.00;
const float SHIPPING_COST_CAN_LESS_THAN_100 = 12.00;
const float SHIPPING_COST_CAN_LESS_THAN_150 = 15.00;
const float SHIPPING_COST_AUS_LESS_THAN_50 = 10.00;
const float SHIPPING_COST_AUS_LESS_THAN_100 = 14.00;
const float SHIPPING_COST_AUS_LESS_THAN_150 = 17.00;
const float SHIPPING_COST_JUPITER_LESS_THAN_50 = 450.00;
const float SHIPPING_COST_JUPITER_LESS_THAN_100 = 485.00;
const float SHIPPING_COST_JUPITER_LESS_THAN_150 = 500.00;
const float FRAGILE_COST = 2.00; 
const float ORDER_TOTAL_50 = 50.00;
const float ORDER_TOTAL_100 = 100.00;
const float ORDER_TOTAL_150 = 150.00;
const float DEFAULT_SHIPPING_COST = 0.00;

int main()
{
  string item_name;
  string fragile;
  ofstream myfile; /* according to the reference, this should behave as the cout stream, I will use the same output code as I used in cout, no need to put 
   comments on each myfile statement */
  myfile.open("Order.txt");

  float order_total;
  string destination;

  cout << setfill('.'); //use setfill to change the fill char to .
  myfile << setfill('.');
  cout << setw(HEADER_WIDTH) << "" << endl; //set the width of the line to 70 chars, output a null char to print the whole stream
  myfile << setw(HEADER_WIDTH) << "" << endl; //set the width of the line to 70 chars, output a null char to print the whole stream
  cout << setfill(' ');
  myfile << setfill(' ');
  cout << "ITCS 2530 - Programming Assignment for week #3" << setw(HEADER_WIDTH_RIGHT_ALIGN) << "" << endl; //message is 28 chars lenght, fill up to HEADER_WIDTH_LEFT_ALIGN chars and then up to HEADER_WIDTH_RIGHT_ALIGN chars after the message
  myfile << "ITCS 2530 - Programming Assignment for week #3" << setw(HEADER_WIDTH_RIGHT_ALIGN) << "" << endl; //message is 28 chars lenght, fill up to HEADER_WIDTH_LEFT_ALIGN chars and then up to HEADER_WIDTH_RIGHT_ALIGN chars after the message
  cout << setfill('.'); //use setfill to change the fill char to .
  myfile << setfill('.'); //use setfill to change the fill char to .
  cout << setw(HEADER_WIDTH) << "" << endl << endl; //output the . in the third row
  myfile << setw(HEADER_WIDTH) << "" << endl << endl; //output the . in the third row

  cout << setw(HEADER_WIDTH) << left << "Please enter the item name (no spaces)" << right << ":";
  myfile << setw(HEADER_WIDTH) << left << "Please enter the item name (no spaces)" << right << ":";
  cin >> item_name; //assign user input to variable item_name
  myfile << item_name<<endl; //output to the file the raw input from the user

  transform(item_name.begin(), item_name.end(), item_name.begin(), ::toupper);

  cout << setw(HEADER_WIDTH) << left << "Is the item fragile (y=yes/n=no)" << right << ":";
  myfile << setw(HEADER_WIDTH) << left << "Is the item fragile (y=yes/n=no)" << right << ":";
  cin >> fragile; //assign user input to variable fragile
  myfile << fragile << endl; //output to the file the raw input from the user

  if ( (fragile !="y") && (fragile !="Y") && (fragile !="n") && (fragile !="N"))
  {
    cout << "Invalid entry, exiting" << endl;
    myfile << "Invalid entry, exiting" << endl;
    assert(0); //according to c++ reference, passing a zero to the assert function will stop program execution
  }

  bool item_is_fragile=false; //since the program was not stopped by the assert, it means fragile input is valid, set it to false as default
  if( (fragile=="y") || (fragile=="Y")) //evaluate if the item is fragile, if yes, then set variable item_is_fragile to true
  {
    item_is_fragile = true;
  }
  

  cout << setw(HEADER_WIDTH) << left << "Please enter your order total" << right << ":";
  myfile << setw(HEADER_WIDTH) << left << "Please enter your order total" << right << ":";
  cin >> order_total; //assign user input to variable fragile
  myfile << order_total << endl; //output to the file the raw input from the user

  cout << setw(HEADER_WIDTH) << left << "Please enter your destination. (usa/can/aus/jupiter)" << right << ":";
  myfile << setw(HEADER_WIDTH) << left << "Please enter your destination. (usa/can/aus/jupiter)" << right << ":";
  cin >> destination; //assign user input to variable fragile
  myfile << destination << endl; //output to the file the raw input from the user
  /* by testing the working example, I found out that for destination it will accept as valid any combination of lowercase and uppercase text entry
  like: uSA, usA. In order to make it work like that, I will convert any user input to uppercase */
  transform(destination.begin(), destination.end(), destination.begin(), ::toupper);
  if ((destination !="USA") && (destination !="AUS") && (destination !="CAN") && (destination != "JUPITER"))
  {
    cout << "Invalid entry, exiting" << endl;
    myfile << "Invalid entry, exiting" << endl;
    assert(0); //according to c++ reference, passing a zero to the assert function will stop program execution
  }
  //leave an empty line after all the user inputs has been captured
  cout<<endl; 
  myfile<<endl;

  cout << setw(RESULT_LEFT_ALIGN_WIDTH) << left << "Your item is" <<  right << item_name << endl;
  myfile << setw(RESULT_LEFT_ALIGN_WIDTH) << left << "Your item is" <<  right << item_name << endl;
  
  float shipping_cost = DEFAULT_SHIPPING_COST; //use the default shipping cost
  if(order_total < ORDER_TOTAL_50) //if total order is less than 
  {
    if(destination == "USA") //if total order is less than 50 and destination is usa
    {
        shipping_cost=SHIPPING_COST_USA_LESS_THAN_50;
    }
    else if(destination == "CAN") //if total order is less than 50 and destination is canada
    {
      shipping_cost=SHIPPING_COST_CAN_LESS_THAN_50;
    }
    else if (destination == "AUS") //if total order is less than 50 and destination is australia
    {
      shipping_cost=SHIPPING_COST_AUS_LESS_THAN_50; 
    }
    else if (destination == "JUPITER") //if total order is less than 50 and destination is Jupiter
    {
      shipping_cost=SHIPPING_COST_JUPITER_LESS_THAN_50; 
    }
  }
  else if((order_total>=ORDER_TOTAL_50) && (order_total<=ORDER_TOTAL_100)) //if total order is greater or equal to 50 and less or equal than 100
  {
    if(destination == "USA") //if total order is greater or equal to 50 and less or equal than 100 and shipping is usa
    {
        shipping_cost=SHIPPING_COST_USA_LESS_THAN_100;
    }
    else if(destination == "CAN") //if total order is greater or equal to 50 and less or equal than 100 and shipping is canada
    {
      shipping_cost=SHIPPING_COST_CAN_LESS_THAN_100;
    }
    else if (destination == "AUS") //if total order is greater or equal to 50 and less or equal than 100 and shipping is australia
    {
      shipping_cost=SHIPPING_COST_AUS_LESS_THAN_100;
    }
      else if (destination == "JUPITER") //if total order is greater or equal to 50 and less or equal than 100 and shipping is jupiter
    {
      shipping_cost=SHIPPING_COST_JUPITER_LESS_THAN_100;
    }
  }
  else if((order_total>ORDER_TOTAL_100) && (order_total<=ORDER_TOTAL_150)) //if total order is less than one hundred and less or equal than 150
  {
    if(destination == "USA") //if total order is less than one hundred and less or equal than 150 and shipping is usa
    {
        shipping_cost=SHIPPING_COST_USA_LESS_THAN_150;
    }
    else if(destination == "CAN") //if total order is less than one hundred and less or equal than 150 and shipping is canada
    {
      shipping_cost=SHIPPING_COST_CAN_LESS_THAN_150;
    }
    else if (destination == "AUS") //if total order is less than one hundred and less or equal than 150 and shipping is australia
    {
      shipping_cost=SHIPPING_COST_AUS_LESS_THAN_150;
    }
    else if (destination == "JUPITER") //if total order is less than one hundred and less or equal than 150 and shipping is jupiter
    {
      shipping_cost=SHIPPING_COST_JUPITER_LESS_THAN_150;
    }
  }

  if(item_is_fragile) //check if it was determined that the item is fragile, if yes, add the extra cost
  {
    shipping_cost+=FRAGILE_COST;
  }

  cout << setprecision(2)<<fixed; //use setprecision(2) to use 2 decimal places, and 'fixed' to use fixed format to show all digits
  cout << setw(RESULT_LEFT_ALIGN_WIDTH) << left << "Your shipping cost is" <<  right << '$' << shipping_cost << endl;
  myfile << setprecision(2)<<fixed; //use setprecision(2) to use 2 decimal places, and 'fixed' to use fixed format to show all digits
  myfile << setw(RESULT_LEFT_ALIGN_WIDTH) << left << "Your item is" <<  right << '$' << shipping_cost << endl;
  
  cout << setw(RESULT_LEFT_ALIGN_WIDTH) << left << "You are shipping to" <<  right << destination << endl;
  myfile << setw(RESULT_LEFT_ALIGN_WIDTH) << left << "You are shipping to" <<  right << destination << endl;
  
  cout << setw(RESULT_LEFT_ALIGN_WIDTH) << left << "Your total shipping costs are" <<  right << '$'<< (shipping_cost+order_total) << endl;
  myfile << setw(RESULT_LEFT_ALIGN_WIDTH) << left << "Your total shipping costs are" <<  right << '$' << (shipping_cost+order_total) << endl;
  
  //leave an empty line after all the outputs has been printed
  cout<<endl; 
  myfile<<endl;

  cout << setfill('-'); //use setfill to change the fill char to -
  myfile << setfill('-'); //use setfill to change the fill char to -
  cout << setw(RESULT_LEFT_ALIGN_WIDTH) << left << "" << right << "Thank you!" << endl;
  myfile << setw(RESULT_LEFT_ALIGN_WIDTH) << left << "" << right << "Thank you!" << endl;
  myfile.close();
}

