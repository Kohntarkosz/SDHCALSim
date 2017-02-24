#!/usr/bin/env python

import os
import SDHCALSim

import math

import gfal2

import sys
from os import path
import time

def upload(input , output) :

	# Instantiate gfal2
	ctx = gfal2.creat_context()

	# Set transfer parameters
	params = ctx.transfer_parameters()
	params.overwrite = True
	params.timeout = 300

	dlCounter = 0
	isOK = False

	print 'Try to Upload ' + input
	while not isOK and dlCounter < 50 :
		source = input
		destination = output
		try:
			r = ctx.filecopy(params, source, destination)
			isOK = True
		except Exception, e:
			print "Upload failed : %s" % str(e)
			isOK = False
			time.sleep(20)

		dlCounter = dlCounter + 1

	if isOK :
		print 'Upload succeeded !'
	else :
		print 'Upload failed !'
		sys.exit(1)




if __name__ == '__main__' :

	if len(sys.argv) != 5 :
		sys.exit('Error : wrong number of arguments')

	particle = 'e-'
	energy = sys.argv[1]
	nEvent = sys.argv[2]
	seed = sys.argv[3]
	physicsList = sys.argv[4]
	g4version = '9.6'

	os.environ["SIMEXE"] = '/gridgroup/ilc/garillot/SDHCALSim/bin' + g4version + '/SDHCALSim'

	params = SDHCALSim.Params()

	params.particle = particle
	params.energy = energy
	params.nEvent = nEvent
	params.physicsList = physicsList

	params.nEvent = nEvent
	params.seed = seed

	params.momentumOption = "gaus"
	params.sigmaMomentum = 0.15

	params.positionOption = "gaus"
	params.positionX = -100
	params.positionY = 10
	params.sigmaPos = 50 

	SDHCALSim.launch( params )

	outputDir = 'srm://lyogrid06.in2p3.fr/dpm/in2p3.fr/home/calice/garillot/SimCalorimeterHit/ElectronsForTuning/Geant4.' + g4version + '/' + physicsList
	outputFile = 'single_' + particle + '_' + energy + 'GeV' + '_I' + seed 

	upload('file:Test.slcio' , outputDir + '/' + outputFile + '.slcio')
	upload('file:Test.root' , outputDir + '/ControlFiles/' + outputFile + '.root')

	os.system('rm Test.slcio OldTest.slcio Test.root')




