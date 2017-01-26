#!/bin/bash

particle=$1
energy=$2
nevent=$3
seed=$4
model=$5

GunOptionPosition=uniform  #fixed uniform gaus cosmic
GunPosX=0                  #0 is Calorimeter center
GunPosY=0
UniformDeltaPos=500        #used if GunOptionPosition == uniform
SigmaPos=20                #used if GunOptionPosition == gaus

GunOptionMomentum=gaus     #fixed gaus
GunMomPhi=0
GunMomTheta=0
SigmaMom=0.1               #used if GunOptionMomentum == gaus

EnergyDistribution=fixed   #fixed gaus uniform forNN
Energy=$energy             #used if EnergyDistribution == fixed or gaus
SigmaEnergy=0              #used if EnergyDistribution == gaus
MinEnergy=1                #used if EnergyDistribution == uniform or forNN
MaxEnergy=120              #used if EnergyDistribution == uniform or forNN

echo "Physics list : "$model
echo "Energy : "$energy" GeV"
echo "Particle : "$particle
echo "Nevent : "$nevent

MACFILENAME=$$.mac

cat > ${MACFILENAME} <<EOF

/GunParameter/Particle $particle

/GunParameter/PositionOption $GunOptionPosition
/GunParameter/PositionX $GunPosX
/GunParameter/PositionY $GunPosY
/GunParameter/UniformDeltaPosition $UniformDeltaPos
/GunParameter/GausSigmaPosition $SigmaPos

/GunParameter/MomentumOption $GunOptionMomentum
/GunParameter/MomentumSigma $SigmaMom

/GunParameter/EnergyDistribution $EnergyDistribution
/GunParameter/Energy $Energy

/run/beamOn $nevent

EOF

${SIMEXE} ${MACFILENAME} ${seed} ${model}
rm ${MACFILENAME}

