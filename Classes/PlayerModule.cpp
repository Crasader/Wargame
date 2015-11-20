#include "pch.h"

#include "PlayerModule.h"

PlayerModule::PlayerModule(int num_players)
{
	playerList = std::list<Player *>(num_players, nullptr);
	curr_player = playerList.begin();
	for (std::list<Player *>::iterator it = playerList.begin(); it != playerList.end(); ++it)
	{
		*it = new Player();
	}

	//set up starting cities, and initialize starting unit
}

/*@TODO : we will have a unique map for each Player, and each player will have permissions for distinct units,
which will be handled by this Module
*/

PlayerModule::~PlayerModule()
{
	playerList.clear();
}

void PlayerModule::nextTurn()
{
	//for all units, set them to full turns excluding planes
	if (curr_player != playerList.end())
		curr_player++;
	else
		curr_player = playerList.begin();
	
	
}

Player * PlayerModule::getCurrentPlayer()
{
	return *curr_player;

}



