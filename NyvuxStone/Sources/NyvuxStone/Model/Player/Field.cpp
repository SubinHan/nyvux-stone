#include "pch.h"

#include "NyvuxStone/Model/Player/Field.h"

#include <iterator>
#include <algorithm>

using namespace std;

nyvux::Field::Field() : FieldImpl()
{
}

std::shared_ptr<nyvux::Field> nyvux::Field::CreateField()
{
	return make_shared<Field>();
}

void nyvux::Field::PlaceCard(std::shared_ptr<nyvux::Minion> PlaceableCard, int ColumnNumber)
{
	ColumnNumber = clamp(ColumnNumber, 0, static_cast<int>(FieldImpl.size()));

	auto Iter = FieldImpl.begin();
	std::advance(Iter, ColumnNumber);

	FieldImpl.insert(Iter, PlaceableCard);
}

int nyvux::Field::GetNumPlayed()
{
	return static_cast<int>(FieldImpl.size());
}

bool nyvux::Field::CanPlace()
{
	return FieldImpl.size() < MAX_FIELD_SIZE;
}

bool nyvux::Field::IsPlaced(std::shared_ptr<nyvux::Minion> Card)
{
	auto Iter = find(FieldImpl.begin(), FieldImpl.end(), Card);
	bool Found = Iter != FieldImpl.end();
	return Found;
}

void nyvux::Field::Remove(std::shared_ptr<nyvux::Minion> Card)
{
	FieldImpl.remove(Card);
}

bool nyvux::Field::ContainsMinion(std::shared_ptr<Minion> Minion)
{
	for(auto Placed : FieldImpl)
	{
		if (Minion == Placed)
			return true;
	}

	return false;
}

std::shared_ptr<nyvux::Minion> nyvux::Field::GetCardAt(int ZeroBasedIndex)
{
	auto Iter = FieldImpl.begin();
	std::advance(Iter, ZeroBasedIndex);

	return *Iter;
}
