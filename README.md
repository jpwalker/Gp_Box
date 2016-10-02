# Gp_Box Project

This code calculates the geometric factor G_p(r) used in Landy & Szalay 1993 
(http://adsabs.harvard.edu/doi/10.1086/172900). The geometric factor is 
normalized to 1 and assumes a N-body box simulation with periodic boundary 
conditions. When calculating DD, periodic boundary conditions should also be 
used.

Required Libaries:
GNU Scientific Library GSL_histogram.h
GLib glib.h

You should use pkg-config to obtain the correct lib and cflags.

After compiling, the software can be tested with test.py.

Use Gp_Box --help-all for syntax information

Jean P. Walker-Soler (jpwalker@physics.rutgers.edu)
