### Files:

- `Patient_Records.csv`: Stores patient registration details,(Name, Emirates ID, Vaccine Type, Dose Count, Status).
- `Appointments.csv`: Records appointment history of each patient logged by admin .
- `Staff_ID.csv`: Stores hashed clinical staff IDs, treated as valid staff IDs with admin access. 

### Data Handling:

- The files are updated automatically based on the role chosen by the user :
    - `Patient_Records.csv' : Gets updated during patient registration and doses get incremented once the vaccine has been administered.
    - 'Appointment.csv' : Gets updated each time a patient wants to book a new appointment.
    - 'Staff_ID.csv' : Is never modified internally; only used to verify staff at the time of login.
  

### Vaccine Stock Management 
- All Vaccine stock data is currently hardcoded to be part of a mapping in Class Vaccine for easy access.
- The Staff class reduces the vaccine stock when a dose is administered, using the Vaccine::stock map. 
- This map tracks the available doses for each vaccine type during program execution.
- Admins can view current stock and place new orders if stock drops below the threshold (e.g., 1000 doses).



- All file I/O uses basic C++ file streams (`fstream`, `ifstream`, `ofstream`).
