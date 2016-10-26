#ifndef SDHCALRunAction_h
#define SDHCALRunAction_h

#include <globals.hh>
#include <G4UserRunAction.hh>

#include "SDHCALLcioWriter.h"
#include "SDHCALRootWriter.h"

#include <string>


class G4Run ;

class SDHCALRunAction : public G4UserRunAction
{
	public :
		SDHCALRunAction() ;
		virtual ~SDHCALRunAction() ;

		G4Run* GenerateRun() ;

		virtual void BeginOfRunAction(const G4Run*) ;
		virtual void EndOfRunAction(const G4Run*) ;

		inline SDHCALLcioWriter* getWriter() const { return writer ; }
		inline SDHCALLcioWriter* getOldWriter() const { return oldWriter ; }

	protected :
		SDHCALLcioWriter* writer ;
		SDHCALLcioWriter* oldWriter ;

} ;

#endif //SDHCALRunAction_h

