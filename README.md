# Space-Engine-Gaia
Gaia to spacengine! Get space engine at http://www.spaceengine.org/
Use
```SQL
SELECT source_id, ra, dec, phot_g_mean_mag, r_est, r_lo, r_hi, teff_val, radius_val, lum_val, astrometric_weight_al
FROM external.gaiadr2_geometric_distance
JOIN gaiadr2.gaia_source USING (source_id)
WHERE r_est < 7000 AND radius_val > 0 AND lum_val > 0
AND source_id < 2251799813685248
```
At https://gea.esac.esa.int/archive/
("Advanced (ADQL)")
Change r_est for the distance! Save it as "result.vot" and put it where you downloaded the .py.
**Make sure you make a new folder cause it makes a *lot* of new files! (However many rows there are, so a few thousand in that snippet)**
Put the .sc files in `addons\catalogs\stars`
Success! All the stars now show up. The names are the numbers they are row for now.
