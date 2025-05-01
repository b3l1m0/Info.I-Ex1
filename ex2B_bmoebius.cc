/*
Student name    : Bente Moebius
Username	    : bmoebius
Date		    : 17.10.2024
Task 		    : B
Time required	: 1 hour
Program Description:
This program puts out sequence of values based on user input. 
The user can put in a Temperature, two volumes, a number of steps and the model (ideal or real), with which the values 
will be calculated. If these given values are not realistic, this program will give an error message. Then it will check
the model which was selected and based on that and the given values, this program computes in a for loop (number of 
equidistant steps) for each volume the pressure. At the end of the loop these values are printed out in two columns 
"Volume" and "Pressure".
My results are realistic and i think that the program is understandably written. 
Short report: 
A. The largest change happens at a low volume, it is then observed that the Pressure calculated using the model of a real 
gas is higher than that calculated using the model of an ideal gas. This is because of the factors a and b the number of 
effective collisions is increased (the volume is less because the molecules use up relatively more volume and the 
interactions are far more because the molecules are packed more tightly.) 
B. The biggest change observed is at 200 K. This is because, regarding the formula, the smaller Temperature is relatively 
much more prone to the deduction of (a * 1/V²) and at higher temperatures, this does not change much about the first 
calculated value, because of the scale.  
C. This is because, at a specific volume it is physically not possible to compress the gas anymore that it already is 
(without inducing nuclear fusion) because this is near the volume taken up by the molecules and also the interactions get 
near infinitely big, which is also not realistic. This volume can be specified as: V_0 > nb + i (with i > 0 but infinitely 
small) and nRT/(V_0-nb) = a*n²/V² = 0
D. This is not physically possible and can therefore be discarded. In reality there would still be a small pressure 
because as long as there are molecules inside of the given volume there will be coincidental and accidental collisions as 
the molecules move.
*/

#include <iostream>
#include <iomanip>
using namespace std;
int main () {
	// declaration (and initialization) of the variables used
	const double R_si = 8.314;
	double a_si = 0.425;
	double b_si = 5.105E-5;
	double n_gas = 1;
	// calculation: R_si J/Kmol * 1 mol (J/K -> kg m2 / s2) * 1000 dm3/m3 * E-5 (bar dm3 / K)
	const double R_cst = R_si * n_gas * 1E3 * 1E-5;
	// calculation: a_si Jm3/mol2 * (1 mol)² * (Jm3 -> kg m5 / s2) (1000 dm3/m3)² * E-5 (Pa to bar)
	const double a_cst = a_si * n_gas * n_gas * 1000 * 1000 * 1E-5;
	// calculation: b_si m3/mol * 1000 dm3/m3 * 1 mol
	const double b_cst = b_si * 1000;
	double T_ref, V_min, V_max;
	int N_step, S_vdw;
	
	// get input and initialize variables
	cout << "# Please enter T_ref in K: " << endl;
	cin >> T_ref; 
	
	cout << "# Please enter V_min in dm3: " << endl;
	cin >> V_min; 
	
	cout << "# Please enter V_max in dm3: " << endl;
	cin >> V_max;
	
	cout << "# Please enter N_step in dm3: " << endl;
	cin >> N_step;
	
	cout << "# Please enter S_vdw (0 = ideal, 1 = real): " << endl;
	cin >> S_vdw ; 
	
	// check if everything is realistic
	if (0 <= T_ref && 0 < V_min && V_min <= V_max && N_step >= 1) {
			
		// print the type of law applied
		// if S_vdw is 1 then it calculates the pressure based on the model an a real gas
		if (S_vdw == 1) {
		cout << "# Values of V in dm3 and P in bar for one mole of real gas: " << endl;
		
		// for loop to calculate the values and print them into rows
		int n_step;
		for (n_step = 0; n_step <= N_step-1; n_step++) {
			
			// calculate V 
			double V;
			if (V_min == V_max)  {V = V_min;
			} else {
			V = V_min + (double) n_step * ((V_max - V_min)/ ((double) N_step -1));
			}
			// calculate P (P = nRT/V)
			double P = (R_cst * T_ref) / (V - b_cst) - a_cst * (1 / V * V);
			
			// print the values of V and P in two coluns separated by " "
			cout << V << " "; 
			cout << P << endl;
		}
		// If S_vdw = 0 it calculates based on the model of an ideal gas 
		} else if (S_vdw == 0){
		cout << "# Values of V in dm3 and P in bar for one mole of ideal gas: " << endl;
		
		// for loop to calculate the values and print them into rows
		int n_step;
		for (n_step = 0; n_step <= N_step-1; n_step++) {
			
			// calculate V 
			double V;
			if (V_min == V_max)  {V = V_min;
			} else {
			V = V_min + (double) n_step * ((V_max - V_min)/ ((double) N_step -1));
			}
			// calculate P (P = nRT/V)
			double P = (R_cst * T_ref) / V;
			
			// print the values of V and P in two columns separated by " "
			cout << V << " "; 
			cout << P << endl;
		}
		}
	// if the data does not make sense, print an error message	
	} else cout << "Error: unrealistic expectations" << endl; 
	
	return 0;
}
