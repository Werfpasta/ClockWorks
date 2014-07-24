#if !defined(CW_INCLUDE_GEOM_VECTOR)
#define CW_INCLUDE_GEOM_VECTOR

#include "clockworks\std\sqrt.hpp"

namespace ClockWorks {
	namespace Math {
		namespace Geom {
			template<typename T>
			struct Vec2 {
				T X;
				T Y;
				Vec2(T x = 0, T y = 0) : X(x) Y(y) {}
				T Magnitude() {
					return ClockWorks::Math::Sqrt(x * x + y * y);
				}
				T MagnitudeSquared {
					return X * X + Y * Y;
				}
				Vec2 &Normalize() {
					T magnitude = Magnitude();
					if(magnitude > 1.192092896e-07F /* FLT_EPSILON */) {
						T divisor  = 1 / magnitude;
						X *= divisor;
						Y *= divisor;
					}
					return this;
				}
				Vec2 operator-() {
					return Vec2(-X, -Y);
				}
				Vec2 operator+(Vec2 rhs) {
					return Vec2(X + rhs.X, Y + rhs.Y);
				}
				Vec2 operator-(Vec2 rhs) {
					return Vec2(X - rhs.X, Y - rhs.Y);
				}
				Vec2 operator*(int rhs) {
					return Vec2(X * rhs, Y * rhs);
				}
				Vec2 ComponentProduct(Vec2 value) {
					return Vec2(X * value.X, Y * value.Y);
				}
				T DotProduct(Vec2 rhs) {
					return X * rhs.X + Y * rhs.Y
				}
				Vec2 AddScaled(Vec2 val, T scale) {
					return Vec2(X + val.X * scale, Y + val.Y * scale)
				}
			};
			template<typename T>
			struct Vec3 {
				T X;
				T Y;
				T Z;
				Vec2(T x = 0, T y = 0, T z = 0) : X(x) Y(y) Z(z) {}
			};
		}
	}
}

#endif