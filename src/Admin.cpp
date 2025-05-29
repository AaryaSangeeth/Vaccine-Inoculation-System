#include <iostream>
#include <string>
#include <fstream>
#include "Admin.h"
#include "Patient.h"
using namespace std; 

//Admin password set to 12345 ( can be internally modified by changing value here)
const string Admin::pass_wd="12345";

//Constructor 
Admin::Admin() {}

//Function validating admin log in 
bool Admin::log_in( string user_passwd) {
    return user_passwd == pass_wd ;
}


//Displays current list of patients at Clinic from "Patient_Records.csv" file
void Admin::view_data()
{
    ifstream inFile;
    inFile.open("Patient_Records.csv");
    cout<<"---------------------------------------------------------------------------------------"<<endl;
    string line;
    cout<<"CURRENT PATIENT RECORDS :\n\n";
    while(getline(inFile,line))
    {
        cout<<line<<endl;
        cout<<"\n";
    }
    inFile.close();
}

//Schedules new appointments and appends data onto "Appointments.csv" 

void Admin::appointments()

{    //Getting Data from user 
    string name, patientID, v_type,date, time;
    cout<<"Enter Patient Name : ";
    cin.ignore();
    getline(cin,name);

    cout << "Enter Patient Emirates ID : ";
    getline(cin,patientID);

    cout << "Enter Vaccine Type: ";
    getline(cin,v_type);

    cout << "Enter Appointment Date (DD/MM/YYYY): ";
    getline(cin,date);

    cout << "Enter Time (HH:MM): ";
    getline(cin,time);

    //Checking if patient already exists by cross-checking patient_records mapping 
    Patient* ptr= Patient::getPatient(patientID); //getPatient() returns pointer to patient object for passed ID

    //If patient is already registered i.e pointer is not nullptr
    if (ptr!=nullptr)
    {
        cout<<"Patient on file." <<endl; //no new object created
       
        //setting appointment by calling setter from class Patient 
        ptr->setAppointment(date,time);

        //Writing new appointment to csv file 
        ptr->record_appointment("Appointments.csv");    //problem is calling record in both cases : need to only change in this case 
 

    }
    else //Patient does not exist on record 
    {
        //Creating new patient object 
        Patient* new_ptr= new Patient(name,patientID,v_type);

        //Entering new record onto file 
        new_ptr->register_patient(new_ptr);

        //Setting appointment by calling setter from class Patient 
        new_ptr->setAppointment(date,time);

        //Writing new appointment to csv file 
        new_ptr->record_appointment("Appointments.csv");
    }

    return;
}

