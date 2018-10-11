import zipfile
import os
import shutil
from astropy.io.votable import parse
from astropy.coordinates import ICRS
from astropy import units as u

import numpy
cwd = os.getcwd()
whichline = 0
# Credit goes to Watsisname for help with a lot of equations!
votable = parse("result.vot")
file = open("yet" + ".txt", 'w+')
for resource in votable.resources:
    for table in resource.tables:
        arrayID = table.array['source_id']
        indivID = numpy.split(arrayID, len(arrayID))
        for i in indivID:
            whichline = whichline + 1
            print(str(whichline) + "/" + "5995")
            file = open(str(whichline) + ".sc", 'w+')
            arrayRA = table.array['ra']
            indivRA = numpy.split(arrayRA, len(arrayRA))
            
            arrayID = table.array['source_id']
            indivID = numpy.split(arrayID, len(arrayID))

            arrayDEC = table.array['dec']
            indivDEC = numpy.split(arrayDEC, len(arrayDEC))
            
            c = ICRS(indivRA[whichline-1]*u.degree, indivDEC[whichline-1]*u.degree)
            
            rahmsstr = c.ra.to_string(u.hour)
            decdmsstr = c.dec.to_string(u.degree, alwayssign=True)
            arraydist = table.array['r_est']
            distance = arraydist[whichline-1]
            
            arrayTeff = table.array['teff_val']
            indivTeff = numpy.split(arrayTeff,len(arrayTeff))

            arrayRadSol = table.array['radius_val']
            indivRadSol = numpy.split(arrayRadSol, len(arrayRadSol))

            arrayLum = table.array['lum_val']
            indivLum = numpy.split(arrayLum, len(arrayLum))
            teffoutput = str(indivTeff[whichline-1])

            teffoutput = teffoutput.replace("[", "")
            teffoutput = teffoutput.replace("]", "")

            radsoloutput = str(indivRadSol[whichline-1])

            radsoloutput = radsoloutput.replace("[", "")
            radsoloutput = radsoloutput.replace("]", "")

            Lumoutput = str(indivLum[whichline-1])

            Lumoutput = Lumoutput.replace("[", "")
            Lumoutput = Lumoutput.replace("]", "")

            rahoutput = numpy.array_str(rahmsstr)
            
            rahoutput = rahoutput.replace("h", " ")
            rahoutput = rahoutput.replace("m", " ")
            rahoutput = rahoutput.replace("s", "")
            rahoutput = rahoutput.replace("[", "")
            rahoutput = rahoutput.replace("]", "")
            rahoutput = rahoutput.replace("'", "")
            
            decoutput = numpy.array_str(decdmsstr)
            
            decoutput = decoutput.replace("d", " ")
            decoutput = decoutput.replace("m", " ")
            decoutput = decoutput.replace("+", "")
            decoutput = decoutput.replace("s", "")
            decoutput = decoutput.replace("[", "")
            decoutput = decoutput.replace("]", "")
            decoutput = decoutput.replace("'", "")
            file.write("Star" + "\t" + '"' + str(whichline-1) + '"' + "\n{")
           
            file.write("\n \t \tRA " + str(rahoutput))
            file.write("\n \t \tDec " + str(decoutput))            
            file.write("\n \t \tDist " + str(distance))
            file.write("\n \t \tClass  " + '"' + "G5V" + '"')
            file.write("\n \t \tLum " + Lumoutput)
            file.write("\n \t \tRadSol " + radsoloutput)
            file.write("\n \t \tMassSol " + "1")
            file.write("\n \t \tTeff " + teffoutput)
            file.write("\n \t")
            file.write("\n}")
            file.close()
        pass
