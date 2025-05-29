#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "Patient.h"
#pragma once 
using namespace std; 


class Staff{
    private:  
    string s_id; //staff id
    
    public: 
    //Constructor 
    Staff(string id);
    
    //Functionalities 
    //Checking log in 
    bool log_in(const string id);
    //Viewing vaccine stocks from mapping 
    void view_stocks();
    //Updating patient's dose count and the vaccine stock after an administration 
    void update_dose(Patient* patient);
    //Updating patient's record after vacciantion ß
    void updateRecord(Patient* patient_ref);

};
