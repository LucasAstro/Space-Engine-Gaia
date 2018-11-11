#include "pch.h"
#include <iostream>
#include "csv.h"
#include <string>
#include <vector>
#include <math.h>
#include <fstream>


/*
Many thanks to Phunnie for a lot of help with the Python one and reporting bugs! Along with Watsisname for helping me with so much math!
Thanks to JackDole for some bug reporting too
*/


std::string calcsspectral(float temperature) {
	if (temperature <= 3850) {
		return "M";
	}
	if (temperature > 3850 && temperature < 5300) {
			return "K";
	}
	if (temperature > 5300 && temperature <= 5920) {
			return "G";
	}
	if (temperature > 5920 && temperature <= 7240) {
			return "F";
	}
	if (temperature > 7240 && temperature <= 9500) {
			return "A";
	}
	if (temperature > 9500 && temperature <= 31000) {
			return "B";
	}
	if (temperature > 31000) {
		return "O";
	}
}

void csvlinecount(std::string csv_file) {
	int count = 0;

	std::string line;
	std::ifstream file(csv_file);

	while (getline(file, line)) {

		count++;
	}
	file.close();
	std::vector<double> raarray(count - 1);
	std::vector<double> decarray(count - 1);
	std::vector<double> distarray(count - 1);
	std::vector<float> teffarray(count - 1);
	std::vector<float> radiusarray(count - 1);
	std::vector<float> magnitudearray(count - 1);
	std::vector<std::string> designationarray(count - 1);

	io::CSVReader<7> in(csv_file);
	std::ofstream myfile("output.csv");
	int newcount = 0;
	int csvcount = 0;
	in.read_header(io::ignore_extra_column, "ra", "dec", "r_est", "teff_val", "radius_val", "phot_g_mean_mag" /*"radius_val", lum_val,*/, "designation");
	double ra; double dec; double r_est; float teff_val; float radius_val; float phot_g_mean_mag; /*; float lum_val*/ std::string designation;;
	while (in.read_row(ra, dec, r_est, teff_val, radius_val, phot_g_mean_mag /*radius_val, lum_val*/, designation)) {
		csvcount++;
		designationarray[csvcount - 1] = designation;
		raarray[csvcount - 1] = ra;
		decarray[csvcount - 1] = dec;
		distarray[csvcount - 1] = r_est;
		teffarray[csvcount - 1] = teff_val;
		radiusarray[csvcount - 1] = radius_val;
		magnitudearray[csvcount - 1] = phot_g_mean_mag /* = lum_val*/;
		if (myfile.is_open())
		{
			if(csvcount == 1)
			{
				myfile << "Name,RA,Dec,Dist,AppMagn,SpecClass,MassSol,RadSol,Temperature" << std::endl;
			}
			float RAOutput = raarray[csvcount - 1] / 360 * 24;
			/*
			float absolute_magnitude = 4.83 - 2.5 * log10(magnitudearray[csvcount - 1]);
			float apparent_magnitude = absolute_magnitude + 5 * log10(distarray[csvcount - 1]) - 5;
			*/
			myfile << designationarray[csvcount - 1] << "," << RAOutput << "," << decarray[csvcount - 1] << "," << distarray[csvcount - 1] << "," << magnitudearray[csvcount -1] << "," << calcsspectral(teff_val) << (rand() % 9 + 1) << "V" << "," << "," << radiusarray[csvcount - 1] << "," << teff_val << std::endl;
			newcount++;
			std::cout << newcount << std::endl;	
		}


	}
	
	myfile.close();
	std::cout << "Completed" << std::endl;
	std::cin.ignore();
}

int main() 
{
	csvlinecount("ram.csv");
	return 0;
}
