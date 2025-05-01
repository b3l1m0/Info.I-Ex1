/*
Student name    : Bente Moebius
Username	    : bmoebius
Date		    : 20.10.2024
Task 		    : C
Time required: 2 hours
Program Description:
This program models the changes during a stirling cycles. It calculates the heat absorbed from the two thermostats and
the work executed. Based on these values it also calculates the thermal yield of this one.
The given values come from the user input. The user can give the temperatures of the cold and the hot thermostat, 
as well as the two volumes and the number of steps with which the calculation is executed.
I think my programm is understandalby and clear written as i have taken the time to add comments.
Short report: 
A. The units in this program are bar dm^3 or 1000 * kg dm^2 s^-2 the conversion factor would be 100. 
B. The tested smallest value sufficient enough to to obtain the correct output for eta is 1.0
C. The theoretically maximal thermal yield would be 1-(300K/400K) = 0.25 for this model, the modelled yield is circa 
0.09 below this value. It is not possible for the stirling machine to achieve this maximum yield. 
D. The irreversible part of the process is the heat transfer from the two thermostats. When the heat is added into the 
system it is added from the hot thermostat, but if the heat is taken away, it is not added back to the hot thermostat but 
to the cold thermostat, signifying an irreversible process.
E. No we do not need a computer to do this for us. (But it is much more fun like this :)
*/

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int main () {
    //declaration and initialisation of the variables
    const double R = 8.3144 * 1E3 * 1E-5;
    double T_A, T_B, V_A, V_B;
    int N_step;
    double Q_A, Q_B, W;
    
    //input of the values
    cout << "# Please provide the temperature of the cold thermostat in K: " << endl;
    cin >> T_A;
    
    cout << "# Please provide the temperature of the hot thermostat in K: " << endl;
    cin >> T_B;
    
    cout << "# Please provide the value for the volume at full compression in dm: " << endl;
    cin >> V_A;
    
    cout << "# Please provide the value for the volume at full expansion in dm: " << endl;
    cin >> V_B;
    
    cout << "# Please provide the number of steps: " << endl;
    cin >> N_step;
    
    //check if the input is sensible
    if (0 < T_A && T_A < T_B && 0 < V_A && V_A < V_B && 1 <= N_step) {
        // set the values to 0
        Q_A, Q_B, W = 0;
        
        // first loop
        int n_step = 0; // counter for the loop, set to 0 at the start of every new loop
        do {
            // set the values for the borders for the calculation of the integration V_ini and V_fin
            double V_ini = V_A + (double) n_step * ((V_B - V_A)/ ((double) N_step));
            double V_fin = V_A + (double) (n_step + 1) * ((V_B - V_A)/ ((double) N_step));
            
            // calculate Q_B and W based on the integral of P(VT) -> nRT * ln(V)
            Q_B = Q_B + (R*T_B* log (V_fin) ) - (R*T_B* log (V_ini) );
            W = W - ((R*T_B*log(V_fin)) - (R*T_B*log(V_ini)));
            
            // increase the counter
            n_step++;
        } while (n_step < N_step);
      
        // second loop
        n_step = 0;
        do {
            // set the values for the borders for the calculation of the integration T_ini and T_fin
            double T_ini = T_B - (double) n_step * ((T_B - T_A)/ ((double) N_step));
            double T_fin = T_B - (double) (n_step + 1) * ((T_B - T_A)/ ((double) N_step));
                
            // calculate Q_A based on the integral of Cv(V, T) -> 3nRT/2   
            Q_A = Q_A + ((3*R*T_fin)/2) - ((3*R*T_ini)/2);
             
            n_step++;
        } while (n_step < N_step);
        
        // third loop
        n_step = 0;
        do {
            // set the values for the borders for the calculation of the integration V_ini and V_fin
            double V_ini = V_B - (double) n_step * ((V_B - V_A)/ ((double) N_step));
            double V_fin = V_B - (double) (n_step + 1) * ((V_B - V_A)/ ((double) N_step));
            
            // calculate Q_A and W based on the integral of P(VT) -> nRT * ln(V) 
            Q_A = Q_A + (R*T_A* log (V_fin) ) - (R*T_A* log (V_ini) );
            W = W - ((R*T_A* log (V_fin) ) - (R*T_A* log (V_ini) ));
            
            n_step++;
        } while (n_step < N_step);
        
        // fourth loop
        n_step = 0;
        do {
            // set the values for the borders for the calculation of the integration T_ini and T_fin
            double T_ini = T_A + (double) n_step * ((T_B - T_A)/ ((double) N_step));
            double T_fin = T_A + (double) (n_step + 1) * ((T_B - T_A)/ ((double) N_step));
            
            // calculate Q_B based on the integral of Cv(V, T) -> 3nRT/2         
            Q_B = Q_B + ((3*R*T_fin)/2) - ((3*R*T_ini)/2);
                    
            n_step++;
        } while (n_step < N_step);
       
        // calculate eta 
        double eta = (0-W)/Q_B;
        
        // print out the values
        cout << "# Values of Q_B, Q_A, W and eta are: " << endl;
        cout << Q_B << ", ";
        cout << Q_A << ", ";
        cout << W << ", ";
        cout << eta << endl;
    
    // if the data does not make sense, print an error message
    }  else cout << "Error: unrealistic expectations" << endl;
    
    return 0;
}