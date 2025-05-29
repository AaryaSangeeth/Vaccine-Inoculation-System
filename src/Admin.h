#include <iostream>
#include <string>
using namespace std; 


class Admin{
    private: 
    //All admins need to enter the same password to access the database 
    static const string pass_wd ; 

    public: 
    //Constructor 
    Admin();

    //Admin Log In Verification
    bool log_in( string user_passwd);

    //Viewing current patient reports and checking status 
    void view_data();

    //Booking appointments for patients 
    void appointments();

};
