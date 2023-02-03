#pragma once

#include "Card.h"
#include "CardSpec.h"
#include "CharacterStat.h"

namespace nyvux
{
	class Character : public Card
	{
	public:
		Character(const CardSpec& Spec);
		virtual ~Character() = default;

		virtual void GainDamage(const int amount);
		virtual void GainHeal(const int amount);

		int GetMaxHealth();
		int GetAttack();
		int GetCurrentHealth();

		virtual bool CanAttack() = 0;

		bool CanBeAttackTarget();
		bool CanBeSpellTarget();
		bool HasImmune();
		bool HasFreeze();
		bool HasStealth();
		bool HasWindfury();
		bool HasPoisonous();
		bool HasLifesteal();

		template<class DecoratorType, class... Types>
		void Modify(Types... Args);

	private:
		CharacterStat CharacterStat;
		
	};

	template <class DecoratorType, class ... Types>
	void Character::Modify(Types... Args)
	{;

		CharacterStat.Modify<DecoratorType>(Args...);
	}
}
