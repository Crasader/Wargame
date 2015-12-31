#ifndef __PLAYER_MODULE_H__
#define __PLAYER_MODULE_H__

#include "Player.h"

#include <list>
class PlayerModule
{
	public:
		/*
		Constructor will do the following:
		1)give each player its starting city,
		2)give one starting Infantry unit located on its starting city
		3)bookkeeping
		turn orders will go from Player 1 to 2 to 3 ... to num_players, back to 1
		does not limit on number of players so do not overload this*/
		PlayerModule(int num_players);

		

		~PlayerModule();


		/*preps curr_player's units for next turn and then moves curr_player to the next player */
		void nextTurn();

		/*returns a pointer to the current player*/
		Player * getCurrentPlayer();

		/*returns the name of the current player*/
		const char * getCurrentPlayerID();

		/*given a specific unit, will show intel on it if it belongs to another player,
		or will allow unit to be acted upon if it belongs to current player
		this function will probably be handled better in the HelloWorldScene.cpp
		*/
		//void selectUnit(Unit u)
	private:
		std::list<Player *> playerList;

		std::list<Player *>::iterator curr_player;
		//considering making a map of all units on board, so user can select another player's visible unit

};
#endif //__PLAYER_MODULE_H__
