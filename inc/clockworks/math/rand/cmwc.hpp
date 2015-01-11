#if !defined(CW_INCL_MATH_RAND_CMWC)
#define CW_INCL_MATH_RAND_CMWC

#include "clockworks/std/new.hpp"
#include "clockworks/std/stdint.hpp"
#include "clockworks/math/rand/xor.hpp"

namespace ClockWorks {
	namespace Math {
		namespace Rand {
			class CMWC4096 {
				private:
					std::uint32_t c;
					std::uint32_t i;
					std::uint32_t* q;
				public:
					CMWC4096(std::uint64_t Seed)
						: c(362436), i(4095) {
						XORShift64 rand(Seed);
						q = (std::uint32_t*)malloc(sizeof(std::uint32_t) * 4096);
						for(int i = 0; i <= 4096; i++){
							q[i] = std::uint32_t(rand());
						}
					}
					~CMWC4096(){
						free(q);
					}
					std::uint32_t Next() {
						std::uint64_t t;
						std::uint32_t x;
						i = (i + 1) & 4095;
						t = 18782ULL * q[i] + c;
						c = (t >> 32);
						x = t + c;
						if(x < c){x++; c++;}
						return(q[i] = 0xfffffffe - x);
					}
					std::uint32_t operator()() {
						return Next();
					}
					std::uint32_t State() {
						return q[i];
					}
			};
		}
	}
}
#endif