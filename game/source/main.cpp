#if __APPLE__
#if TARGET_OS_IPHONE
#include <SFML/Main.hpp>
#endif
#endif

#include <ctime>
#include "World.h"

int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));
	TT::World::GetInstance()->Loop();
	return 0;
}
