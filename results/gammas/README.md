These simulations have the following structure :

Gammas from a GPS source are shot with a cone distribution towards a scintillator,
the energy deposit is saved and used to make a histogram directly with Geant4.

The "edep.csv" files are the energy deposit histograms made with Geant. It is to be noted
that Geant4 automatically adds one extra bin at the beginning and at the end of the bins.

The "edep_photons.csv" files are energy deposit histograms where the energy deposit was
computed based on the number of scintillation and Cerenkov photons created.

The "data.csv" files are stripped versions of the "edep.csv" files where the first value
is the upper bound of the histogram bin (the bins are 5 keV) and the second value is the count

The "run.mac" files are the macro files that were used to run the simulation. Note that the only thing that changes is the gamma energy

The plots compare the energy deposit value (label: edep) and the edep value computed by using the number of photons (label: nPhotons)
