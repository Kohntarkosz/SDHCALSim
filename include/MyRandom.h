#ifndef MyRandom_h
#define MyRandom_h

#include <stdexcept>
#include <Randomize.hh>
#include <TRandom3.h>

class MyRandom : public TRandom3 
{
    static MyRandom* theOneTrueInstance ;

	public :

		static MyRandom* Instance()
		{
		    if ( !theOneTrueInstance ) 
				initInstance() ;

		    return theOneTrueInstance ;
		}


	protected :

		MyRandom(unsigned int seed)
			: TRandom3(seed)
		{
			if (theOneTrueInstance) 
				throw std::logic_error("MyRandom already exists") ;

			std::cout << "MyRandom initialized with seed : " << GetSeed() << std::endl ;
			theOneTrueInstance = this ;
		}

		static void initInstance()
		{
			new MyRandom( static_cast<unsigned int>(CLHEP::HepRandom::getTheSeed()) ) ;
		}

		virtual ~MyRandom() ;
} ;

#endif //MyRandom_h
