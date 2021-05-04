
#if  defined (_MSC_VER)

    #pragma warning (push, 4)                    // Set maximum warning level. This 'push' is to set the level only. It will NOT be popped.

    #pragma warning (disable:    4616)           // #pragma warning: warning number 'n' not a valid compiler warning

    #pragma warning (disable:    4514)           // Unreferenced inline function has been removed
    #pragma warning (disable:    4710)           // Function not inlined
    #pragma warning (disable:    4786)           // Identifier was truncated to '255' characters in the debug information

    #pragma warning (error:      4715)           // Not all control paths return a value

    #pragma warning (default:    4616)           // #pragma warning: warning number 'n' not a valid compiler warning  //-V665

    // These warning settings for TXLib.h only and will be re-enabled at end of file:

    #pragma warning (push)

    #pragma warning (disable:    4616)           // #pragma warning: warning number 'n' not a valid compiler warning

    #pragma warning (disable:    4091)           // 'typedef': ignored on left of '...' when no variable is declared
    #pragma warning (disable:    4124)           // Using __fastcall with stack checking is ineffective
    #pragma warning (disable:    4127)           // Conditional expression is constant
    #pragma warning (disable:    4200)           // Nonstandard extension used: zero-sized array in struct/union
    #pragma warning (disable:    4201)           // Nonstandard extension used: nameless struct/union
    #pragma warning (disable:    4351)           // New behavior: elements of array will be default initialized
    #pragma warning (disable:    4480)           // Nonstandard extension used: specifying underlying type for enum 'type'
    #pragma warning (disable:    4481)           // Nonstandard extension used: override specifier 'override'
    #pragma warning (disable:    4555)           // Result of expression not used
    #pragma warning (disable:    4611)           // Interaction between '_setjmp' and C++ object destruction is non-portable
    #pragma warning (disable:    5045)           // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
    #pragma warning (disable:    6269)           // Possibly incorrect order of operations: dereference ignored
    #pragma warning (disable:    6285)           // (<non-zero constant>) || (<non-zero constant>) is always a non-zero constant. Did you intend to use bitwize-and operator?
    #pragma warning (disable:    6319)           // Use of the comma-operator in a tested expression causes the left argument to be ignored when it has no side-effects
    #pragma warning (disable:    6326)           // Potential comparison of a constant with another constant
    #pragma warning (disable:   26135)           // Missing locking annotation
    #pragma warning (disable:   26400)           // Do not assign the result of an allocation or a function call with an owner<T> return value to a raw pointer, use owner<T> instead (i.11).
    #pragma warning (disable:   26401)           // Do not delete a raw pointer that is not an owner<T> (i.11).
    #pragma warning (disable:   26403)           // Reset or explicitly delete an owner<T> pointer 'name' (r.3).
    #pragma warning (disable:   26408)           // Avoid malloc() and free(), prefer the nothrow version of new with delete (r.10).
    #pragma warning (disable:   26409)           // Avoid calling new and delete explicitly, use std::make_unique<T> instead (r.11).
    #pragma warning (disable:   26426)           // Global initializer calls a non-constexpr function 'name' (i.22).
    #pragma warning (disable:   26429)           // Symbol 'name' is never tested for nullness, it can be marked as not_null (f.23).
    #pragma warning (disable:   26430)           // Symbol 'name' is not tested for nullness on all paths (f.23).
    #pragma warning (disable:   26432)           // If you define or delete any default operation in the type 'struct 'name'', define or delete them all (c.21).
    #pragma warning (disable:   26435)           // Function 'name' should specify exactly one of 'virtual', 'override', or 'final' (c.128).
    #pragma warning (disable:   26438)           // Avoid 'goto' (es.76).
    #pragma warning (disable:   26440)           // Function 'name' can be declared 'noexcept' (f.6).
    #pragma warning (disable:   26446)           // Prefer to use gsl::at() instead of unchecked subscript operator (bounds.4).
    #pragma warning (disable:   26447)           // The function is declared 'noexcept' but calls function 'func' which may throw exceptions (f.6).
    #pragma warning (disable:   26448)           // Consider using gsl::finally if final action is intended (gsl.util).
    #pragma warning (disable:   26451)           // Arithmetic overflow: Using operator 'op' on a n-byte value and then casting the result to a m-byte value. Cast the value to the wider type before calling operator 'op' to avoid overflow (io.2).
    #pragma warning (disable:   26455)           // Default constructor may not throw. Declare it 'noexcept' (f.6).
    #pragma warning (disable:   26460)           // The reference argument 'stream' for function 'name' can be marked as const (con.3).
    #pragma warning (disable:   26461)           // The pointer argument 'name' for function 'name' can be marked as a pointer to const (con.3).
    #pragma warning (disable:   26462)           // The value pointed to by 'name' is assigned only once, mark it as a pointer to const (con.4).
    #pragma warning (disable:   26475)           // Do not use function style C-casts (es.49).
    #pragma warning (disable:   26477)           // Use 'nullptr' rather than 0 or NULL (es.47).
    #pragma warning (disable:   26481)           // Don't use pointer arithmetic. Use span instead (bounds.1).
    #pragma warning (disable:   26482)           // Only index into arrays using constant expressions (bounds.2).
    #pragma warning (disable:   26483)           // Value 'value' is outside the bounds (min, max) of variable 'name'. Only index into arrays using constant expressions that are within bounds of the array (bounds.2).
    #pragma warning (disable:   26485)           // Expression 'expr': No array to pointer decay (bounds.3).
    #pragma warning (disable:   26486)           // Don't pass a pointer that may be invalid to a function. Parameter 'n' 'name' in call to 'name' may be invalid (lifetime.3).
    #pragma warning (disable:   26487)           // Don't return a pointer 'name' that may be invalid (lifetime.4).
    #pragma warning (disable:   26488)           // Do not dereference a potentially null pointer: 'name'. 'name' was null at line 'n' (lifetime.1).
    #pragma warning (disable:   26489)           // Don't dereference a pointer that may be invalid: 'name'. 'name' may have been invalidated at line 'n' (lifetime.1).
    #pragma warning (disable:   26490)           // Don't use reinterpret_cast (type.1).
    #pragma warning (disable:   26492)           // Don't use const_cast to cast away const or volatile (type.3).
    #pragma warning (disable:   26493)           // Don't use C-style casts (type.4).
    #pragma warning (disable:   26496)           // The variable 'name' is assigned only once, mark it as const (con.4).
    #pragma warning (disable:   26497)           // The function 'name' could be marked constexpr if compile-time evaluation is desired (f.4).
    #pragma warning (disable:   26812)           // The enum type 'type' is unscoped. Prefer 'enum class' over 'enum' (Enum.3).
    #pragma warning (disable:   26814)           // The const variable 'name' can be computed at compile-time. Consider using constexpr (con.5).
    #pragma warning (disable:   28125)           // The function must be called from within a try/except block
    #pragma warning (disable:   28159)           // Consider using another function instead

    #pragma warning (default:    4616)           // #pragma warning: warning number 'n' not a valid compiler warning  //-V665

    #define _tx_thread          __declspec (thread)
    #define _tx_decltype(value)   decltype (value)

    #if !defined (_CLANG_VER)

    #pragma setlocale           ("russian")      // Set source file encoding, see also _TX_CODEPAGE

    #if !defined (NDEBUG)
        #pragma check_stack     (      on)       // Turn on stack probes at runtime
        #pragma strict_gs_check (push, on)       // Detects stack buffer overruns
    #endif

    #endif

    #define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES  1

#endif