#if !defined(CW_INCLUDE_DELEGATE)
#define CW_INCLUDE_DELEGATE

#if defined(_MSC_VER)
#define CW_FASTCALL __fastcall
#else
#define CW_FASTCALL
#endif

namespace ClockWorks {
	namespace Util {
		template <typename TSignature> class Delegate;
		template <typename R, typename ... A>
		class Delegate<R(A...) > {
			public:
				typedef R ReturnType;
				typedef ReturnType(CW_FASTCALL *signature_type)(A...);
				Delegate()
					: _objectPtr(0)
					, _stubPtr(0) {}
				template <ReturnType(*TMethod)(A...) >
				static Delegate FromFunction() {
					return _FromStub(0, &_FunctionStub<TMethod>);
				}
				template <class T, ReturnType(T::*TMethod)(A...) >
				static Delegate FromMethod(T *_objectPtr) {
					return _FromStub(_objectPtr, &_MethodStub<T, TMethod>);
				}
				template <class T, ReturnType(T::*TMethod)(A...) const>
				static Delegate FromConstMethod(T const *_objectPtr) {
					return _FromStub(const_cast<T *>(_objectPtr), &_ConstMethodStub<T, TMethod>);
				}
				ReturnType operator()(A ... a) const {
					return (*_stubPtr)(_objectPtr, a...);
				}
				bool operator==(const Delegate &d) const {
					return (d._stubPtr == this._stubPtr) && (d._objectPtr == this._objectPtr);
				}
				bool operator!=(const Delegate &d) const {
					return !(*this == d);
				}
				explicit operator bool() const {
					return _stubPtr != 0;
				}
				bool operator!() const {
					return !(operator bool());
				}
			private:
				typedef ReturnType(CW_FASTCALL *stub_type)(void *_objectPtr, A ... a);
				void *_objectPtr;
				stub_type _stubPtr;
				static Delegate _FromStub(void *_objectPtr, stub_type _stubPtr) {
					Delegate d;
					d._objectPtr = _objectPtr;
					d._stubPtr = _stubPtr;
					return d;
				}
				template <ReturnType(*TMethod)(A...) >
				static ReturnType CW_FASTCALL _FunctionStub(void *, A ... a) {
					return (TMethod)(a...);
				}
				template <class T, ReturnType(T::*TMethod)(A...) >
				static ReturnType CW_FASTCALL _MethodStub(void *_objectPtr, A ... a) {
					T *p = static_cast<T *>(_objectPtr);
					return (p->*TMethod)(a...);
				}
				template <class T, ReturnType(T::*TMethod)(A...) const>
				static ReturnType CW_FASTCALL _ConstMethodStub(void *_objectPtr, A ... a) {
					T const *p = static_cast<T *>(_objectPtr);
					return (p->*TMethod)(a...);
				}
		};
	}
}

#endif