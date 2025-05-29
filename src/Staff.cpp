#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Staff.h"
#include "Vaccine.h"

using namespace std;
//Non-default (parametrized) Constructor 
Staff::Staff(string id ){
    s_id=id; //creates staff objects based on passed staff ID
}

//Cross-checking entered ID with staff ID's on file to verify log-in
bool Staff::log_in( const string id) 
{
    ifstream inFile;
    inFile.open("/data/Staff_IDs.csv");
    string data;

    while (inFile>>data) //Reading IDs 
    {
        if (id==data) //ID found in records 
        {
            inFile.close();
            return true;
        }
    }

    //If entered if not on record
    inFile.close();
    return false; 
}


//Displaying vaccine and it's current stock 
void Staff::view_stocks()
{
    //Stock i.e the mapping in which data is stored in 

    cout << "\n------------------------ Current Vaccine Stock ---------------------------\n";
    for (const auto& entry : Vaccine::stock) {
        cout << entry.first << " :  " << entry.second << " doses\n";
        cout<<"\n";
    }
    cout << "----------------------------------------------------------------------------\n";

}

//Updating the patient's data and modifies vaccine stock data 
void Staff::update_dose(Patient* patient)
{
    string vaccine= patient->getVaccine(); //Getting vaccine type 
    patient->UpdateDoses(); //Calling patient's UpdateDose() function 
    cout<<"check : "<<patient->doses_done<<"\n";

    //Decreasing stock count for vaccine
    Vaccine::stock[vaccine]--; 

    cout << "Dose successfully administered to " << patient->getName() << ".\n";
    cout << "Remaining " << vaccine << " stock: " << Vaccine::stock[vaccine] << " doses.\n";

}

//Updating record after being vaccinated 
void Staff::updateRecord(Patient* patient_ref)
{
    // Getting the vaccine object based on the vaccine type
    Vaccine* vaccine = nullptr;
    vaccine=Vaccine::createVaccine(patient_ref->vacc_type); //Getting name of vaccine type and passing as argument 

    cout<<"Doses done: "<<patient_ref->doses_done<<"\n";

    // Updating vaccination status based on individual vaccine requirement 
    if (patient_ref->doses_done == vaccine->getRequiredDoses()) { //If patient's dose count matches the vaccines required number of doses 
            patient_ref->status = "Fully Vaccinated"; //Now patient is fully vaccinated 
    } else {
            patient_ref->status = "Partially Vaccinated"; //In this case, they need more doses to be fully vaccinated
    }


    //Rewriting data onto file 
    ifstream infile;
    infile.open("/data/Patient_Records.csv");
    vector<string> lines;
    string line;

    bool updated = false;

    if (infile.is_open()) {
        while (getline(infile, line)) {
            stringstream ss(line);
            string cell;
            vector<string> record;

            // Parsing the line and splitingt by commas
            while (getline(ss, cell, ',')) {
                record.push_back(cell);
            }

            // If we find the matching patient ID,then updating that record
            if (record.size() >= 5 && record[0] == patient_ref->getID()) {
                // Update the doses and status in the existing record
                record[3] = to_string(patient_ref->getDoses());  // Update doses
                record[4] = patient_ref->getStatus();  // Update status
                updated = true;
            }

            // Converting the updated record back into a string
            stringstream updated_line;
            for (size_t i = 0; i < record.size(); ++i) {
                updated_line << record[i];
                if (i != record.size() - 1) updated_line << ",";
            }

            lines.push_back(updated_line.str());
        }
        infile.close();
    }

    // Writing the modified content back to the file
    if (updated) {
        ofstream outfile("/data/Patient_Records.csv", ios::trunc);
        for (const string& updated_line : lines) {
            outfile << updated_line << endl;
        }
        outfile.close();
    } else {
        cout << "Patient not found in the record." << endl;
    }

    //deallocating memory for vaccine object 
    delete vaccine; 

}
