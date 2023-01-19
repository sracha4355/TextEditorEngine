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
}

int main(){
	
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
	return 0;
}
