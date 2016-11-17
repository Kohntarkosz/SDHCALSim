#!/bin/bash

g4version=$1

if [[ $g4version == "9.6" ]]
then 

	echo Geant4 9.6 chosen
	
	export LD_LIBRARY_PATH=''

	TOTO=/gridsoft/ipnls/ilc/v01-17-04
	ILCSOFT=/home/ilc/garillot #juste pour que ILCSOFT existe dans le test de while

	while [ $ILCSOFT != $TOTO ]
	do
		source /gridgroup/gridsoft/ipnls/ilc/v01-17-04/init_ilcsoft.sh
		sleep 5
	done

	export SIMDIR=/gridgroup/ilc/garillot/SDHCALSim/bin9.6


elif [[ $g4version == "10.01" ]]
then 

	echo Geant4 10.01 chosen

	export LD_LIBRARY_PATH=''

	TOTO=/gridgroup/gridsoft/ipnls/ilc/v01-17-08
	ILCSOFT=/home/ilc/garillot #juste pour que ILCSOFT existe dans le test de while

	while [ $ILCSOFT != $TOTO ]
	do
		source /gridgroup/gridsoft/ipnls/ilc/v01-17-08/init_ilcsoft.sh
		sleep 5
	done

	export SIMDIR=/gridgroup/ilc/garillot/SDHCALSim/bin10.01


elif [[ $g4version == "10.02" ]]
then 
	echo Geant4 10.02 chosen

	export LD_LIBRARY_PATH=''

	TOTO=/gridgroup/gridsoft/ipnls/ilc/v01-17-08
	ILCSOFT=/home/ilc/garillot #juste pour que ILCSOFT existe dans le test de while

	while [ $ILCSOFT != $TOTO ]
	do
		source /gridgroup/ilc/garillot/init_ilcsoft.sh
		sleep 5
	done

	export SIMDIR=/gridgroup/ilc/garillot/SDHCALSim/bin10.02


else
	echo G4version not valid
fi

