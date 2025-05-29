
###  `src/` Directory

This folder contains the complete source code for the Vaccine Inoculation System. It includes class definitions, implementation files, and the main entry point of the application.

### Files :

                                                                                                                                            
 `user.cpp`                          : The entry point of the program. Handles the user role selection (Admin, Staff, Patient) and redirects to corresponding module logic.                                                 
 `admin.h / admin.cpp`               : Defines and implements the `Admin` class, which manages appointments, views records, and monitors vaccine stock levels. Also handles vaccine ordering when 
                                       stock is low.             

`staff.h / staff.cpp`                : Defines and implements the `Staff` class, allowing clinic staff to update a patient's vaccination status and view current vaccine stock.                                             
 `patient.h / patient.cpp`           : Defines and implements the `Patient` class, representing each individual getting vaccinated. Handles registration, status tracking, and appointment     
                                       information.                     

 `vaccine.h / vaccine.cpp`           : Defines the base `Vaccine` class and its derived classes (e.g., Pfizer, Moderna). Manages vaccine-specific data such as required doses, recovery time, and                                         in-memory stock tracking. 


###  Additional Notes:

* Each `.cpp` file corresponds to a `.h` header file that declares the class and its public/private members.
* The program uses **modular design** to separate logic by role and functionality.
* All classes follow **OOP principles**, including encapsulation and class friendship (e.g., `Admin` and `Staff` are friend classes of `Patient`).

