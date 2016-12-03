/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Nicholas Dass
 *
 * Created on November 16, 2016, 1:59 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// This is the Customer class

class Customer {
// Field variables    
protected:
    char* name;
    int numberOfCalls;
    double balance;
    int numberOfMinutes;
    
public:
    Customer(char* name, double balance) {
        this->name = name;
        this->numberOfCalls = 0;
        this->balance = balance;
        this->numberOfMinutes = 0;
    }

    // This method computes a bill for Customer.
    virtual double computeBill() {
        return 10 + (0.50 * numberOfCalls);
    }

    // Add Call method.
    virtual void addCall(int min) {
        numberOfCalls++;
    }

    char* getName() {
        return name;
    }

    void printBill() {
        cout << getName() << " owes $" << computeBill()
                << " dollars." << endl;
    }

    ~Customer() {
        
    }
};

// This is the PremiumCustomer class that inherits from Customer
class PremiumCustomer : public Customer {
       
protected:
    int numberOfMinutes;

public:
    PremiumCustomer(char* name, double balance) : Customer(name, balance) {

        this->numberOfMinutes = 0;

    }
    // This method computes a bill for a Premium Customer.
    double computeBill() {
        return 20 + (numberOfCalls * 0.05)+ (numberOfMinutes * 0.10);
    }

    void addCall(int min) {
        numberOfCalls++;
        numberOfMinutes += min;

    }

};

// This class simulates calls made by Customer and Premium customers.
class Simulate{
    
public:
    void generate(){
        
        double normal = 0;
        double premium = 0;
        
        //generate a random number of customers
        int numCust = (rand() % 200) + 50;
        
        vector<Customer*> vectCustomer;
        vector<PremiumCustomer*> vectPremiumCustomer;
        
        for(int i = 0; i < numCust; i++){       
            vectCustomer.push_back(new Customer("Customer",0));
             
        }

        for(int i = 0; i < numCust; i++){
            vectPremiumCustomer.push_back(new PremiumCustomer("Premium Customer", 0));
        }

        //Add number of calls for each Customer
        for (int i = 0; i < numCust; i++) {
            Customer* c = vectCustomer.at(i);
            
            //generate a random number 10-100
            int numCalls = (rand() % 90) + 10;
            //add that many calls of random time 1 min to 4 HOURS
            for (int j = 0; j < numCalls; j++) {
                int numMin = (rand() % 240) + 1;
                c->addCall(numMin);
            }
        }
        
         //Add number of calls for each Premium Customer
        for (int i = 0; i < numCust; i++) {
            PremiumCustomer* c = vectPremiumCustomer.at(i);
            
            //generate a random number 10-100
            int numCalls = (rand() % 90) + 10;
            //add that many calls of random time 1 min to 4 HOURS
            for (int j = 0; j < numCalls; j++) {
                int numMin = (rand() % 240) + 1;
                c->addCall(numMin);
            }
        }
        
            //This prints how much each Customer owes. 
           for (int i = 0; i < numCust; i++) {
               Customer* c = vectCustomer.at(i);
               //PremiumCustomer* c = vectPremiumCustomer.at(i);
               normal += c->computeBill();
               
               c->printBill();
       }
        
        cout << endl;
        
         //This prints how much each Premium Customer owes. 
           for (int i = 0; i < numCust; i++) {
               PremiumCustomer* c = vectPremiumCustomer.at(i);
               premium += c->computeBill();

               c->printBill();
       }
        
       normal /= numCust;
       premium /= numCust;
       cout << endl;
       
       cout << "There are " << vectCustomer.size() << " Basic Customers" << endl;
       cout << "There are " << vectPremiumCustomer.size() << " Premium Customers" << endl;
       
       cout << endl;
       
       cout << "Basic Customer's average bill is " << setprecision(2) << fixed << normal << endl;       
       cout << "Premium Customer's average bill is " << setprecision(2) << fixed << premium << endl;
       
       cout << endl;
       
       if (normal < premium) {
           cout << "Customers on the normal plan on average, save more than customers on the premium plan." << endl;
       } else {
           cout << "Customers on the premium plan on average, save more than customers on the normal plan." << endl;
       }

       for (int i = 0; i < numCust; i++) {
           free(vectCustomer.at(i));
       }
       
        for (int i = 0; i < numCust; i++) {
           free(vectPremiumCustomer.at(i));
       } 
        
    }
      
};

// Main method to run program
int main(int argc, char** argv) {
    
    Simulate* g;
    g->generate();
  
    return 0;
}

