#include "window.h"
#include <gtest/gtest.h>

TEST(windowSetup, initWindow){
	Window sim("test.txt");
	

	sim.initWin();
	sim.infoWin();
	sim.initTextWin();
	
	sim.eventLoop();	
	
	sim.debug();
	sim.getBufferRef() -> dump();
	cout << sim.getBufferRef() -> getLine(5) -> getOccupied() << endl;
}

int main(){
	
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
	return 0;
}
