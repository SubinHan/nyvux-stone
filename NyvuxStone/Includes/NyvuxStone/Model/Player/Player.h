#pragma once

#include "Deck.h"
#include "Field.h"
#include "Hand.h"
#include "../../Core/Game/GameMediator.h"

#include <memory>

namespace nyvux
{
	class GameMediator;

	class Player : public std::enable_shared_from_this<Player>
	{
	public:
		Player(std::shared_ptr<Deck> Deck, std::shared_ptr<GameMediator> GameMediator);
		static std::shared_ptr<Player> CreatePlayer(std::shared_ptr<Deck> Deck, std::shared_ptr<GameMediator> GameMediator);

		void DrawCard();
		int GetNumCardsInDeck() const;
		int GetNumCardsInHand() const;
		int GetNumPlayedInField() const;
		void PlaceCardWithoutBattlecry(int ZeroBasedHandIndex, int ZeroBasedFieldIndex);
		std::shared_ptr<Character> GetCardInFieldAt(int ZeroBasedIndex);
		bool CanAttack(int ZeroBasedFieldIndexOfOpponents);

	private:
		void FirePlayed(std::shared_ptr<Card> Card);
		void FireDrawed(std::shared_ptr<Card> Card);
		void FireSummoned(std::shared_ptr<Character> Shared);

	private:
		std::shared_ptr<Deck> Deck;
		std::shared_ptr<Field> Field;
		std::shared_ptr<Hand> Hand;

		std::shared_ptr<GameMediator> GameMediator;
	};
}