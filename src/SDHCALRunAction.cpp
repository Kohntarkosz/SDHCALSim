#include "SDHCALRunAction.h"
#include "SDHCALRun.h"
#include "SDHCALLcioWriter.h"

#include <globals.hh>

SDHCALRunAction::SDHCALRunAction()
	: G4UserRunAction()
{
	writer = NULL ;
	oldWriter = NULL ;

	lcioFileName = "test.slcio" ;
	rootFileName = "test.root" ;
}

SDHCALRunAction::~SDHCALRunAction()
{

}

G4Run* SDHCALRunAction::GenerateRun()
{
	return new SDHCALRun ;
}

void SDHCALRunAction::BeginOfRunAction(const G4Run*)
{
	writer = new SDHCALLcioWriter( lcioFileName ) ;

	std::stringstream toto ; toto << "Old" << lcioFileName ;
	oldWriter = new SDHCALLcioWriter( toto.str() ) ;

	SDHCALRootWriter* rootWriter = SDHCALRootWriter::Instance() ;
	rootWriter->createRootFile( rootFileName ) ;
}

void SDHCALRunAction::EndOfRunAction(const G4Run*)
{
	SDHCALRootWriter* rootWriter = SDHCALRootWriter::Instance() ;
	rootWriter->closeRootFile() ;

	SDHCALRootWriter::deleteInstance() ;

	if (writer)
		delete writer ;

	if (oldWriter)
		delete oldWriter ;

	writer = NULL ;
	oldWriter = NULL ;
}

