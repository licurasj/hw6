#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        //convert string to vector of ints
        std::vector<int> kArray;
        //unsigned long long* w[5] ={0};
        size_t it=0;
        for(size_t i = 0 ; i<30; i++){
            if(i< (30-k.size())){
                kArray.push_back(0);
            }
            else if(it!=k.size()){
                char temp = k[it];
                if(temp>'9'&& temp < 'a'){
                    temp = tolower(temp);
                }

                if(temp<'a'){
                    temp -= 22;
                }
                else if(temp >'9'){
                    temp -= 97;
                }
                kArray.push_back(temp);
                it++;
            }
        }
        HASH_INDEX_T out=0;
        //convert to decimal and add to output
        for(int i=0;i<5;i++){
            out += ((((((kArray[i*6])*36+kArray[i*6+1])*36+kArray[i*6+2])*36+kArray[i*6+3])*36+kArray[i*6+4])*36+kArray[i*6+5]) *rValues[i];
        }
        return out;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
