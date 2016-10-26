#include "SDHCALRunAction.h"
#include "SDHCALRun.h"
#include "SDHCALLcioWriter.h"

#include <globals.hh>

SDHCALRunAction::SDHCALRunAction()
	: G4UserRunAction()
{
	writer = NULL ;
	oldWriter = NULL ;
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
	writer = new SDHCALLcioWriter("test.slcio") ;
	oldWriter = new SDHCALLcioWriter("testOld.slcio") ;

	SDHCALRootWriter* rootWriter = SDHCALRootWriter::Instance() ;
	rootWriter->createRootFile("test.root") ;
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

