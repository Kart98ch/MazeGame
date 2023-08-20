#include "Player.h"
#include <iostream>

void Player::Draw() const { std::cout << kCursor; }

void Player::UpdateDirection(int arrowInput)
{
	switch (arrowInput)
	{
	case kUpArrow:
		ResetXDirection();
		SetYDirection(1);
		break;

	case kDownArrow:
		ResetXDirection();
		SetYDirection(-1);
		break;

	case kRightArrow:
		ResetYDirection();
		SetXDirection(1);
		break;

	case kLeftArrow:
		ResetYDirection();
		SetXDirection(-1);
		break;

	default:
		break;
	}

}

