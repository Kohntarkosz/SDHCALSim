#!/usr/bin/env python

import os
import sys
import SDHCALSim

import math




if __name__ == '__main__' :

	os.environ["SIMEXE"] = '/home/garillot/SDHCALSim2/bin/SDHCALSim'

	params = SDHCALSim.Params()

	params.particle = "e-"
	params.physicsList = "QGSP_BERT_HP"
	params.energy = sys.argv[1]
	params.nEvent = 4000
	params.seed = 0

	params.momentumOption = "gaus"
	params.sigmaMomentum = 0.15

	params.positionOption = "gaus"
	params.positionX = -100
	params.positionY = 10
	params.sigmaPos = 33 

	SDHCALSim.launch( params )

	os.system('rm Oldtest.slcio')

	outputFile = 'single_' + params.particle + '_' + str(params.energy) + 'GeV' + '_I' + str(params.seed) 

	os.system('mv test.slcio /home/garillot/files/local/SimCalorimeterHit/Geant4.10.01/' + params.physicsList + '/' + outputFile + '.slcio')
	os.system('mv test.root /home/garillot/files/local/SimCalorimeterHit/Geant4.10.01/' + params.physicsList + '/ControlFiles/' + outputFile + '.root')
