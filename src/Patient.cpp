#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "Patient.h"
using namespace std; 

//mapping storing patient id and pointer to patient object 
map<string, Patient*> Patient::patient_records;  

//Non-Default (parametrized) Constructor 
Patient::Patient(string name, string id, string vacc_type)
{
    this->name = name;
    this-> id=id;
    this->vacc_type=vacc_type; 
    patient_records[id]=this; //Maps patient object pointer to patient ID in mapping 
}


//Adding pre-existing patient records to mapping 
void Patient::add_to_mapping(){
    ifstream inFile;
    if (!inFile) //failed to open file 
    {
        cout<<"Error in Opening File ! Make sure it exists or if file name is correct !\n";
    }
    else {
        inFile.open("/data/Patient_Records.csv");
        string line;

        // Skiping the header line
        getline(inFile, line); 
    
        while (getline(inFile, line))
        {
            stringstream ss(line); 
            string id, name, vaccine_type,doses;

            //Reading first three values from each record : ID, NAME, VACCINE TYPE
            getline(ss,id,',');
            getline(ss,name,',');
            getline(ss,vaccine_type,',');
            getline(ss,doses,',');


            //Creating a patient object for each record
            Patient* new_patient= new Patient(name,id,vaccine_type);

            // Check if doses is a valid number, and if not, set a default value
            if (doses.empty() || !std::all_of(doses.begin(), doses.end(), ::isdigit)) 
            {
                doses = "0"; 
            }

            //setting doses for patient (since default value is 0)
            int doses1=stoi(doses);
            new_patient->doses_done=doses1;
            
        }
        inFile.close();
    }
 }


//Reading pre-exisitng appointment records from "Appointment.csv" and updating patient information 
void Patient::update_appointments() {
    ifstream appFile("/data/Appointments.csv");
    if (!appFile) {
        cout << "Error in Opening Appointments.csv! Make sure it exists or if the file name is correct!\n";
    }

    else{
        string line;

        // Reading Appointments.csv and update patient objects
         while (getline(appFile, line)) 
         {
            stringstream ss(line);
            string id, name, vaccine_type, app_date, timing;

            // Read fields from the CSV line
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, vaccine_type, ',');
            getline(ss, app_date, ',');
            getline(ss, timing, ',');


            // Finding the patient in the patient_records map
            auto it = patient_records.find(id);
            if (it != patient_records.end()) 
            {
                // Updating the patient's appointment date and timing
                it->second->app_date = app_date;
                it->second->timing = timing;
            } 
            else 
            {
                cout << "Patient with ID " << id << " not found in records. Skipping appointment.\n";
            }
        }
        appFile.close();
    }   
}

//Checking if Patient already exists in records ; returns pointer to object if exists 
Patient* Patient::getPatient(string id)
{
    auto it = patient_records.find(id); // Searching for the ID

    if (it != patient_records.end()) 
    {
        return it->second; // Returning the pointer to obj if found
    }
    else 
    {
        return nullptr; // Returning nullptr if not found
    }
}

//Setters 
//Setting date and time for vaccination 
void Patient::setAppointment( const string& date, const string& time)
{
    app_date=date; 
    timing=time; 
}

//Setting patient's vaccine type
void Patient::setVaccine(string vaccine)
{
    this->vacc_type=vaccine;
    return;
}

//Updating number of doses administered to patient 
void Patient::UpdateDoses( )
{
    doses_done++; //increments dose count by 1
    return ; 
}


//Getters
string Patient::getAppDate()const {
    return app_date;
}

string Patient::getTime()const{
    return timing;
}

string Patient::getVaccine()const{
    return vacc_type; 
}

string Patient::getName()const{
    return name; 
}

string Patient::getID()const{
    return id ;
}

int Patient::getDoses()const{
    return doses_done;
}

string Patient::getStatus()const{
    return status; 
}

//Saving appointmenet data to csv file
void Patient::record_appointment(const string& fname)
{
    ofstream appFile;
    appFile.open(fname, ios::app); //opening file in append mode 
    if (!appFile)
    {
        cout<<"Error ! Cannot Open File "<<endl;
    }

    else{
        appFile<< id <<","<< name <<"," <<vacc_type << "," << app_date << "," <<timing; 
        cout<<"Appointment Successfully Booked \n"<<endl;
    }
}

//Entering Patient data onto file "Patient_Records"
void Patient::register_patient(Patient* patient_ref)
{
    ofstream appFile;
    appFile.open("/data/Patient_Records.csv", ios::app); //opening file in append mode 
    if (!appFile)
    {
        cout<<"Error ! Cannot Open File "<<endl;
    }
    else{
        //appending data 
        appFile<<patient_ref->id << "," << patient_ref->name <<","<< patient_ref->vacc_type <<"," << patient_ref->doses_done <<"," << patient_ref->status<<endl;
        appFile.close();
    }
    return; 

}


