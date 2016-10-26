#include "StepLinkingAlgo.h"

#include <algorithm>
#include <globals.hh>

StepLinkingAlgo::StepLinkingAlgo(std::vector<OldSDHCALHit*>& vec)
{
	inputStepList = vec ;
	LinkStep() ;
}

void StepLinkingAlgo::LinkStep()
{
	std::set< std::vector<OldSDHCALHit*>::iterator > antiDoubleComptSet ;
	for(std::vector<OldSDHCALHit*>::iterator it = inputStepList.begin() ; it != inputStepList.end() ; ++it)
	{
		if( antiDoubleComptSet.find(it) != antiDoubleComptSet.end() )
			continue;
		std::vector<OldSDHCALHit*> hitListToMerge ;
		hitListToMerge.push_back(*it);
		if( !(*it)->isLeaving() )
			for(std::vector<OldSDHCALHit*>::iterator jt = it+1 ; jt != inputStepList.end() ; ++jt)
			{
				if( (*jt)->shouldBeLinkedTo(*it) )
				{
					hitListToMerge.push_back(*jt) ;
					antiDoubleComptSet.insert(jt) ;
					if( (*jt)->isLeaving() )
						break ;
				}
			}
		MergeHitList(hitListToMerge) ;
	}
}

//#define DEBUG
void StepLinkingAlgo::MergeHitList(std::vector<OldSDHCALHit*>& vec)
{
	OldSDHCALHit* hit = ( *vec.begin() ) ;
	if( vec.size() > 1 )
	{
#ifdef DEBUG
		G4cout << "FIRST \t _replicaCopyNumber = " << hit->replicaCopyNumber() << "\t"
			   << "_enteringStep = " << hit->isEntering() << "\t"
			   << "_leavingStep = " << hit->isLeaving() << "\t"
			   << "_trackID = " << hit->trackid() << "\t"
			   << "entrancePoint() = " << hit->entrancePoint() << "\t"
			   << "exitPoint() = " << hit->exitPoint() << G4endl;
		if( !hit->isEntering() && !hit->isLeaving() )
			G4cout << hit->trackVertexVolumeName() << G4endl;
#endif
		for( std::vector<OldSDHCALHit*>::iterator it = vec.begin()+1 ; it != vec.end() ; ++it )
		{
#ifdef DEBUG
			G4cout << "_replicaCopyNumber = " << (*it)->replicaCopyNumber() << "\t"
				   << "_enteringStep = " << (*it)->isEntering() << "\t"
				   << "_leavingStep = " << (*it)->isLeaving() << "\t"
				   << "_trackID = " << (*it)->trackid() << " "
				   << "entrancePoint() = " << (*it)->entrancePoint() << " "
				   << "exitPoint() = " << (*it)->exitPoint() << G4endl;
#endif
			hit->updateWith(*it) ;
		}
	}
	outputStepList.push_back(hit) ;
}

