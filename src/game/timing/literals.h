#pragma once

#include <cstdint>

namespace timing::literals
{
	constexpr uint32_t operator"" _fps(unsigned long long value)
	{
		return static_cast<uint32_t>(value);
	}

}  // timing::literals
