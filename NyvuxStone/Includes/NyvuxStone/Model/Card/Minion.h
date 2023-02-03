#pragma once

#include "Character.h"
#include "MinionStat.h"

namespace nyvux
{
	class Minion : public Character
	{
	public:
		Minion(const CardSpec& CardSpec);

		void GainDamage(const int amount) override;
		void GainHeal(const int amount) override;

		void GainTaunt();
		void Silence();

		bool CanAttack() override;

		bool HasTaunt();
		bool HasCharge();
		bool HasRush();
		bool HasDivineShield();
		bool HasReborn();

	private:
		MinionStat MinionStat;
	};
}
