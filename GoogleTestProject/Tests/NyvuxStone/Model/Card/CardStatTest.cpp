#include "testpch.h"

#include "NyvuxStone/Core/Game/Decorator/CardStat/CardStatDecoratorModify.h"
#include "NyvuxStone/Model/Card/CardStat.h"
#include "NyvuxStone/Model/Card/CardSpec.h"
#include "NyvuxStone/Model/Card/CardSpecRepository.h"

#include "Helper.h"

using namespace std;

namespace nyvux
{
	class CharacterStatDecoratorModify;

	class CardStatTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			constexpr int CARD_ID = 69543;
			CardSpecRepository& Repository = MakeCardSpecRepositoryToMock();
			CardSpec = Repository.GetCardSpecById(CARD_ID);
		}

		CardSpec CardSpec;
	};
	TEST_F(CardStatTest, TestModify)
	{
		constexpr int MODIFY_MANA_COST = -1;
		constexpr int EXPECTED_MANA_COST = 3;

		CardStat CardStat(CardSpec);
		CardStat.Modify<CardStatDecoratorModify>(MODIFY_MANA_COST);

		EXPECT_EQ(EXPECTED_MANA_COST, CardStat.GetManaCost());
	}

	TEST_F(CardStatTest, TestModifyMore)
	{
		constexpr int MODIFY_MANA_COST = -1;
		constexpr int EXPECTED_MANA_COST = 0;

		CardStat CardStat(CardSpec);
		CardStat.Modify<CardStatDecoratorModify>(MODIFY_MANA_COST);
		CardStat.Modify<CardStatDecoratorModify>(MODIFY_MANA_COST);
		CardStat.Modify<CardStatDecoratorModify>(MODIFY_MANA_COST);
		CardStat.Modify<CardStatDecoratorModify>(MODIFY_MANA_COST);
		CardStat.Modify<CardStatDecoratorModify>(MODIFY_MANA_COST);
		CardStat.Modify<CardStatDecoratorModify>(MODIFY_MANA_COST);

		EXPECT_EQ(EXPECTED_MANA_COST, CardStat.GetManaCost());
	}

}
