**_DOWNLOAD THE C++ VERSION, THIS IS HERE FOR ARCHIVE'S SAKE_**

Gaia .vot to spacengine! Get space engine at http://www.spaceengine.org/

Download Gaia.py from here https://github.com/LucasAstro/Space-Engine-Gaia/releases/download/1.01/Gaia.py

Remember you need python 3, and pip, if you have those setup run `pip install astropy` or `python -m pip install astropy`


Download the .vot file from here https://gea.esac.esa.int/archive/  after making an ADQL request (you can just paste
```SQL
SELECT TOP 500 source_id, ra, dec, r_est, teff_val, radius_val, lum_val, designation
FROM external.gaiadr2_geometric_distance
JOIN gaiadr2.gaia_source USING (source_id)
WHERE r_est < 7000 AND radius_val > 0 AND lum_val > 0
```
 in here 
 ![Screenshot](https://cdn.discordapp.com/attachments/418486708409991178/509644507520958464/unknown.png)
 
 
If you want to change the distance change `r_est` (It's parsecs!). 
Make sure to change `val_lum` to a "high" value like 2-4 so the stars are bright stars!
And if you want to change the amount of stars change the `500` at the top to however many stars you want to get.

Then download the votable by clicking 
![Screenshot](https://cdn.discordapp.com/attachments/418486708409991178/509645250491449354/chrome_2018-11-07_02-27-54.png) 
Make sure the bar on the bottom says `VOTable` and not `VOTable (plain)` or anything else.
Put it in the same folder as the .py file. Now run the .py.
It's gonna ask you what the name of the file is and just copy the file name into console and add .vot if it's not there already.
It's gonna output 1 file in outputsc, put that in `SpaceEngine/addons/catalogs/stars` and it's done!

**_DOWNLOAD THE C++ VERSION, THIS IS HERE FOR ARCHIVE'S SAKE_**
