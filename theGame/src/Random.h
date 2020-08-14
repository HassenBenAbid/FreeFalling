#pragma once

#include <random>

namespace game {

	class Random {

	private:

		static std::mt19937 m_randomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> m_destribution;

	public:

		static void init() {
			m_randomEngine.seed(std::random_device()());
		}

		static float isFloat() {
			return (float)m_destribution(m_randomEngine) / (float)std::numeric_limits<uint32_t>::max();
		}
		

	};
}