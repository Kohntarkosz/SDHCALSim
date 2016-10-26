#ifndef StepLinkingAlgo_h
#define StepLinkingAlgo_h

#include <iostream>
#include <vector>
#include <map>

#include "SDHCALHit.h"
#include <set>

class StepLinkingAlgo
{
	public :
		StepLinkingAlgo(std::vector<OldSDHCALHit*> &vec) ;
		virtual ~StepLinkingAlgo() { ; }

		void LinkStep() ;
		void MergeHitList(std::vector<OldSDHCALHit*> &vec) ;
		inline std::vector<OldSDHCALHit*>& getLinkedStepList() { return outputStepList ; }

	protected :
		std::vector<OldSDHCALHit*> inputStepList ;
		std::vector<OldSDHCALHit*> outputStepList ;

} ;

#endif
