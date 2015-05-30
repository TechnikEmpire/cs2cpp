#ifdef _MSC_VER
#error Not supported yet
#elif __GNUC__ >= 3
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
extern void *__builtin_memset(void *,int32_t,uint32_t);
#define memset __builtin_memset
extern void *__builtin_memcpy(void *,const void *,uint32_t);
#define compare_and_swap __sync_val_compare_and_swap 
#define sync_synchronize __sync_synchronize
#define fetch_and_add __sync_fetch_and_add
#define fetch_and_sub __sync_fetch_and_sub
#define swap __sync_lock_test_and_set
#define alloca __builtin_alloca

inline void* memcpy(void* dst, void* src, int32_t size)
{
	return __builtin_memcpy(dst, src, size);
}

#endif

typedef void Void;
typedef bool Boolean;
typedef int8_t SByte;
typedef int16_t Int16;
typedef int32_t Int32;
typedef int64_t Int64;
typedef uint8_t Byte;
typedef uint16_t Char;
typedef uint16_t UInt16;
typedef uint32_t UInt32;
typedef uint64_t UInt64;
typedef float Single;
typedef double Double;

#define GC_MALLOC calloc
#define GC_MALLOC_ATOMIC calloc
#define GC_MALLOC_IGNORE_OFF_PAGE calloc
#define GC_MALLOC_ATOMIC_IGNORE_OFF_PAGE calloc

extern "C" Byte* calloc(UInt32);
extern "C" Void* __dynamic_cast(Void*, Void*, Void*, Int32);
extern "C" Void __cxa_pure_virtual();

// RTTI externals
extern "C" void* _ZTVN10__cxxabiv117__class_type_infoE;
extern "C" void* _ZTVN10__cxxabiv119__pointer_type_infoE;
extern "C" void* _ZTVN10__cxxabiv120__si_class_type_infoE;
extern "C" void* _ZTVN10__cxxabiv121__vmi_class_type_infoE;
extern "C" void* _ZTVN10__cxxabiv129__pointer_to_member_type_infoE;

// Float
extern "C" Double fmod (Double, Double);

inline Void* __interface_to_object(Void* _interface)
{
	if (!_interface)
	{
		return 0;
	}

	return (Void*) ((Byte*)_interface + *(*(Int32**)_interface - 2));
}

inline Void* __dynamic_cast_null_test(Void* src, Void* rttiFrom, Void* rttiTo, Int32 offset)
{
	if (!src)
	{
		return 0;
	}

	return __dynamic_cast(src, rttiFrom, rttiTo, offset);
}

struct System_InvalidCastException;
Void Void_System_InvalidCastException__ctorFN(System_InvalidCastException* __this);
System_InvalidCastException* System_InvalidCastException_System_InvalidCastException__newFN();
inline Void* __dynamic_cast_null_test_throw(Void* src, Void* rttiFrom, Void* rttiTo, Int32 offset)
{
	if (!src)
	{
		return 0;
	}

	Void* casted = __dynamic_cast(src, rttiFrom, rttiTo, offset);
	if (!casted)
	{
		System_InvalidCastException* _new;
		_new = System_InvalidCastException_System_InvalidCastException__newFN();
		Void_System_InvalidCastException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return casted;
}

struct System_DivideByZeroException;
Void Void_System_DivideByZeroException__ctorFN(System_DivideByZeroException* __this);
System_DivideByZeroException* System_DivideByZeroException_System_DivideByZeroException__newFN();
template < typename T > T __check_divide(T div)
{
	if (!div)
	{
		System_DivideByZeroException* _new;
		_new = System_DivideByZeroException_System_DivideByZeroException__newFN();
		Void_System_DivideByZeroException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return div;
}

struct System_OverflowException;
Void Void_System_OverflowException__ctorFN(System_OverflowException* __this);
System_OverflowException* System_OverflowException_System_OverflowException__newFN();

inline SByte __add_ovf(SByte a, SByte b)
{
	SByte s = (Byte) a + (Byte) b;
	if (b >= 0)
	{
		if (s < a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}
	else
	{
		if (s >= a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}

	return s;
}

inline Int16 __add_ovf(Int16 a, Int16 b)
{
	Int16 s = (UInt16) a + (UInt16) b;
	if (b >= 0)
	{
		if (s < a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}
	else
	{
		if (s >= a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}

	return s;
}

inline Int32 __add_ovf(Int32 a, Int32 b)
{
	Int32 s = (UInt32) a + (UInt32) b;
	if (b >= 0)
	{
		if (s < a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}
	else
	{
		if (s >= a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}

	return s;
}

inline Int64 __add_ovf(Int64 a, Int64 b)
{
	Int64 s = (UInt64) a + (UInt64) b;
	if (b >= 0)
	{
		if (s < a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}
	else
	{
		if (s >= a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}

	return s;
}

template < typename T > inline T __add_ovf_un(T a, T b)
{
	if ((T)-1 - (T)a <= (T) b)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a + b;
}

inline SByte __sub_ovf(SByte a, SByte b)
{
	SByte s = (Byte) a - (Byte) b;
	if (b >= 0)
	{
		if (s > a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}
	else
	{
		if (s <= a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}

	return s;
}

inline Byte __sub_ovf(Byte a, Byte b)
{
	if (a < b)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a - b;
}

inline Int16 __sub_ovf(Int16 a, Int16 b)
{
	Int16 s = (UInt16) a - (UInt16) b;
	if (b >= 0)
	{
		if (s > a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}
	else
	{
		if (s <= a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}

	return s;
}

inline Char __sub_ovf(Char a, Char b)
{
	if (a < b)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a - b;
}

inline Int32 __sub_ovf(Int32 a, Int32 b)
{
	Int32 s = (UInt32) a - (UInt32) b;
	if (b >= 0)
	{
		if (s > a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}
	else
	{
		if (s <= a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}

	return s;
}

inline Int64 __sub_ovf(Int64 a, Int64 b)
{
	Int64 s = (UInt64) a - (UInt64) b;
	if (b >= 0)
	{
		if (s > a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}
	else
	{
		if (s <= a)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}

	return s;
}

template < typename T > inline T __sub_ovf_un(T a, T b)
{
	if ((T)a < (T) b)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a - b;
}

#define CHAR_BIT 8
template < typename T > inline T __mul_ovf(T a, T b)
{
	const int N = (int)(sizeof(T) * CHAR_BIT);
	const T MIN = (T)1 << (N-1);
	const T MAX = ~MIN;
	if (a == MIN)
	{
		if (b == 0 || b == 1)
		{
			return a * b;
		}

		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}
	if (b == MIN)
	{
		if (a == 0 || a == 1)
		{
			return a * b;
		}

		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	T sa = a >> (N - 1);
	T abs_a = (a ^ sa) - sa;
	T sb = b >> (N - 1);
	T abs_b = (b ^ sb) - sb;
	if (abs_a < 2 || abs_b < 2)
		return a * b;
	if (sa == sb)
	{
		if (abs_a > MAX / abs_b)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}
	else
	{
		if (abs_a > MIN / -abs_b)
		{
			System_OverflowException* _new;
			_new = System_OverflowException_System_OverflowException__newFN();
			Void_System_OverflowException__ctorFN(_new);
			throw (::Void*) _new;
		}
	}

	return a * b;
}

inline Byte __mul_ovf_un(Byte a, Byte b)
{
	if (b > ((Byte)-1) / a)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a * b;
}

inline UInt16 __mul_ovf_un(UInt16 a, UInt16 b)
{
	if (b > ((UInt16)-1) / a)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a * b;
}

inline UInt32 __mul_ovf_un(UInt32 a, UInt32 b)
{
	if (b > ((UInt32)-1) / a)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a * b;
}

inline UInt64 __mul_ovf_un(UInt64 a, UInt64 b)
{
	if (b > ((UInt64)-1) / a)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a * b;
}

inline SByte __mul_ovf_un(SByte a, SByte b)
{
	if ((Byte)b > ((Byte)-1) / (Byte)a)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a * b;
}

inline Int16 __mul_ovf_un(Int16 a, UInt16 b)
{
	if ((UInt16)b > ((UInt16)-1) / (UInt16)a)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a * b;
}

inline Int32 __mul_ovf_un(Int32 a, Int32 b)
{
	if ((UInt32)b > ((UInt32)-1) / (UInt32)a)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a * b;
}

inline Int64 __mul_ovf_un(Int64 a, Int64 b)
{
	if ((UInt64)b > ((UInt64)-1) / (UInt64)a)
	{
		System_OverflowException* _new;
		_new = System_OverflowException_System_OverflowException__newFN();
		Void_System_OverflowException__ctorFN(_new);
		throw (::Void*) _new;
	}

	return a * b;
}