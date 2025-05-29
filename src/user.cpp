#include <iostream>
#include <string>
#include "Admin.h"
#include "Staff.h"
#include "Patient.h"
#include <fstream>
using namespace std; 


int main()
{
    bool check=true; //Loop variable 
    int choice; //User's choice from first menu 
    string password; //Password for each case 

    //Calling function to read and record an pre-existing data on "Patient_Records.csv" and add them to mapping 
    Patient::add_to_mapping();

    //Calling function to read pre-exisitng appointment data and add attributes to patient objects 
    Patient::update_appointments(); 

    while (check) 
    {
        cout<<"-------------------------------------------------------------------------------------------\n\n";
        //Allows user to choose what functionality is needed 
        cout<< "-------------------------------- Please choose your role ------------------------------------- \n";
        cout <<"1. Adminstrator "<<endl;
        cout<<"2. Vaccine Staff "<<endl;
        cout<< "3. Patient " <<endl;
        cout<<"Enter Choice: ";
        cin>>choice; 
        cout<<"\n\n";

        switch(choice)
        {
            //USER ROLE : CLINIC ADMINISTRATOR 
            case 1 :  
            {
                Admin admin1 ; 

                //Requesting password 
                cout<<"Enter System Password for Authorization : ";
                cin>> password; 
                cout<<"\n";

                if ( admin1.log_in(password)) //i.e entered password is correct
                {
                    cout <<"Login Successful !"<<endl;
                    int adminChoice; 
                    
                    //Menu for admin functionalities 
                    do {
                        cout << "\n--------------------------------- Administrator Menu -----------------------------------\n";
                        cout << "1. View Current Patient Records\n2. Schedule Appointments\n";
                        cout << "3. Place Orders for Additonal Supplies \n4. Logout\n";
                        cout << "Enter choice: ";
                        cin >> adminChoice;
            
                        switch (adminChoice) {
                            case 1: {
                                //Viewing  patient records currently on file 
                                admin1.view_data();
                                 break;
                            }

                            case 2: {
                                //Scheduling appointments in Appointemnts.csv
                                cout<<"\n\n";
                                admin1.appointments(); 
                                break;
                            }
                        
                            case 3: {
                                //Placing order is vaccine stock decreases 
                                string v_type;
                                int current_stock; 
                                int minimum =1000; //min. doses of vaccine 


                                cout<<"Enter Vaccine to Check stock :  ";
                                cin>> v_type;

                                //Creating a vaccine object 
                                Vaccine *check_val= Vaccine::createVaccine(v_type);

                                //If vaccine is not offered, a nullptr is returned by createVaccine()
                                if (check_val==nullptr)
                                {
                                    cout<<"This vaccine is not currently offered at Richmond Clinic !\n\n";
                                }
                                else{
                                    current_stock =check_val->getCurrentStock(); //Storing stock of vaccine
                                    cout<<"\n";
                                    cout<<"Current Stock : "<<current_stock<<endl; 

                                    //If vaccine supply is below or equal to minimum threshold 
                                    if (current_stock<=minimum)
                                    {
                                        cout<<"Warning : Vaccine in Low Supply ! ( < 1000 available doses )\n"<<endl;
                                        cout<<"Placing Order for additional 1,200 doses from Sinopharm CNBG \n\n ";
                                    }

                        
                                    //i.e Vaccine in adequate supply 
                                    else {
                                        cout<<"Vaccine Supply is Adequate \n";
                                        cout<< current_stock <<" doses available for "<<v_type<<"\n"; 
                                    }
                                }

                                break;
                            }
                           
                            case 4: {
                                cout << "Logging out...\n"; 
                                break;
                            }
                            default: {
                                cout << "Invalid choice, try again.\n";
                            }
                        }
                    } while (adminChoice != 4); //Loop will repeat  as long as user does not log out 
                } 
                else {
                    cout<< "Incorrect Password. Please retry !"<<endl;}
                break;
            }
            
            //USER ROLE : CLINIC STAFF
            case 2 :  
            {
                //Requesting password 
                cout<<"Enter Staff ID : ";
                cin>> password; 

                //Creating Staff Object 
                Staff staff1(password); 

                if ( staff1.log_in(password))
                {
                    cout <<"Login Successful !"<<endl;
                    
                    //creating a staff object 
                    int staffChoice; 

                    do {
                        cout << "\n--------------------------------- Staff Menu -------------------------------\n";
                        cout << "1. View Current Vaccine Stocks \n2. Register Patient Vaccination \n";
                        cout << "3. Logout\n";
                        cout << "Enter choice: ";
                        cin >> staffChoice;
            
                        switch (staffChoice) {
                            case 1: {
                                //Displaying all vaccines and they're availability
                                staff1.view_stocks();
                                 break;
                            }

                            case 2: {
                                string entered_id;

                                //Getting patient's Emirates ID 
                                cout<<"Enter Patient Emirates ID : "; 
                                cin>>entered_id; 

                                // Checking if patient already exisits on record 
                                 Patient* patient = Patient::getPatient(entered_id);

                                // i.e patient not on record 
                                if (patient == nullptr) {
                                    cout<<"\n";
                                    cout << "Error: Patient not found in records.\n";
                                    cout<<"Patient needs to be registered first. \n";
                                    cout<<"Please contact Admin to register the patient.\n";
                                } 
                                
                                //i.e patient is on file 
                                else {
                                    // Pass patient pointer to update_dose
                                    staff1.update_dose(patient); 

                                    //Updating patient record on file 
                                    staff1.updateRecord(patient);  

                                    //deaalocating memory 
                                    delete patient; 
                                 }
                                break;
                            }
                           
                            case 3: {
                                cout << "Logging out...\n"; 
                                break;
                            }
                            default: {
                                cout << "Invalid choice, try again.\n";
                            }
                        }
                    } while (staffChoice != 3);
                }

                else {
                    cout<< "Incorrect Password. Please retry !"<<endl;}
                break;
            }

            //USER ROLE : PATIENT
            case 3 :  
            {
                cout<<"**********************************************************************************************\n\n";
                cout<<"Welcome to Richmond Clinic ! \n\n";
                cout<<"At Richmond Clinic, we are committed to providing safe and reliable vaccinations to protect you and your loved ones.\nFrom routine immunizations to specialized vaccines, our expert team ensures top-quality care in a comfortable and professional setting.\n\n"; 

                string p_id;
                cout<<"Please enter Emirates ID: ";
                cin>>p_id; 
                cout<<"\n";

                //Checking if patient already exists 
                Patient* patient_ptr= Patient::getPatient(p_id); 

                if (patient_ptr){ // returned ptr is not null i.e patient is already registered in system
                     cout<<"You're already registered in our system "<<patient_ptr->getName()<<".\n";
                     
                }

                else { //if  patient does not exist in systemm 
                                    
                    //Registering patient into system 
                        cout<<"You're not currently registered in our system! \n";
                        cout<<"Please enter details prompted below to register youself in the system.\n";
                        string name, type;
                        cout<<"Enter Name: ";
                        cin>>name;

                        cout<<"Enter Vaccine Type: ";
                        cin>>type; 

                        //creating patient obj 
                        patient_ptr = new Patient(name, p_id, type);
                        patient_ptr->register_patient(patient_ptr);
                        cout<<"Successfully registered you into our system";
                    }

                 //Menu for patient functionalities 
                 int patientChoice; //variable storing option from menu 
                    
                    do {
                        cout << "\n------------------------------------------ Patient Menu --------------------------------------------\n";
                        cout << "1. Check Vaccines Offered and Additional Information \n2. View Scheduled Appointments\n";
                        cout << "3.Logout\n";
                        cout << "Enter choice: ";
                        cin >> patientChoice;

                        switch (patientChoice) 
                        {

                            //Getting info for a particular vaccine 
                            case 1: 
                            {
                                cout<<"Vaccines Currently Offered at our Clinic : \n"<<endl;

                                int index=1; //loop variable
                                string my_vaccine; //user input 

                                //Printing vaccines from mapping
                                for ( auto i: Vaccine::stock)
                                {
                                    cout<< index << ". "<< i.first<<endl; 
                                    index++; 
                                }

                                cout<<"\n\n";
                                cout<< "Enter Name of Vaccine You Would Like to Check :";
                                cin >> my_vaccine; 

                                //creating vaccine object 
                                Vaccine* user_vacc= Vaccine::createVaccine(my_vaccine); 

                                //Printing information
                                cout<<"\n_______________________________________________________________________________________________________\n\n";
                                cout<<"                                           VACCINE : "<<my_vaccine<<"                         "<<endl;
                                cout<<"\n_______________________________________________________________________________________________________\n\n";
                                cout << "Number of Required Doses : "<<user_vacc->getRequiredDoses()<<endl;
                                cout << "Possible Side Effects : "<<user_vacc->getSideEffects()<<endl;
                                cout <<"Aproxmiate Recovery Period : "<<user_vacc->getRecoveryTime()<<endl;
                                cout<<"\n";
                                
                                //Deallocating memeory
                                delete user_vacc;
                                break;
                            }

                            //Checking if they have an app scheduled 
                            case 2: 
                            {
                                string date;
                                date = patient_ptr->getAppDate(); 
                               

                                //For Patients with registered appointments
                                if (date!="") //entry is not the default value i.e not an empty stringß
                                {
                                    cout<<"Appointment Date: "<<date<<endl;
                                    cout<<"Appointment Timing: "<<patient_ptr->getTime()<<endl; 

                                }

                                //For Patients with no bookings 
                                else { //date is a null
                                    cout<<"You Have Not Booked Any Appointments ! \n\n";
                                    cout<<"Please contact Admin to book your appointment !\n\n";
                                }

                                break;
                            }
                           
                            case 3: 
                            {
                                cout << "Logging out...\n\n"; 
                                break;
                            }

                            default: 
                            {
                                cout << "Invalid choice, try again.\n";
                            }
                        }
                    }
                     
                    while (patientChoice != 3);
                    break;
            }

            default: 
            {
                cout<<"Invalid Option. Please Try Again !\n"<<endl;
                //re-run program in this case 
                check = false; 
                break;
            }
        }

        //Re-running program 
        cout<< "Would you like to continue ? Enter 1 (Yes) or 0 (No) : " ;

        //Program will re-run as long as user enters 1
        cin >> check; //updating while loop condition 
    }
}
