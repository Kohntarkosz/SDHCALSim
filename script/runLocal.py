#!/usr/bin/env python

import os
import SDHCALSim

import math

os.environ["SIMEXE"] = '/home/garillot/SDHCALSim2/bin/SDHCALSim'

params = SDHCALSim.Params()

params.particle = "e-"
params.energy = 20
params.nEvent = 1000

params.momentumOption = "gaus"
params.sigmaMomentum = 0.15

params.positionOption = "gaus"
params.positionX = -100
params.positionY = 10
params.sigmaPos = 50 

SDHCALSim.launch( params )

