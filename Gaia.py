import numpy
import astropy
import os
from astropy.io.votable import parse
from astropy.coordinates import ICRS
from astropy import units as u
myinput = input("What is the file you want to read" + "(" + "must have .vot in the name!" + ")")
dirpath = os.getcwd()

votable = parse(myinput)
newpath = str(dirpath + "\\outputsc")
if os.path.exists(newpath):
    os.chdir(newpath)
if not os.path.exists(newpath):
    os.makedirs(newpath)
    os.chdir(newpath)
# Credit goes to Watsisname and Grote for a few bits of code and help with some equations
numRow = 0
for table in votable.iter_tables():
    arrayID = table.array['source_id']
    for i in arrayID:
        numRow = numRow + 1
        print(str(numRow) + ' / ' + str(len(arrayID)), end='\r')
        with open(str(numRow) + ".sc", 'w+') as file:
            arrayRA = table.array['ra']
            
            arrayID = table.array['source_id']

            arrayDEC = table.array['dec']
            
            c = ICRS(arrayRA[numRow-1]*u.degree, arrayDEC[numRow-1]*u.degree)
            
            rahmsstr = c.ra.to_string(u.hour)
            decdmsstr = str(arrayDEC[numRow-1])
            arraydist = table.array['r_est']
            distance = arraydist[numRow-1]
            
            arrayTeff = table.array['teff_val']

            arrayRadSol = table.array['radius_val']

            arrayLum = table.array['lum_val']
            teffoutput = str(arrayTeff[numRow-1])


            radsoloutput = str(arrayRadSol[numRow-1])
            
            Lumoutput = str(arrayLum[numRow-1])


            rahoutput = str(rahmsstr)
            
            rahoutput = rahoutput.replace("h", " ")
            rahoutput = rahoutput.replace("m", " ")
            rahoutput = rahoutput.replace("s", "")
            
            decoutput = str(decdmsstr)
            
            decoutput = decoutput.replace("d", " ")
            decoutput = decoutput.replace("m", " ")
            decoutput = decoutput.replace("+", "")
            decoutput = decoutput.replace("s", "")
            file.write("Star" + "\t" + '"' + str(numRow-1) + '"' + "\n{"
                      + "\n \t \tRA " + rahoutput + 
                      "\n \t \tDec " + decoutput + 
                     "\n \t \tDist " + str(distance) + 
                     "\n \t \tClass  " + '"' + "G5V" + '"' + 
                     "\n \t \tLum " + Lumoutput + 
                     "\n \t \tRadSol " + radsoloutput + 
                     "\n \t \tMassSol 1" + 
                     "\n \t \tTeff " + teffoutput + 
                     "\n \t" + "\n}")
        os.path.join(newpath, str(numRow) + ".sc")
print("\nCompleted!")
