#include <iostream>
#include <string>
#include <map>
#include "Vaccine.h"
#pragma once
using namespace std; 

//forward declaration for friend classes 
class Admin;
class Staff; 


class Patient {
    private:
    string name; //Patient Name
    string id;   //Patient's Emirates ID
    string app_date=""; //Appointment Date  (DD:MM:YY)
    string vacc_type=""; //Vaccine Name / pointer to vaccine obj 
   
    string status= "Unvaccinated";  //Vaccinated or Not (all new patient are by drfualt set to be unvaccinated)
    string timing=""; //Appointment Timing (HH:MM)


    public: 
    int doses_done = 0 ; //Number of Doses Taken (initialized to 0 for all)

    //Constructor 
    Patient(string name, string id, string vacc_type);

    //Static Functions 

    //Static Map to keep track of all patient objects 
    static map <string, Patient*> patient_records;

    //Checking object exisistnece using static function 
    static Patient* getPatient(string id);

    //Function to add pre-existing records into patient_records mapping
    static void add_to_mapping();

    //Reading Appointments.csv and updating pre-exisitng patient information
    static void update_appointments();
   

    //Setters 
    void setAppointment( const string& date, const string& timing);
    void setVaccine(string vaccine);
    void setDoses(int count);
    void UpdateDoses( );

    //Getters
    string getAppDate()const;
    string getVaccine()const;
    string getName()const;
    string getID()const;
    int getDoses()const;
    string getStatus()const;
    string getTime()const; 

    //Adding new patient records to file 
    void register_patient(Patient* patient_ref); 
    //Saving appointmenet data to csv file
    void record_appointment(const string& fname);
    
    //Friend Classes
    friend class Admin; 
    friend class Staff; 
};