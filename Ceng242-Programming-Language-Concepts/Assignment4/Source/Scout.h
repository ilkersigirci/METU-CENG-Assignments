#ifndef HW4_SCOUT_H
#define HW4_SCOUT_H

#include"Player.h"

class Scout : public Player{
	/**
	 * Attack damage 25
	 * Heal power 0
	 * Max HP 125
	 * Goal Priorities -> {CHEST,TO_ALLY,ATTACK} in decreasing order
	 * Class abbreviation -> "sc" or "SC"
	 * Can move to all adjacent squares, including diagonals.
	 * Can attack all adjacent squares, including diagonals.
	 *
	 */
	public:
		Scout(uint id,int x, int y, Team team);
		int getAttackDamage() const override;
		int getHealPower() const override;
		int getMaxHP() const override;
		std::vector<Goal> getGoalPriorityList() override;
		const std::string getClassAbbreviation() const override;
		std::vector<Coordinate> getAttackableCoordinates() override;
		std::vector<Coordinate> getMoveableCoordinates() override;
		std::vector<Coordinate> getHealableCoordinates() override;
};

#endif
