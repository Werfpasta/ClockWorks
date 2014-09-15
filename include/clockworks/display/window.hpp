#if !defined(CW_INCLUDE_WINDOW)
#define CW_INCLUDE_WINDOW

#include "clockworks\os\os.hpp"
#include "clockworks\util\dispatcher.hpp"
#include "clockworks\math\geom\rect.hpp"
#include "clockworks\std\abs.hpp"
#include "clockworks\std\pair.hpp"

namespace ClockWorks {
	namespace Display {
		enum class WindowEdge : WPARAM {
			Top = WMSZ_TOP,
			Bottom = WMSZ_BOTTOM,
			Left = WMSZ_LEFT,
			Right = WMSZ_RIGHT,
			TopLeft = WMSZ_TOPLEFT,
			TopRight = WMSZ_TOPRIGHT,
			BottomLeft = WMSZ_BOTTOMLEFT,
			BottomRight = WMSZ_BOTTOMRIGHT,
			Unknown = 0
		};
		WindowEdge GetEdge(WPARAM wPARAM) {
			return static_cast<WindowEdge>(wPARAM);
		}
		class Window {
			public:
				enum class OSChrome {
					Default,
					Borderless,
					Tool
				};
				struct ChromeBorder {
					int Left;
					int Right;
					int Top;
					int Bottom;
				};
				struct WindowParameters {
					unsigned int Width;
					unsigned int Height;
					bool AutoWidthHeight;
					int X;
					int Y;
					int AutoPos;
					bool Fullscreen;
					bool Resizeable;
					double AspectRatio;
					OSChrome Chrome;
					static WindowParameters GetDefault() {
						WindowParameters ret;
						ret.Width = 800;
						ret.Height = 600;
						ret.AutoWidthHeight = false;
						ret.X = 0;
						ret.Y = 0;
						ret.AutoPos = true;
						ret.Fullscreen = false;
						ret.Resizeable = true;
						ret.Chrome = OSChrome::Default;
						return ret;
					}
					static WindowParameters GetFullscreen() {
						WindowParameters ret;
						ret.Width = 0;
						ret.Height = 0;
						ret.AutoWidthHeight = true;
						ret.X = 0;
						ret.Y = 0;
						ret.AutoPos = false;
						ret.Fullscreen = true;
						ret.Resizeable = false;
						ret.Chrome = OSChrome::Borderless;
						return ret;
					}
				};
				Window(const Window &) = delete;
				Window operator=(const Window &) = delete;
			private:
				HWND _handle;
				LRESULT WndProc(HWND hWND, UINT uMSG, WPARAM wPARAM, LPARAM lPARAM) {
					switch(uMSG) {
						case WM_NULL:
							return 0;
						case WM_CREATE: {
								OnCreate();
								return 0;
							}
						case WM_KILLFOCUS: {
								OnLostFocus();
								return 0;
							}
						case WM_ACTIVATEAPP: {
								if(wPARAM == TRUE) {
									OnGainedFocus();
								} else {
									OnLostFocus();
								}
								return 0;
							}
						case WM_WINDOWPOSCHANGING: {
								auto *bounds = reinterpret_cast<WINDOWPOS *>(lPARAM);
								if(!(bounds->flags & SWP_NOMOVE)) {
									auto currentBounds = ClockWorks::Math::Geom::Rect<int>(
															 bounds->x +  _chromeBorder.Left,
															 bounds->y + _chromeBorder.Top,
															 bounds->cx + bounds->x - _chromeBorder.Right,
															 bounds->cy + bounds->y - _chromeBorder.Bottom
														 );
									_x = currentBounds.X;
									_y = currentBounds.Y;
									_width = currentBounds.Width();
									_height = currentBounds.Height();
									OnBoundsChange(currentBounds, WindowEdge::Unknown);
									bounds->x = currentBounds.X - _chromeBorder.Left;
									bounds->y = currentBounds.Y - _chromeBorder.Top;
									bounds->cx = currentBounds.X2 - currentBounds.X + _chromeBorder.Right;
									bounds->cy = currentBounds.Y2 - currentBounds.Y + _chromeBorder.Bottom;
								}
								return 0;
							}
						case WM_MOVING:
						case WM_SIZING: {
								WindowEdge edge = GetEdge(wPARAM);
								auto *bounds = reinterpret_cast<RECT *>(lPARAM);
								auto currentBounds = ClockWorks::Math::Geom::Rect<int>(
														 bounds->left + _chromeBorder.Left,
														 bounds->top + _chromeBorder.Top,
														 bounds->right - _chromeBorder.Right,
														 bounds->bottom - _chromeBorder.Bottom);
								_x = currentBounds.X;
								_y = currentBounds.Y;
								_width = currentBounds.Width();
								_height = currentBounds.Height();
								OnBoundsChange(currentBounds, edge);
								bounds->left = currentBounds.X - _chromeBorder.Left;
								bounds->top = currentBounds.Y - _chromeBorder.Top;
								bounds->right = currentBounds.X2 + _chromeBorder.Right;
								bounds->bottom = currentBounds.Y2 + _chromeBorder.Bottom;
								return TRUE;
							}
						case WM_SHOWWINDOW: {
								if(wPARAM == TRUE) {
									OnShow();
								} else {
									OnHide();
								}
								return 0;
							}
						case WM_CLOSE: {
								auto temp = OnClose();
								for(bool prevent : temp) {
									if(prevent) {
										return 0;
									}
								}
								Close();
								return 0;
							}
						case WM_DESTROY: {
								OnDestroy();
								return 0;
							}
						case WM_PAINT: {
								static PAINTSTRUCT ps;
								BeginPaint(_handle, &ps);
								OnRender();
								EndPaint(_handle, &ps);
								return 0;
							}
						// Ignored messages:
						case WM_WINDOWPOSCHANGED:
						case WM_SIZE: // WM_SIZING, no need to process duplicate data.
						case WM_MOVE: // WM_MOVING, no need to process duplicate data.
						case WM_ACTIVATE: { // WM_ACTIVATEAPP, no need to process duplicate data.
								return 0;
							}
						// Defaulted Messages:
						case WM_NCHITTEST:
						case WM_NCMOUSELEAVE:
						case WM_NCMOUSEMOVE: {
								return DefWindowProcA(hWND, uMSG, wPARAM, lPARAM);
							}
						default: {
								std::vector<std::pair<bool, long>> trapped = OnUntrappedMessage(hWND, uMSG, wPARAM, lPARAM);
								long ret = 0;
								bool isTrapped = false;
								for(std::pair<bool, long> wasTrapped : trapped) {
									if(wasTrapped.first) {
										ret = wasTrapped.second;
										isTrapped = true;
									}
								}
								if(isTrapped) {
									return ret;
								} else {
									//std::cout << ClockWorks::Win32::WMToString(uMSG) << ", " << wPARAM << ", " << lPARAM << std::endl;
								}
							}
					}
					return DefWindowProcA(hWND, uMSG, wPARAM, lPARAM);
				}
				static LRESULT CALLBACK StaticWndProc(HWND hWND, UINT uMSG, WPARAM wPARAM, LPARAM lPARAM) {
					if(uMSG == WM_NCCREATE) {
						SetWindowLongPtrA(hWND, GWLP_USERDATA, reinterpret_cast<LPARAM>(
											  reinterpret_cast<LPCREATESTRUCT>(lPARAM)->lpCreateParams));
					}
					Window *_this = reinterpret_cast<Window *>(
										GetWindowLongPtrA(hWND, GWLP_USERDATA));
					return _this ? _this->WndProc(hWND, uMSG, wPARAM, lPARAM)
						   : DefWindowProcA(hWND, uMSG, wPARAM, lPARAM);
				}
			public:
				void *GetHWND();
				ClockWorks::Util::Dispatcher<std::pair<bool /* Trapped */, long /* ReturnVal */>(void *hWND, unsigned int uMSG, unsigned int wPARAM, long lPARAM)> OnUntrappedMessage;
			private:
				ChromeBorder _chromeBorder;
				int _x;
				int _y;
				unsigned int _width;
				unsigned int _height;
				bool _fullscreen;
				OSChrome _chrome;
				char *_title;
			public:
				Window(const WindowParameters &Params = WindowParameters::GetDefault()) { /*: Mouse(*this)*/
					static_assert(sizeof(_handle) == sizeof(HWND), "_handle is not of proper size!");
					if(Params.AutoWidthHeight) {
						if(Params.Width > 0 && Params.Height <= 0) {
							_height = (Params.Width * 3) / 4;
						} else if(Params.Width <= 0 && Params.Height > 0) {
							_width = (_height * 4) / 3;
						} else if(Params.Width <= 0 && Params.Height <= 0) {
							_width = 800;
							_height = (_width * 3) / 4;
						}
					} else {
						_width = Params.Width;
						_height = Params.Height;
					}
					if(Params.AutoPos) {
					} else {
						_x = Params.X;
						_y = Params.Y;
					}
					_fullscreen = Params.Fullscreen;
					Params.Resizeable; // TODO
					_chrome = Params.Chrome;
					// Register window class.
					static WNDCLASS wc = { 0 };
					if(wc.hInstance == nullptr) {
						wc.lpfnWndProc = reinterpret_cast<WNDPROC>(StaticWndProc);
						wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
						wc.hInstance = GetModuleHandleA(nullptr);
						wc.cbClsExtra = 0;
						wc.cbWndExtra = 0;
						wc.hIcon = LoadIconA(nullptr, IDI_WINLOGO);
						wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
						wc.hbrBackground = nullptr;
						wc.lpszMenuName = nullptr;
						wc.lpszClassName = "CW_Window";
						if(!RegisterClass(&wc)) {
							DebugBreak();
							//throw new std::exception("Class failed to register");
						}
					}
					DWORD dwStyle;
					DWORD dwExStyle;
					dwStyle =
						WS_CLIPSIBLINGS |
						WS_CLIPCHILDREN |
						WS_OVERLAPPED |
						WS_CAPTION |
						WS_SYSMENU |
						WS_MINIMIZEBOX |
						WS_MAXIMIZEBOX |
						WS_SIZEBOX;
					dwExStyle =
						WS_EX_APPWINDOW |
						WS_EX_WINDOWEDGE;
					RECT rect = { 0, 0, 0, 0 };
					AdjustWindowRectEx(&rect, dwStyle, false, dwExStyle);
					_chromeBorder.Left = ClockWorks::std::abs(rect.left);
					_chromeBorder.Top = ClockWorks::std::abs(rect.top);
					_chromeBorder.Bottom = rect.bottom;
					_chromeBorder.Right = rect.right;
					_handle = CreateWindowEx(
								  dwExStyle,
								  "CW_Window",
								  "_TODO_",
								  dwStyle,
								  CW_USEDEFAULT, CW_USEDEFAULT, // Default X/Y
								  _width + _chromeBorder.Left + _chromeBorder.Right, _height + _chromeBorder.Top + _chromeBorder.Bottom, // Width/Height
								  0, // Parent
								  0, // Menu
								  GetModuleHandle(nullptr),
								  this);
					if(_handle == nullptr) {
						DebugBreak();
						//throw new std::exception("Window not created");
					}
				}
				Window(const Window &&RHS) {
					_chromeBorder = RHS._chromeBorder;
					_x = RHS._x;
					_y = RHS._y;
					_width = RHS._width;
					_height = RHS._height;
					_fullscreen = RHS._fullscreen;
					_chrome = RHS._chrome;
					_title = RHS._title;
					_handle = RHS._handle;
					SetWindowLongPtrA(_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
				}
				Window &operator=(const Window && RHS) {
					_chromeBorder = RHS._chromeBorder;
					_x = RHS._x;
					_y = RHS._y;
					_width = RHS._width;
					_height = RHS._height;
					_fullscreen = RHS._fullscreen;
					_chrome = RHS._chrome;
					_title = RHS._title;
					_handle = RHS._handle;
					SetWindowLongPtrA(_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
					return *this;
				}
				~Window() {
					Close();
					PumpOSQueue();
				}
				int  X() const {
					return _x;
				}
				void X(const int val) {
					_x = val;
				}
				int  Y() const {
					return _y;
				}
				void Y(const int val) {
					_y = val;
				}
				unsigned int Width() const {
					return _width;
				}
				void Width(const unsigned int val) {
					_width = val;
				}
				unsigned int Height() const {
					return _height;
				}
				ClockWorks::Math::Geom::Rect<int> Bounds() {
					return ClockWorks::Math::Geom::Rect<int>(_x, _y, _width, _height);
				}
				void Height(const unsigned int val) {
					_height = val;
				}
				bool Fullscreen() const {
					return _fullscreen;
				}
				void Fullscreen(bool val) {
					_fullscreen = val;
				}
				void PumpOSQueue() {
					MSG msg = { 0 };
					while(PeekMessage(&msg, _handle, 0, 0, PM_REMOVE)) {
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
				void Minimize() {
					ShowWindow(_handle, SW_MINIMIZE);
				}
				void Maximize() {
					ShowWindow(_handle, SW_MAXIMIZE);
				}
				void Restore() {
					ShowWindow(_handle, SW_RESTORE);
				}
				void Focus() {
					SetForegroundWindow(_handle);
					SetActiveWindow(_handle);
					SetFocus(_handle);
				}
				void Show() {
					ShowWindow(_handle, SW_SHOW);
					Focus();
				}
				void Hide() {
					ShowWindow(_handle, SW_HIDE);
				}
				void Close() {
					DestroyWindow(_handle);
				}
				friend void swap(Window &LHS, Window &RHS);
				const char *Title() const {
					return _title;
				}
				void Title(char *val) {
					_title = val;
					if(!SetWindowTextA(_handle, _title)) {
						//              FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(),
						//                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, nullptr);
						//std::exception("Failed to set window title");
						DebugBreak();
					}
				}
				OSChrome    Chrome() const {
					return _chrome;
				}
				void        Chrome(const OSChrome val) {
					_chrome = val;
				}
				ClockWorks::Util::Dispatcher<bool /* Prevent */()> OnClose;
				ClockWorks::Util::Dispatcher<void()> OnLostFocus;
				ClockWorks::Util::Dispatcher<void()> OnGainedFocus;
				ClockWorks::Util::Dispatcher<void()> OnShow;
				ClockWorks::Util::Dispatcher<void()> OnHide;
				ClockWorks::Util::Dispatcher<void()> OnCreate;
				ClockWorks::Util::Dispatcher<void()> OnDestroy;
				ClockWorks::Util::Dispatcher<void()> OnRender;
				ClockWorks::Util::Dispatcher<void(ClockWorks::Math::Geom::Rect<int>& Bounds, WindowEdge Edge)> OnBoundsChange;
		};
	}
}

#endif
