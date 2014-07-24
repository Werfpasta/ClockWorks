#if !defined(CW_INCLUDE_GEOM_SQRT)
#define CW_INCLUDE_GEOM_SQRT

namespace ClockWorks {
	namespace std {
		double inline __declspec(naked) __fastcall sqrt(double val) {
			_asm {
				fld qword ptr[esp + 4]
				fsqrt
				ret 8
			}
		}
		float inline sqrt(int val) {
			return sqrt(double(val));
		}
	}
}

#endif