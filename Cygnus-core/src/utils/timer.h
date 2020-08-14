#pragma once

#include <Windows.h>

namespace Cygnus {

	class Timer {
	private:
		LARGE_INTEGER m_start;
		double m_frequency;

	public:
		Timer() {
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			m_frequency = 1.0 /frequency.QuadPart;
			QueryPerformanceCounter(&m_start);
		}

		void reset() {
			QueryPerformanceCounter(&m_start);
		}

		double elapsed() {
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_start.QuadPart;
			//m_start = current;
			return (double)(cycles * m_frequency);
		}



	};
}