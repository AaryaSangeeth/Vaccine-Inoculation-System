#ifndef VACCINE_H
#define VACCINE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <functional>
#pragma once 
using namespace std; 

class Vaccine {
protected:
    string name;
    int required_doses;
    string side_effects;
    string recovery_time;
    
public:
    //mapping of vaccine:count
    static map<string,int>stock; //made public for access outside class scope i.e in main


    // Default constructor
    Vaccine(); 

    // Parameterized constructor 
    Vaccine(string n, int doses, string effects, string recovery)
        : name(n), required_doses(doses), side_effects(effects), recovery_time(recovery) {}

    // Virtual destructor
    virtual ~Vaccine() {} 

    // Getters
    virtual string getName() const { return name; }
    virtual int getRequiredDoses() const { return required_doses; }
    virtual string getSideEffects() const { return side_effects; }
    virtual string getRecoveryTime() const { return recovery_time; }
    virtual int getCurrentStock();

    // Static fucntion to create vaccine specific objects 
    static Vaccine* createVaccine(const string& type);

    // Friend classes
    friend class Admin;
    friend class Staff;     
};



// Derived classes 
class Pfizer : public Vaccine {
public:
    Pfizer() : Vaccine("Pfizer", 2, "Fatigue, Fever", "1-2 days") {}

    //Returns stock of vaccine
    virtual int getCurrentStock(){
        for (auto i:Vaccine::stock)
        {
            if (i.first=="Pfizer"){
                return i.second; //returns stock if name matches 
            }
        }
        return 0; //if not in mapping 
    }

};

class Moderna : public Vaccine 
{
public:
    Moderna() : Vaccine("Moderna", 2, "Headache, Chills", "1-2 days") {}

    //Returns stock of vaccine
    virtual int getCurrentStock(){
        for (auto i:Vaccine::stock)
        {
            if (i.first=="Moderna"){
                return i.second; //returns stock if name matches 
            }
        }
        return 0; //if not in mapping 
    }
};

class AstraZeneca : public Vaccine 
{
public:
    AstraZeneca() : Vaccine("AstraZeneca", 2, "Mild fever, Body ache", "2-3 days") {}

    //Returns stock of vaccine
    virtual int getCurrentStock(){
        for (auto i:Vaccine::stock)
        {
            if (i.first=="AstraZeneca"){
                return i.second; //returns stock if name matches 
            }
        }
        return 0; //if not in mapping 
    }
};

class HPV : public Vaccine 
{
public:
    HPV() : Vaccine("HPV", 1, "Mild fatigue, Soreness", "1 day") {}

    //Returns stock of vaccine
    virtual int getCurrentStock(){
        for (auto i:Vaccine::stock)
        {
            if (i.first=="HPV"){
                return i.second; //returns stock if name matches 
            }
        }
        return 0; //if not in mapping 
    }
};

class Tetanus : public Vaccine 
{
public:
    Tetanus() : Vaccine("Tetanus", 3, "Mild fever", "1 day") {}

    //Returns stock of vaccine
    virtual int getCurrentStock(){
        for (auto i:Vaccine::stock)
        {
            if (i.first=="Tetanus"){
                return i.second; //returns stock if name matches 
            }
        }
        return 0; //if not in mapping 
    }
};

class Diptheria : public Vaccine 
{
public:
    Diptheria() : Vaccine("Diptheria", 2, "Mild fever, chills, headache", "2 days") {}

    //Returns stock of vaccine
    virtual int getCurrentStock(){
        for (auto i:Vaccine::stock)
        {
            if (i.first=="Diptheria"){
                return i.second; //returns stock if name matches 
            }
        }
        return 0; //if not in mapping 
    }
};

class Measles : public Vaccine 
{  
public:
    Measles() : Vaccine("Measles", 3, "Mild fever, chills, headache", "2 days") {}

    //Returns stock of vaccine
    virtual int getCurrentStock(){
        for (auto i:Vaccine::stock)
        {
            if (i.first=="Measles"){
                return i.second; //returns stock if name matches 
            }
        }
        return 0; //if not in mapping 
    }
};

#endif
