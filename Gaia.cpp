#include "pch.h"
#include <iostream>
#include "csv.h"
#include <string>
#include <vector>
#include <math.h>
#include <chrono>
#include <fstream>
typedef std::chrono::high_resolution_clock Clock;

std::string calcsspectral(float temperature) {
	if (temperature <= 3850) {
		return "M";
	}
	if (temperature > 3850) {
		if (temperature <= 5300)
		{
			return "K";
		}
	}
	if (temperature > 5300) {
		if (temperature <= 5920) {
			return "G";
		}
	}
	if (temperature > 5920) {
		if (temperature <= 7240) {
			return "F";
		}
	}
	if (temperature > 7240) {
		if (temperature <= 9500) {
			return "A";
		}
	}
	if (temperature > 9500) {
		if (temperature <= 31000) {
			return "B";
		}
	}
	if (temperature > 31000) {
		return "O";
	}
}

int csvlinecount(std::string csv_file) {
	auto t1 = Clock::now();
	int count = 0;

	std::string line;
	std::ifstream file(csv_file);

	while (getline(file, line)) {

		count++;
	}
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
	in.read_header(io::ignore_extra_column, "ra", "dec", "r_est", "teff_val", "radius_val", "phot_g_mean_mag", "designation");
	double ra; double dec; double r_est; float teff_val; float radius_val; float phot_g_mean_mag; std::string designation;;
	while (in.read_row(ra, dec, r_est, teff_val, radius_val, phot_g_mean_mag, designation)) {
		csvcount++;
		designationarray[csvcount - 1] = designation;
		raarray[csvcount - 1] = ra;
		decarray[csvcount - 1] = dec;
		distarray[csvcount - 1] = r_est;
		teffarray[csvcount - 1] = teff_val;
		radiusarray[csvcount - 1] = radius_val;
		magnitudearray[csvcount - 1] = phot_g_mean_mag;
		if (myfile.is_open())
		{
			if(csvcount == 1)
			{
				myfile << "Name,RA,Dec,Dist,AppMagn,SpecClass,MassSol,RadSol,Temperature" << std::endl;
			}
			float RAOutput = raarray[csvcount - 1] / 360 * 24;
			myfile << designationarray[csvcount - 1] << "," << RAOutput << "," << decarray[csvcount - 1] << "," << distarray[csvcount - 1] << "," << magnitudearray[csvcount -1] << "," << calcsspectral(teff_val) << (rand() % 10 + 1) << "V" << "," << "," << radiusarray[csvcount - 1] << "," << teff_val << std::endl;
			newcount++;
			std::cout << newcount << std::endl;	
		}


	}
	
	myfile.close();
	auto t2 = Clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() << std::endl;
	std::cin.ignore();
	return 0;
}

int main() 
{
	std::string input;
	std::cout << "What is the input file?";
	std::cin >> input;
	csvlinecount(input);
}
