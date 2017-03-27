#include "SDHCALEventAction.h"

#include "SDHCALRun.h"

#include <G4RunManager.hh>

SDHCALEventAction::SDHCALEventAction(SDHCALRunAction* _runAction)
	: G4UserEventAction()
{
	runAction = _runAction ;
	nEventsProcessed = 0 ;
	averageTime = 0 ;
}


SDHCALEventAction::~SDHCALEventAction()
{
}

void SDHCALEventAction::BeginOfEventAction(const G4Event* event)
{
	beginClock = clock() ;

	SDHCALSteppingAction::Instance()->reset() ;

	SDHCALLcioWriter* lcioWriter = runAction->getWriter() ;
	lcioWriter->clear() ;
	lcioWriter->createLCEvent(event) ;

	SDHCALLcioWriter* lcioOldWriter = runAction->getOldWriter() ;
	lcioOldWriter->clear() ;
	lcioOldWriter->createLCEvent(event) ;
}

void SDHCALEventAction::EndOfEventAction(const G4Event* event)
{
	G4cout << "-------------------------------------------------------" << G4endl ;
	G4cout << "Event " << event->GetEventID() << G4endl ;

	SDHCALLcioWriter* lcioWriter = runAction->getWriter() ;
	SDHCALLcioWriter* lcioOldWriter = runAction->getOldWriter() ;
	SDHCALRootWriter* rootWriter = SDHCALRootWriter::Instance() ;

	G4HCofThisEvent* col = event->GetHCofThisEvent() ;

	std::vector<SDHCALHit*> hits ;
	for (int i = 0 ; i < col->GetNumberOfCollections() ; i++ )
	{
		SDHCALHitCollection* hCol = dynamic_cast<SDHCALHitCollection*>( col->GetHC(i) ) ;
		std::vector<SDHCALHit*> hitVec = *( hCol->GetVector() ) ;
		hits.insert(hits.end() , hitVec.begin() , hitVec.end() ) ;
	}

	std::vector<OldSDHCALHit*> oldHits = linkSteps(event) ;

	lcioWriter->createPrimaryParticle(event) ;
	lcioOldWriter->createPrimaryParticle(event) ;

	lcioWriter->createSimCalorimeterHits(hits) ;
	lcioOldWriter->createSimCalorimeterHits(oldHits) ;

	G4RunManager* runManager = G4RunManager::GetRunManager() ;
	const SDHCALPrimaryGeneratorAction* anAction = dynamic_cast<const SDHCALPrimaryGeneratorAction*>( runManager->GetUserPrimaryGeneratorAction() ) ;

	G4double primaryEnergy = anAction->getPrimaryEnergy()/CLHEP::GeV ;
	G4ThreeVector primaryMom = anAction->getPrimaryMom() ;
	G4ThreeVector primaryPos = anAction->getPrimaryPos() ;

	G4int particleID = anAction->getParticleDefinition()->GetPDGEncoding() ;

	lcioWriter->setValue("ParticleID" , particleID) ;
	lcioWriter->setValue("ParticleMomentum" , primaryMom) ;
	lcioWriter->setValue("ParticlePosition" , primaryPos) ;
	lcioWriter->setValue("ParticleEnergy" , primaryEnergy) ;

	lcioOldWriter->setValue("ParticleID" , particleID) ;
	lcioOldWriter->setValue("ParticleMomentum" , primaryMom) ;
	lcioOldWriter->setValue("ParticlePosition" , primaryPos) ;
	lcioOldWriter->setValue("ParticleEnergy" , primaryEnergy) ;

	anAction->print() ;
	G4cout << G4endl ;

	SDHCALSteppingAction* steppingAction = SDHCALSteppingAction::Instance() ;
	steppingAction->processSteps() ;

	G4double depositedEnergy = steppingAction->getDepositedEnergy()/CLHEP::GeV ;
	G4double leakedEnergy = steppingAction->getLeakedEnergy()/CLHEP::GeV ;
	G4double emFraction = steppingAction->getEMFraction() ;

	G4cout << "Deposited energy : " << depositedEnergy << " GeV" << G4endl ;
	G4cout << "Leaked energy : " << leakedEnergy << " GeV" << G4endl ;
	G4cout << "EM Fraction : " << 100*emFraction << " %" << G4endl ;
	G4cout << G4endl ;

	lcioWriter->setValue("DepositedEnergy" , depositedEnergy ) ;
	lcioWriter->setValue("LeakedEnergy" , leakedEnergy ) ;
	lcioWriter->setValue("EMFraction" , emFraction ) ;

	lcioOldWriter->setValue("DepositedEnergy" , depositedEnergy ) ;
	lcioOldWriter->setValue("LeakedEnergy" , leakedEnergy ) ;
	lcioOldWriter->setValue("EMFraction" , emFraction ) ;

	lcioWriter->writeLCEvent() ;
	lcioOldWriter->writeLCEvent() ;


	int nRealHits = 0 ;
	for ( std::vector<SDHCALHit*>::const_iterator it = hits.begin() ; it != hits.end() ; ++it )
	{
		if ( ( (*it)->getEndPos() - (*it)->getBeginPos() ).mag() > 0 )
			nRealHits++ ;
	}

	int nOldRealHits = 0 ;
	for ( std::vector<OldSDHCALHit*>::const_iterator it = oldHits.begin() ; it != oldHits.end() ; ++it )
	{
		if ( ( (*it)->getEndPos() - (*it)->getBeginPos() ).mag() > 0 )
			nOldRealHits++ ;
	}


	//processing time
	double timeOfThisEvent = 1.0*( clock() - beginClock )/CLOCKS_PER_SEC ;
	G4cout << "computing time : " << timeOfThisEvent << G4endl ;

	averageTime = (averageTime*nEventsProcessed + timeOfThisEvent)/(nEventsProcessed+1) ;
	nEventsProcessed++ ;
	G4cout << "average time : " << averageTime << G4endl ;




	rootWriter->setEventNumber( event->GetEventID() ) ;
	rootWriter->setNHit( nRealHits ) ;
	rootWriter->setNOldHit( nOldRealHits ) ;
	rootWriter->setPrimaryID( particleID ) ;
	rootWriter->setPrimaryEnergy( primaryEnergy ) ;
	rootWriter->setPrimaryPos( primaryPos ) ;
	rootWriter->setPrimaryMom( primaryMom ) ;
	rootWriter->setDepositedEnergy( depositedEnergy ) ;
	rootWriter->setLeakedEnergy( leakedEnergy ) ;
	rootWriter->setEmFraction( emFraction ) ;
	rootWriter->setComputingTime( timeOfThisEvent ) ;

	std::vector<double> stepCosAngle ;
	std::vector<double> stepLength ;
	std::vector<double> stepTime ;
	for ( std::vector<SDHCALHit*>::const_iterator it = hits.begin() ; it != hits.end() ; ++it )
	{
		stepCosAngle.push_back( std::cos( (*it)->getDeltaPos().angle( (*it)->getRPC()->rpcToGlobalCoordTransform( G4ThreeVector(0,0,1) ) ) ) ) ;
		stepLength.push_back( (*it)->getTrueLength() ) ;
		stepTime.push_back( (*it)->getTime() ) ;
	}

	rootWriter->setStepCosAngle( stepCosAngle ) ;
	rootWriter->setStepLength( stepLength ) ;
	rootWriter->setStepTime( stepTime ) ;

	rootWriter->fillTree() ;
}


//to be removed
std::vector<OldSDHCALHit*> SDHCALEventAction::linkSteps(const G4Event* event)
{
	std::vector<OldSDHCALHit*> hits ;

	const std::set<SDHCALRPCSensitiveDetector*>& detVec = SDHCALRPCSensitiveDetector::getSensitiveDetectorVec() ;

	for ( std::set<SDHCALRPCSensitiveDetector*>::const_iterator it = detVec.begin() ; it != detVec.end() ; ++it )
	{
		std::vector<OldSDHCALHit*> rpcHits = (*it)->getOldHitsCollection() ;
		StepLinkingAlgo* algo = new StepLinkingAlgo(rpcHits) ;
		std::vector<OldSDHCALHit*> temp = algo->getLinkedStepList() ;
		hits.insert(hits.end() , temp.begin() , temp.end() ) ;
		delete algo ;
	}

	return hits ;
}
