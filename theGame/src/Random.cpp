#include "Random.h"

namespace game {
	
	std::mt19937 Random::m_randomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> Random::m_destribution;

}
