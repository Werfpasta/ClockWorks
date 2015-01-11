#if !defined(CW_INCLUDE_XOR)
#define CW_INCLUDE_XOR

#include "clockworks\std\stdint.hpp"

// TODO: Get the real implementation working

namespace ClockWorks {
	namespace Math {
		namespace Rand {
			class XORShift64 {
				private:
					std::uint64_t state;
				public:
					XORShift64(std::uint64_t Seed) : state(Seed) {}
					std::uint64_t Next() {
						state ^= state << 15;
						state ^= state >> 45;
						state ^= state << 17;
						return state;
					}
					std::uint64_t operator()() {
						return Next();
					}
					std::uint64_t State() {
						return state;
					}
			};
			class XORShift64_2 {
				private:
					std::uint64_t state;
				public:
					XORShift64_2(std::uint64_t Seed) : state(Seed) {}
					std::uint64_t Next() {
						state ^= state >> 6;
						state ^= state >> 27;
						state ^= state << 7;
						return state;
					}
					std::uint64_t operator()() {
						return Next();
					}
					std::uint64_t State() {
						return state;
					}
			};
			class XORShift64_3 {
				private:
					std::uint64_t state;
				public:
					XORShift64_3(std::uint64_t Seed) : state(Seed) {}
					std::uint64_t Next() {
						state ^= state << 20;
						state ^= state << 1;
						state ^= state >> 31;
						return state;
					}
					std::uint64_t operator()() {
						return Next();
					}
					std::uint64_t State() {
						return state;
					}
			};
		}
	}
}

#endif