#include "GOL.h"
#include "WolframCA.h"


void main()
{
	WolframCA ca({1,0,1,1,0,1,1,0}, 60);
	//GOL ca(1000, 5, 40);
	ca.run();
}
