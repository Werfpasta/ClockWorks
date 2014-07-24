namespace ClockWorks {
	namespace Math {
		namespace Geom {
			template<typename T>
			struct Rect {
				T X;
				T Y;
				T X2;
				T Y2;
				Rect(T x = 0, T y = 0, T x2 = 0, T y2 = 0)
					: X(x), Y(y), X2(x2), Y2(y2) {}
				T Width() { return X2 - X; }
				T Height() { return Y2 - Y; }
				void Width(T val) { X2 = X + val; }
				void Height(T val) { Y2 = Y + val; }
			};
		}
	}
}