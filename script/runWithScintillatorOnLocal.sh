#!/bin/bash

particle=$1
energy=$2
nevent=$3
seed=$4
model=$5

source /home/garillot/ilcsoft/v01-17-08/init_ilcsoft.sh

export SIMEXE=/home/garillot/SDHCALSim2/bin/SDHCALSimWithScintillator

source /home/garillot/SDHCALSim2/script/run.sh ${particle} ${energy} ${nevent} ${seed} ${model}

mv wScintillator.slcio /home/garillot/files/local/SimCalorimeterHit/WithScintillator/Geant4.10.01/${model}/single_${particle}_${energy}GeV_I${seed}.slcio
mv wScintillator.root /home/garillot/files/local/SimCalorimeterHit/WithScintillator/Geant4.10.01/${model}/ControlFiles/single_${particle}_${energy}GeV_I${seed}.root

rm OldwScintillator.slcio
