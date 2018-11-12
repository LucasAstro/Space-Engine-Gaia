
#include "stdafx.h"
#include <iostream>
#include "csv.h"
#include <time.h>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>


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

int csvlinecount(std::string csv_file) {
	int count = 0;

	srand(time(NULL));

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
	std::vector<double> parallaxarray(count - 1);
	std::vector<double> parralax_errorarray(count - 1);

	io::CSVReader<9> in(csv_file);
	std::ofstream myfile("output.csv");
	int newcount = 0;
	int csvcount = 0;
	in.read_header(io::ignore_extra_column, "ra", "dec", "r_est", "teff_val", "radius_val", "phot_g_mean_mag" /*"radius_val", lum_val,*/, "designation", "parallax", "parallax_error");
	double ra; double dec; double r_est; float teff_val; float radius_val; float phot_g_mean_mag; /*; float lum_val*/ std::string designation; double parallax; double parallax_error;
	while (in.read_row(ra, dec, r_est, teff_val, radius_val, phot_g_mean_mag /*radius_val, lum_val*/, designation, parallax, parallax_error)) {
		csvcount++;
		designationarray[csvcount - 1] = designation;
		raarray[csvcount - 1] = ra;
		decarray[csvcount - 1] = dec;
		distarray[csvcount - 1] = r_est;
		teffarray[csvcount - 1] = teff_val;
		radiusarray[csvcount - 1] = radius_val;
		magnitudearray[csvcount - 1] = phot_g_mean_mag /* = lum_val*/;
		parallaxarray[csvcount - 1] = parallax;
		parralax_errorarray[csvcount - 1] = parallax_error;
		
		if (myfile.is_open())
		{
			if (csvcount == 1)
			{
				myfile << "Name,RA,Dec,Dist,AppMagn,SpecClass,MassSol,RadSol,Temperature" << std::endl;
			}
			double parallaxpercentage = parallax * parallax_error / 100;
			
			
			if (parallaxpercentage > 10)
			{
				std::cout << parallaxpercentage << " " << parallax_error << std::endl;
				break;
			}
			else if (parallaxpercentage < 10)
			{

				myfile << designationarray[csvcount - 1] << "," << raarray[csvcount - 1] << "," << decarray[csvcount - 1] << "," << distarray[csvcount - 1] << "," << magnitudearray[csvcount - 1] << "," << calcsspectral(teff_val) << (rand() % 9 + 1) << "V" << "," << "," << radiusarray[csvcount - 1] << "," << teff_val << std::endl;
				newcount++;
			}
		}


	}

	myfile.close();
	std::cin.ignore();
	return 0;
}

int main()
{
	std::string inputfile;
	std::cin >> inputfile;
	csvlinecount(inputfile);
}
