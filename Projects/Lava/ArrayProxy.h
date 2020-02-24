/*************************************************************************
*************************    Lava_ArrayProxy    **************************
*************************************************************************/
#pragma once

#include <array>
#include <vector>
#include <assert.h>

namespace Lava
{
	/*********************************************************************
	************************    ArrayProxy<T>    *************************
	*********************************************************************/

	/**
	 *	@brief		Template for array data.
	 */
	template<typename Type> class ArrayProxy
	{

	public:

		//!	@brief	Default constructor.
		constexpr ArrayProxy() : m_Address(nullptr), m_Count(0) {}

		//!@brief	Construct with an instance.
		ArrayProxy(Type & instance) : m_Address(&instance), m_Count(1) {}

		//!@brief	Only used in this case: ArrayProxy<T> = nullptr.
		constexpr ArrayProxy(std::nullptr_t) : m_Address(nullptr), m_Count(0) {}

		//!@brief	Construct with a list of data.
		explicit ArrayProxy(Type * address, uint32_t count) : m_Address(address), m_Count(count) {}

		//!@brief	Convert to constant type of this object.
		operator ArrayProxy<const Type>() const { return ArrayProxy<const Type>(m_Address, m_Count); }

		//!@brief	Construct with std::array.
		template<uint32_t N> ArrayProxy(std::array<Type, N> & rhs) : m_Address(rhs.data()), m_Count(static_cast<uint32_t>(rhs.size())) {}

		//!@brief	Construct with std::vector.
		template<class Alloc = std::allocator<Type>> ArrayProxy(std::vector<Type, Alloc> & rhs) : m_Address(rhs.data()), m_Count(static_cast<uint32_t>(rhs.size())) {}

	public:

		//!@brief	Return last element of this array (constant).
		const Type & back() const { assert((m_Address != nullptr) && (m_Count != 0)); return *(m_Address + m_Count - 1); }

		//!@brief	Return last element of this array.
		Type & back() { assert((m_Address != nullptr) && (m_Count != 0)); return *(m_Address + m_Count - 1); }

		//!@brief	Return reference to the specified element (constant).
		const Type & operator[](uint32_t pos) const { assert(pos < m_Count); return m_Address[pos]; }

		//!@brief	Return reference to the specified element.
		Type & operator[](uint32_t pos) { assert(pos < m_Count); return m_Address[pos]; }

		//!@brief	Return first element of this array (constant).
		const Type & front() const { assert(m_Address != nullptr); return *m_Address; }

		//!@brief	Test if the array is empty.
		bool empty() const { return (m_Address == nullptr) || (m_Count == 0); }

		//!@brief	Return first element of this array.
		Type & front() { assert(m_Address != nullptr); return *m_Address; }

		//!@brief	Get end of the list (constant).
		const Type * end() const { return m_Address + m_Count; }

		//!@brief	Get beginning of the list (constant).
		const Type * begin() const { return m_Address; }

		//!@brief	Return address to the first element (constant).
		const Type * data() const { return m_Address; }

		//!@brief	Get end of the list.
		Type * end() { return m_Address + m_Count; }

		//!@brief	Return count of elements.
		uint32_t size() const { return m_Count; }

		//!@brief	Get beginning of the list.
		Type * begin() { return m_Address; }

		//!@brief	Return address to the first element.
		Type * data() { return m_Address; }

	private:

		Type *			m_Address;

		uint32_t		m_Count;
	};

	/*********************************************************************
	*********************    ArrayProxy<const T>    **********************
	*********************************************************************/

	/**
	 *	@brief		Special template for const array data.
	 */
	template<typename Type> class ArrayProxy<const Type>
	{

	public:

		//!@brief	Default constructor.
		constexpr ArrayProxy() : m_Address(nullptr), m_Count(0) {}

		//!@brief	Construct with an instance.
		ArrayProxy(const Type & instance) : m_Address(&instance), m_Count(1) {}

		//!@brief	Only used in this case: ArrayProxy<T> = nullptr.
		constexpr ArrayProxy(std::nullptr_t) : m_Address(nullptr), m_Count(0) {}

		//!@brief	Construct with a list of data.
		explicit ArrayProxy(const Type * address, uint32_t count) : m_Address(address), m_Count(count) {}

		//!@brief	Construct with std::initializer_list.
		ArrayProxy(const std::initializer_list<Type> & rhs) : m_Address(rhs.begin()), m_Count(static_cast<uint32_t>(rhs.size())) {}

		//!@brief	Construct with std::array.
		template<uint32_t N> ArrayProxy(const std::array<Type, N> & rhs) : m_Address(rhs.data()), m_Count(static_cast<uint32_t>(rhs.size())) {}

		//!@brief	Construct with std::vector.
		template<class Alloc = std::allocator<Type>> ArrayProxy(const std::vector<Type, Alloc> & rhs) : m_Address(rhs.data()), m_Count(static_cast<uint32_t>(rhs.size())) {}

	public:

		//!@brief	Return last element of this array.
		const Type & back() const { assert((m_Address != nullptr) && (m_Count != 0)); return *(m_Address + m_Count - 1); }

		//!@brief	Return reference to the specified element.
		const Type & operator[](uint32_t pos) const { assert(pos < m_Count); return m_Address[pos]; }

		//!@brief	Return first element of this array.
		const Type & front() const { assert(m_Address != nullptr); return *m_Address; }

		//!@brief	Test if the array is empty.
		bool empty() const { return (m_Address == nullptr) || (m_Count == 0); }

		//!@brief	Get end of the list.
		const Type * end() const { return m_Address + m_Count; }

		//!@brief	Get beginning of the list).
		const Type * begin() const { return m_Address; }

		//!@brief	Return address to the first element.
		const Type * data() const { return m_Address; }

		//!@brief	Return count of elements.
		uint32_t size() const { return m_Count; }

	private:

		const Type *		m_Address;

		uint32_t			m_Count;
	};
}