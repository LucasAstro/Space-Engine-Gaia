# Space-Engine-Gaia
Gaia to spacengine! Get space engine at http://www.spaceengine.org/

**If you want premade packs then I recommend Phunnie's post on the Space Engine forums! 
http://forum.spaceengine.org/viewtopic.php?f=3&t=478&p=24288#p24273**

Gaia `.csv` to spacengine! Get space engine at http://www.spaceengine.org/

Download Gaia.exe from here https://github.com/LucasAstro/Space-Engine-Gaia/releases/download/2.01/Gaia.exe

Download the `.csv` file from here https://gea.esac.esa.int/archive/  after making an ADQL request (you can just paste
```SQL
SELECT TOP 500 source_id, (ra/360*24) AS RA, dec, r_est, teff_val, radius_val, phot_g_mean_mag, designation
FROM external.gaiadr2_geometric_distance
JOIN gaiadr2.gaia_source USING (source_id)
WHERE r_est < 7000 AND radius_val > 0 AND lum_val > 0
```
 in here 
 ![Screenshot](https://cdn.discordapp.com/attachments/418486708409991178/509644507520958464/unknown.png)
 
 
If you want to change the distance change `r_est` (It's parsecs!). 
Make sure to change `val_lum` to a "high" value like 2-4 so the stars are bright stars!
And if you want to change the amount of stars change the `500` at the top to however many stars you want to get.

Then download the `.csv` by clicking 
![Screenshot](https://cdn.discordapp.com/attachments/418486708409991178/509645250491449354/chrome_2018-11-07_02-27-54.png) 
Make sure the bar on the bottom says `CSV` and not `VOTable` or anything else.
Put it in the same folder as the .exe file, **rename it to `ram.csv`**. Now run the .exe.
It's gonna output 1 file named `output.csv`, put that in `SpaceEngine/addons/catalogs/stars` and it's done!

