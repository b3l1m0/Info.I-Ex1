/*
Student name    : Bente Moebius
Username	    : bmoebius
Date		    : 10.10.2024
Task 		    : A
Time required	: 3 (reading) + 2 hours
Program Description:
This program puts out sequence of values based on user input. 
The user can put in a Temperature, two volumes and a number of steps.
If these given values are not realistic, this program with give an error message. Otherwise, based on these values, this 
program computes in a for loop (number of equidistant steps) for each volume the pressure. At the end of the loop these 
values are printed out in two columns "Volume" and "Pressure".
Short report: 
My results are good, as i could verify some of the outputs through my own calculations, and the script is clear and understandable.
Answer to the questions:
A. exponential 
B. It does make sense that they are decreasing, regarding the fact that with the same temperature and amount of substance 
there is a bigger Volume for all those molecules or atoms. Hence the pressure decreases, as there are less effective particle 
collisions with the wall as before. However from a physical standpoint there will me a point when they can no longer decrease 
as the pressure cannot be negative or zero. 
C. The limit of P would be infinity (lim V-> 0 nRT / V = infinity) but this is not physically or experimentally possible, 
because it is not possible to make zero space, and therefore not realistic. 
D. The limit of P would be zero (lim V-> infinity nRT / V = 0) which is also not realistic, as there would still be 
effective collisions as long as there would be molecules or atoms in the volume. Also, there is basically one big experiment 
testing this: outer space. As big intergalactic voids still have a pressure in the magnitude of E−17 Pa (source: wikipedia) 
and i think that substantiates my answer.
E. Increasing T_ref has the effect of increasing the pressure. This is because the molecules and atoms have more energy 
and are basically faster and have more force and hence the number and the force of the collisions increases, resulting in a 
higher pressure.
*/

#include <iostream>
#include <iomanip>
using namespace std;
int main () {
	// declaration (and initialization) of the variables used
	double R_si = 8.314;
	// calculation: 8.314 J/K mol* 1 mol (J/K -> kg m2 / s2) * 1000 dm3/m3 * E-5 (bar dm3 / K)
	double R_cst = R_si * 1 * 1E3 * 1E-5;
	double T_ref, V_min, V_max;
	int N_step;
	
	// get input and initialize variables
	cout << "# Please enter T_ref in K: " << endl;
	cin >> T_ref; 
	
	cout << "# Please enter V_min in dm3: " << endl;
	cin >> V_min; 
	
	cout << "# Please enter V_max in dm3: " << endl;
	cin >> V_max;
	
	cout << "# Please enter N_step in dm3: " << endl;
	cin >> N_step;
	
	// check if everything is realistic
	if (T_ref >= 0 && 0 < V_min && V_min < V_max && N_step >= 2) {
		
		cout << "# Values of V in dm3 and P in bar for one mole of ideal gas: " << endl;
		
		// for loop to calculate the values and print them into rows
		int n_step;
		for (n_step = 0; n_step <= N_step-1; n_step++) {
			
			// calculate V 
			double V = V_min + (double) n_step * ((V_max - V_min)/ ((double) N_step -1));
			// calculate P (P = nRT/V)
			double P = (R_cst * T_ref) / V;
			
			// print the values of V and P in two columns separated by " "
			cout << V << " "; 
			cout << P << endl;
		}
	// if the data does not make sense, print an error message	
	} else cout << "Error: unrealistic expectations" << endl; 
	
	return 0;
}
