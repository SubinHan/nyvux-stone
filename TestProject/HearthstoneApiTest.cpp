#include "pch.h"
#include "CppUnitTest.h"

#include "../HearthStoneFake/HearthstoneApi.h"
#include "../HearthStoneFake/Card.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nyvux
{
	TEST_CLASS(HearthstoneApiTest)
	{
	public:

		TEST_METHOD(TestBasicRequest)
		{
			using namespace std;

			constexpr int CARD_ID = 79593;

			Card Expected = {};
			Expected.CardId = CARD_ID;
			Expected.Collectible = 1;
			Expected.Slug = "79593-all-fel-breaks-loose";
			Expected.ClassId = 14;
			Expected.MultiClassIds = vector<int>{};
			Expected.SpellSchoolId = 7;
			Expected.CardTypeId = 5;
			Expected.CardSetId = 1691;
			Expected.RarityId = 1;
			Expected.ManaCost = 5;
			Expected.Name = string("All Fel Breaks Loose");
			Expected.Text = string("Summon a friendly Demon that died this game. <b>Infuse ( Demons):</b> Summon three instead.");
			Expected.ParentId = CARD_ID;
			vector<int> ExpectedChildIds;
			ExpectedChildIds.push_back(79595);
			Expected.ChildIds = ExpectedChildIds;
			vector<int> ExpectedKeywordIds;
			ExpectedKeywordIds.push_back(238);
			Expected.KeywordIds = ExpectedKeywordIds;

			Card Actual = HearthstoneApi::GetCardById(CARD_ID);

			Assert::AreEqual(Expected, Actual);
		}
	};
}
