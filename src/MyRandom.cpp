#include "MyRandom.h"

MyRandom* MyRandom::theOneTrueInstance = 0 ;

MyRandom::~MyRandom()
{
	theOneTrueInstance = NULL ;
}
