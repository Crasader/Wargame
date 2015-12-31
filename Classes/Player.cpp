#include "pch.h"
#include "Player.h"

Player::Player()
{
	id = "Doofus";
	//hey there's something!
}

Player::Player(std::string id)
{
	this->id = id;
}

std::string Player::getID()
{
	return this->id;
}
