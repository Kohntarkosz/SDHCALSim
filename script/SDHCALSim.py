#!/usr/bin/env python

import os

class Params :
	def __init__(self) :
		self.particle = "mu-"
		self.physicsList = "FTFP_BERT"

		self.nEvent = 100
		self.seed = 0

		self.positionOption = "fixed"       #fixed uniform gaus cosmic
		self.positionX = 0                  #0 is calorimeter center
		self.positionY = 0
		self.positionZ = -20                #0 is calorimeter begin
		self.uniformDeltaPos = 0            #if uniform
		self.sigmaPos = 0                   #if gaus

		self.momentumOption = "fixed"       #fixed gaus
		self.momentumPhi = 0                #
		self.momentumTheta = 0              #
		self.sigmaMomentum = 0.0            #if gaus

		self.energyDistribution = "fixed"   #fixed gaus uniform forNN
		self.energy = 50                    #if fixed or gaus
		self.sigmaEnergy = 0                #if gaus
		self.minEnergy = 1                  #if uniform or forNN
		self.maxEnergy = 120                #if uniform or forNN


def launch(a) :

	pid = os.getpid()
	macFileName = str(pid) + '.mac'

	macFileContent = '''
/GunParameter/Particle ''' + a.particle + '''

/GunParameter/PositionOption ''' + a.positionOption + '''
/GunParameter/PositionX ''' + str(a.positionX) + '''
/GunParameter/PositionY ''' + str(a.positionY) + '''
/GunParameter/PositionZ ''' + str(a.positionZ) + '''
/GunParameter/UniformDeltaPosition ''' + str(a.uniformDeltaPos) + '''
/GunParameter/GausSigmaPosition ''' + str(a.sigmaPos) + '''

/GunParameter/MomentumOption ''' + a.momentumOption + '''
/GunParameter/MomentumSigma ''' + str(a.sigmaMomentum) + '''
/GunParameter/MomentumPhi ''' + str(a.momentumPhi) + '''
/GunParameter/MomentumTheta ''' + str(a.momentumTheta) + '''

/GunParameter/EnergyDistribution ''' + a.energyDistribution + '''
/GunParameter/Energy ''' + str(a.energy) + '''
/GunParameter/SigmaEnergy ''' + str(a.sigmaEnergy) + '''
/GunParameter/MinEnergy ''' + str(a.minEnergy) + '''
/GunParameter/MaxEnergy ''' + str(a.maxEnergy) + '''

/run/beamOn ''' + str(a.nEvent) + '''
	'''

	macFile = open(macFileName , 'w')
	macFile.write(macFileContent)
	macFile.close()


	simuExe = os.environ["SIMEXE"]

	os.system(simuExe + ' ' + macFileName + ' ' + str(a.seed) + ' ' + str(a.physicsList))

	os.system('rm ' + macFileName)

