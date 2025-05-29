#include <iostream>
#include <string>
#include <map>
#include "Vaccine.h"
using namespace std; 

//Mapping storing Vaccine:Stock 
map<string, int> Vaccine::stock =
{
    {"Pfizer", 12000},
    {"Moderna", 19222},
    {"AstraZeneca", 12000},
    {"Tetanus", 35000},
    {"Diphtheria", 2000},
    {"Measles", 90888},
    {"Chickenpox", 9099},
    {"HPV", 1000}
};

// Factory method implementation for creating vaccine specific object based on string 
Vaccine* Vaccine::createVaccine(const string& type) 
{
    static unordered_map<string, function<Vaccine*()>> vaccineMap = 
    {
        {"Pfizer", []() { return new Pfizer(); }},
        {"Moderna", []() { return new Moderna(); }},
        {"AstraZeneca", []() { return new AstraZeneca(); }},
        {"HPV", []() { return new HPV(); }},
        {"Tetanus", []() { return new Tetanus(); }},
        {"Diptheria", []() { return new Diptheria(); }},
        {"Measles", []() { return new Measles(); }}
    };

    auto it = vaccineMap.find(type);
    return (it != vaccineMap.end()) ? it->second() : nullptr;
}

//Vaccine stock tracking fucntion 
int Vaccine::getCurrentStock(){
    int tsum=0;
    for (const auto i: stock){
        tsum+=i.second; //adding up stock of all vaccine types
    }
    return tsum; 
}

