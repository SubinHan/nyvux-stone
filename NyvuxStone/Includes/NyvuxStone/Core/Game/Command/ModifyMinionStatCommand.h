#pragma once

#include "ICommand.h"
#include "NyvuxStone/Model/Card/Minion.h"
#include "NyvuxStone/Model/Event/NyvuxStoneEvent.h"

#include <memory>


namespace nyvux
{
	class ModifyMinionStatCommand : public ICommand
	{
	public:
		ModifyMinionStatCommand() = delete;
		ModifyMinionStatCommand(std::shared_ptr<Minion> Target, int DeltaAttack, int DeltaHealth);

		void Execute(std::shared_ptr<NyvuxStoneEvent> Event) override;

	private:
		std::shared_ptr<Minion> Target;
		int DeltaAttack;
		int DeltaHealth;
	};
}
