#include "Field.h"

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

void nyvux::Field::PlaceCard(std::shared_ptr<AbstractPlaceableCard> PlaceableCard, int ColumnNumber)
{
	ColumnNumber = clamp(ColumnNumber, 0, static_cast<int>(FieldImpl.size()));

	auto Iter = FieldImpl.begin();
	std::advance(Iter, ColumnNumber);

	FieldImpl.insert(Iter, PlaceableCard);
}

int nyvux::Field::GetNumPlayed()
{
	return FieldImpl.size();
}

bool nyvux::Field::CanPlace()
{
	return FieldImpl.size() < MAX_FIELD_SIZE;
}
