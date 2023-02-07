#include "testpch.h"

#include "NyvuxStone/Model/Event/EventListener.h"
#include "NyvuxStone/Model/Event/ICommand.h"

using ::testing::_;
using namespace std;

namespace nyvux
{
	class MockCommand : public ICommand
	{
	public:
		MOCK_METHOD(void, Execute, (Event), (override));
	};

	class EventListenerTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			Command = make_shared<MockCommand>();
		}

		shared_ptr<MockCommand> Command;
		EventListener Listener;
	};
	TEST_F(EventListenerTest, TestOnDamaged)
	{
		EXPECT_CALL(*Command, Execute(_)).Times(3);

		Listener.AddOnDamagedCommand(Command);

		Listener.OnDamaged(Event{});
		Listener.OnDamaged(Event{});
		Listener.OnDamaged(Event{});
		Listener.OnDrawed(Event{});
		Listener.OnHealed(Event{});
	}

	TEST_F(EventListenerTest, TestOnDrawed)
	{
		EXPECT_CALL(*Command, Execute(_)).Times(3);

		Listener.AddOnDrawedCommand(Command);

		Listener.OnDrawed(Event{});
		Listener.OnDrawed(Event{});
		Listener.OnDrawed(Event{});
		Listener.OnDamaged(Event{});
		Listener.OnHealed(Event{});
	}

	TEST_F(EventListenerTest, TestOnHealed)
	{
		EXPECT_CALL(*Command, Execute(_)).Times(3);

		Listener.AddOnHealedCommand(Command);

		Listener.OnHealed(Event{});
		Listener.OnHealed(Event{});
		Listener.OnHealed(Event{});
		Listener.OnDamaged(Event{});
		Listener.OnDrawed(Event{});
	}
}