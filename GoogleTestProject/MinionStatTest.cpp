#include "pch.h"

#include "../HearthStoneFake/Core/Api/HearthstoneApi.h"
#include "../HearthStoneFake/Model/Card/MinionStat.h"
#include "../HearthStoneFake/Model/Card/CardSpec.h"
#include "../HearthStoneFake/Model/Card/MinionStatDecoratorModifier.h"
#include "../HearthStoneFake/Model/Card/MinionStatDecoratorSilence.h"

using namespace std;

namespace nyvux
{
	class MinionStatTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			constexpr int CARD_ID = 69543;
			CardSpec = HearthstoneApi::GetCardSpecById(CARD_ID);
		}

		CardSpec CardSpec;
	};
	TEST_F(MinionStatTest, TestVanilla)
	{
		constexpr int EXPECTED_ATTACK = 4;
		constexpr int EXPECTED_MAX_HEALTH = 5;
		constexpr int EXPECTED_CURRENT_HEALTH = 5;

		MinionStat MinionStat(CardSpec);

		EXPECT_EQ(EXPECTED_ATTACK, MinionStat.GetAttack());
		EXPECT_EQ(EXPECTED_MAX_HEALTH, MinionStat.GetMaxHealth());
		EXPECT_EQ(EXPECTED_CURRENT_HEALTH, MinionStat.GetCurrentHealth());
	}

	TEST_F(MinionStatTest, TestBuff)
	{
		constexpr int MODIFY_ATTACK = 1;
		constexpr int MODIFY_HEALTH = 2;
		constexpr int EXPECTED_ATTACK = 5;
		constexpr int EXPECTED_MAX_HEALTH = 7;
		constexpr int EXPECTED_CURRENT_HEALTH = 7;

		MinionStat MinionStat(CardSpec);
		MinionStat.Modify<MinionStatDecoratorModifier>(MODIFY_ATTACK, MODIFY_HEALTH);

		EXPECT_EQ(EXPECTED_ATTACK, MinionStat.GetAttack());
		EXPECT_EQ(EXPECTED_MAX_HEALTH, MinionStat.GetMaxHealth());
		EXPECT_EQ(EXPECTED_CURRENT_HEALTH, MinionStat.GetCurrentHealth());
	}

	TEST_F(MinionStatTest, TestBuffMore)
	{
		constexpr int MODIFY_ATTACK = 1;
		constexpr int MODIFY_HEALTH = 2;
		constexpr int EXPECTED_ATTACK = 6;
		constexpr int EXPECTED_MAX_HEALTH = 9;
		constexpr int EXPECTED_CURRENT_HEALTH = 9;

		MinionStat MinionStat(CardSpec);
		MinionStat.Modify<MinionStatDecoratorModifier>(MODIFY_ATTACK, MODIFY_HEALTH);
		MinionStat.Modify<MinionStatDecoratorModifier>(MODIFY_ATTACK, MODIFY_HEALTH);

		EXPECT_EQ(EXPECTED_ATTACK, MinionStat.GetAttack());
		EXPECT_EQ(EXPECTED_MAX_HEALTH, MinionStat.GetMaxHealth());
		EXPECT_EQ(EXPECTED_CURRENT_HEALTH, MinionStat.GetCurrentHealth());
	}

	TEST_F(MinionStatTest, TestSilence)
	{
		constexpr int MODIFY_ATTACK = 1;
		constexpr int MODIFY_HEALTH = 2;
		constexpr int EXPECTED_ATTACK = 4;
		constexpr int EXPECTED_MAX_HEALTH = 5;
		constexpr int EXPECTED_CURRENT_HEALTH = 5;

		MinionStat MinionStat(CardSpec);
		MinionStat.Modify<MinionStatDecoratorModifier>(MODIFY_ATTACK, MODIFY_HEALTH);
		MinionStat.Modify<MinionStatDecoratorModifier>(MODIFY_ATTACK, MODIFY_HEALTH);
		MinionStat.Modify<MinionStatDecoratorSilence>();

		EXPECT_EQ(EXPECTED_ATTACK, MinionStat.GetAttack());
		EXPECT_EQ(EXPECTED_MAX_HEALTH, MinionStat.GetMaxHealth());
		EXPECT_EQ(EXPECTED_CURRENT_HEALTH, MinionStat.GetCurrentHealth());
	}

	TEST_F(MinionStatTest, TestSilenceAndBuff)
	{
		constexpr int MODIFY_ATTACK = 1;
		constexpr int MODIFY_HEALTH = 2;
		constexpr int EXPECTED_ATTACK = 5;
		constexpr int EXPECTED_MAX_HEALTH = 7;
		constexpr int EXPECTED_CURRENT_HEALTH = 7;

		MinionStat MinionStat(CardSpec);
		MinionStat.Modify<MinionStatDecoratorModifier>(MODIFY_ATTACK, MODIFY_HEALTH);
		MinionStat.Modify<MinionStatDecoratorModifier>(MODIFY_ATTACK, MODIFY_HEALTH);
		MinionStat.Modify<MinionStatDecoratorSilence>();
		MinionStat.Modify<MinionStatDecoratorModifier>(MODIFY_ATTACK, MODIFY_HEALTH);

		EXPECT_EQ(EXPECTED_ATTACK, MinionStat.GetAttack());
		EXPECT_EQ(EXPECTED_MAX_HEALTH, MinionStat.GetMaxHealth());
		EXPECT_EQ(EXPECTED_CURRENT_HEALTH, MinionStat.GetCurrentHealth());
	}

	TEST_F(MinionStatTest, TestDamage)
	{
		constexpr int AMOUNT_DAMAGE = 2;
		constexpr int EXPECTED_ATTACK = 4;
		constexpr int EXPECTED_MAX_HEALTH = 5;

		MinionStat MinionStat(CardSpec);

		MinionStat.Damage(AMOUNT_DAMAGE);

		EXPECT_EQ(EXPECTED_ATTACK, MinionStat.GetAttack());
		EXPECT_EQ(EXPECTED_MAX_HEALTH, MinionStat.GetMaxHealth());
		EXPECT_EQ(EXPECTED_MAX_HEALTH - AMOUNT_DAMAGE, MinionStat.GetCurrentHealth());
	}

	TEST_F(MinionStatTest, TestDamageAndBuff)
	{
		constexpr int MODIFY_ATTACK = 1;
		constexpr int MODIFY_HEALTH = 2;
		constexpr int AMOUNT_DAMAGE = 2;
		constexpr int EXPECTED_ATTACK = 5;
		constexpr int EXPECTED_MAX_HEALTH = 7;

		MinionStat MinionStat(CardSpec);

		MinionStat.Damage(AMOUNT_DAMAGE);
		MinionStat.Modify<MinionStatDecoratorModifier>(MODIFY_ATTACK, MODIFY_HEALTH);

		EXPECT_EQ(EXPECTED_ATTACK, MinionStat.GetAttack());
		EXPECT_EQ(EXPECTED_MAX_HEALTH, MinionStat.GetMaxHealth());
		EXPECT_EQ(EXPECTED_MAX_HEALTH - AMOUNT_DAMAGE, MinionStat.GetCurrentHealth());
	}

	TEST_F(MinionStatTest, TestDamageAndNerf)
	{
		constexpr int MODIFY_ATTACK = -1;
		constexpr int MODIFY_HEALTH = -2;
		constexpr int AMOUNT_DAMAGE = 2;
		constexpr int EXPECTED_ATTACK = 3;
		constexpr int EXPECTED_MAX_HEALTH = 3;


		MinionStat MinionStat(CardSpec);

		MinionStat.Damage(AMOUNT_DAMAGE);
		MinionStat.Modify<MinionStatDecoratorModifier>(MODIFY_ATTACK, MODIFY_HEALTH);

		EXPECT_EQ(EXPECTED_ATTACK, MinionStat.GetAttack());
		EXPECT_EQ(EXPECTED_MAX_HEALTH, MinionStat.GetMaxHealth());
		EXPECT_EQ(EXPECTED_MAX_HEALTH - AMOUNT_DAMAGE, MinionStat.GetCurrentHealth());
	}

	TEST_F(MinionStatTest, TestDamageAndNerfAndSilence)
	{
		constexpr int MODIFY_ATTACK = -1;
		constexpr int MODIFY_HEALTH = -2;
		constexpr int AMOUNT_DAMAGE = 2;
		constexpr int EXPECTED_ATTACK = 4;
		constexpr int EXPECTED_MAX_HEALTH = 5;

		MinionStat MinionStat(CardSpec);

		MinionStat.Damage(AMOUNT_DAMAGE);
		MinionStat.Modify<MinionStatDecoratorModifier>(MODIFY_ATTACK, MODIFY_HEALTH);
		MinionStat.Modify<MinionStatDecoratorSilence>();

		EXPECT_EQ(EXPECTED_ATTACK, MinionStat.GetAttack());
		EXPECT_EQ(EXPECTED_MAX_HEALTH, MinionStat.GetMaxHealth());
		EXPECT_EQ(EXPECTED_MAX_HEALTH - AMOUNT_DAMAGE, MinionStat.GetCurrentHealth());
	}

	TEST_F(MinionStatTest, TestDamageAndHeal)
	{
		constexpr int AMOUNT_DAMAGE = 2;
		constexpr int AMOUNT_HEAL = 1;
		constexpr int EXPECTED_HEALTH = 4;

		MinionStat MinionStat(CardSpec);

		MinionStat.Damage(AMOUNT_DAMAGE);
		MinionStat.Heal(AMOUNT_HEAL);

		EXPECT_EQ(EXPECTED_HEALTH, MinionStat.GetCurrentHealth());
	}

	TEST_F(MinionStatTest, TestOverHeal)
	{
		constexpr int AMOUNT_HEAL = 99;
		constexpr int EXPECTED_HEALTH = 5;

		MinionStat MinionStat(CardSpec);

		MinionStat.Heal(AMOUNT_HEAL);

		EXPECT_EQ(EXPECTED_HEALTH, MinionStat.GetCurrentHealth());
	}

}