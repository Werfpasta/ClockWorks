#if !defined(CW_INCLUDE_MONITOR)
#define CW_INCLUDE_MONITOR

#include "clockworks\std\vector.hpp"
#include "clockworks\math\geom\rect.hpp"
#include "clockworks\os\os.hpp"

namespace ClockWorks {
	namespace Display {
		class Monitor {
				HMONITOR _hMonitor;
				HDC _hdcMonitor;
				LPRECT _lprcMonitor;
				LPARAM _dwData;
			public:
				Monitor(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
					: _hMonitor(hMonitor), _hdcMonitor(hdcMonitor), _lprcMonitor(lprcMonitor), _dwData(dwData) {
				}
				Math::Geom::Rect<int> GetDimensions() {
				}
				//VERTEDGE
				// VREFRESH 0 or 1 Default
		};

		std::vector<Monitor> GetMonitors() {
			std::vector<Monitor> ret;
			EnumDisplayMonitors(nullptr, nullptr,
			[&](HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)->BOOL {
				ret.push_back(Monitor(hMonitor, hdcMonitor, lprcMonitor, dwData));
			}, 0);
		}
	}
}

#endif
