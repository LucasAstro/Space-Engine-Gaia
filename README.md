# Space-Engine-Gaia
Gaia `.vot` to spacengine! Get space engine at http://www.spaceengine.org/
Use
```SQL
SELECT TOP 500 source_id, ra, dec, r_est, teff_val, radius_val, lum_val
FROM external.gaiadr2_geometric_distance
JOIN gaiadr2.gaia_source USING (source_id)
WHERE r_est < 7000 AND radius_val > 0 AND lum_val > 0
```
At https://gea.esac.esa.int/archive/
("Advanced (ADQL)")
Change r_est for the distance! Save it as "result.vot" and put it where you downloaded the .py.
**SC Files are outputted in "outputsc" folder!**
Put the .sc files in `addons\catalogs\stars`
Success! All the stars now show up. The names are the numbers they are row for now.
