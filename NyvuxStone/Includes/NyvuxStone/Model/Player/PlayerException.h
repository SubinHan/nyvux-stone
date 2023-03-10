#pragma once

#include <exception>

namespace nyvux
{
	class PlayerException : public std::exception
	{
	public:
		PlayerException(const char* Message);

		const char* what() const noexcept override;

	private:
		const char* Message;
	};
}