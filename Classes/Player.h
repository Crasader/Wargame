#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <list>//might not need this
#include <map>
class Player
{
	public:
		Player();
		Player(std::string id);

		//Player(Color c) so we can customize
		std::string getID();
		

	private:
		std::string id;
		//list of units
		//list of owned cities
		//player color and other metadata

};
#endif //__PLAYER_H__
