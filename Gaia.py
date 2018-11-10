import os
import math
import random
import astropy
import numpy
from astropy.io.votable import parse
from astropy.coordinates import ICRS
from astropy import units as u
myinput = input("What is the file you want to read" + "(" + "must have .vot in the name!" + ")\n")
dirpath = os.getcwd()

votable = parse(myinput)
newpath = str(dirpath + "\\outputsc")
if os.path.exists(newpath):
    os.chdir(newpath)
if not os.path.exists(newpath):
    os.makedirs(newpath)
    os.chdir(newpath)
if(os.path.isfile(newpath + "\\outputsc.csv")):
    os.remove("outputsc.csv")
       
# Credit goes to Watsisname, and Grote for a few bits of code and help with some equations!
# Also, thanks to Phunnie for some help too!
# Thanks to DominikDoom too for some enhancements!
def calcsspectral(temperature):
    if(temperature <= 3850):
        return "M"
    if(temperature > 3850):
        if(temperature <= 5300):
            return "K"
    if(temperature > 5300):
        if(temperature <= 5920):
            return "G"
    if(temperature > 5920):
        if(temperature <= 7240):
            return "F"
    if(temperature > 7240):
        if(temperature <= 9500):
            return "A"
    if(temperature > 9500):
        if(temperature <= 31000):
            return "B"
    if(temperature > 31000):
            return "O"
numRow = 0
for table in votable.iter_tables():
    idss = 0
    arrayID = table.array['designation']

    for i in arrayID:
        numRow = numRow + 1
        print(str(numRow) + ' / ' + str(len(arrayID)), end='\r')
        with open("outputsc" + ".csv", 'a+') as file:
            if idss == 0:
                idss = 1
                
                file.write("Name,RA,Dec,Dist,AppMagn,SpecClass,MassSol,RadSol,Temperature\n")
            arrayRA = table.array['ra']
            
            arrayID = table.array['designation']

            arrayDEC = table.array['dec']
            
            c = ICRS(arrayRA[numRow-1]*u.degree, arrayDEC[numRow-1]*u.degree)
            
            rahmsstr = c.ra.to_string(u.hour)
            decdmsstr = str(arrayDEC[numRow-1])
            arraydist = table.array['r_est']
            arrayDesignation = table.array['designation']
            designation = arrayDesignation.astype(str)
            distance = arraydist[numRow-1]
            
            arrayTeff = table.array['teff_val']
                
            arrayRadSol = table.array['radius_val']

            arrayLum = table.array['lum_val']
            teffoutput = str(arrayTeff[numRow-1])

            radsoloutput = str(arrayRadSol[numRow-1])
            
            Lumoutput = str(arrayLum[numRow-1])

            designationoutput = str(designation[numRow-1])
            rahoutput = str(rahmsstr)
            
            rahoutput = rahoutput.replace("h", " ")
            rahoutput = rahoutput.replace("m", " ")
            rahoutput = rahoutput.replace("s", "")
            
            decoutput = str(decdmsstr)

            decoutput = decoutput.replace("d", " ")
            decoutput = decoutput.replace("m", " ")
            decoutput = decoutput.replace("+", "")
            decoutput = decoutput.replace("s", "")
            absolute_magnitude = 4.83 - 2.5 * math.log10(float(Lumoutput))
            apparent_magnitude = absolute_magnitude + 5 * math.log10(float(distance)) - 5
            file.write(str(designationoutput) + "," + str(rahoutput) + "," + str(decoutput) + "," + str(distance) + "," + str(apparent_magnitude) + "," + str(calcsspectral(float(teffoutput)) + str(random.randrange(1,9)) + "V") + "," + "," + str(radsoloutput) + "," + str(teffoutput) + "\n")
            
        os.path.join(newpath, str(numRow) + ".csv")
print("\nCompleted!")
