/*************************************************************************
*************************    Lava_ArrayProxy    **************************
*************************************************************************/
#pragma once

#include <array>
#include <vector>

namespace Lava
{
	/*********************************************************************
	**************************    ArrayProxy    **************************
	*********************************************************************/

	/**
	 *	@brief		Template for array data.
	 */
	template<typename Type> class ArrayProxy
	{

	public:

		//!	@brief	Default constructor.
		constexpr ArrayProxy() : m_Address(nullptr), m_Count(0) {}

		//!	@brief	Construct with an instance.
		ArrayProxy(const Type & inst) : m_Address(&inst), m_Count(1) {}

		//!	@brief	Only used in this case: ArrayProxy<T> = nullptr.
		constexpr ArrayProxy(std::nullptr_t) : m_Address(nullptr), m_Count(0) {}

		//!	@brief	Construct with a list of data.
		explicit ArrayProxy(const Type * address, uint32_t count) : m_Address(address), m_Count(count) {}

		//!	@brief	Construct with std::initializer_list.
		ArrayProxy(const std::initializer_list<Type> & rhs) : m_Address(rhs.begin()), m_Count(static_cast<uint32_t>(rhs.size())) {}

		//!	@brief	Construct with std::array.
		template<size_t N> ArrayProxy(const std::array<typename std::remove_const<Type>::type, N> & rhs) : m_Address(rhs.data()), m_Count(static_cast<uint32_t>(rhs.size())) {}

		//!	@brief	Construct with std::vector.
		template<class Alloc> ArrayProxy(const std::vector<typename std::remove_const<Type>::type, Alloc> & rhs) : m_Address(rhs.data()), m_Count(static_cast<uint32_t>(rhs.size())) {}

	public:

		//!	@brief	Test if the array is empty.
		bool empty() const { return (m_Address == nullptr) || (m_Count == 0); }

		//!	@brief	Return reference to the specified element.
		const Type & operator[](size_t pos) const { return m_Address[pos]; }

		//!	@brief	Return last element of this array.
		const Type & back() const { return *(m_Address + m_Count - 1); }

		//!	@brief	Get end of the list.
		const Type * end() const { return m_Address + m_Count; }

		//!	@brief	Return first element of this array.
		const Type & front() const { return *m_Address; }

		//!	@brief	Get beginning of the list.
		const Type * begin() const { return m_Address; }

		//!	@brief	Return address to the first element.
		const Type * data() const { return m_Address; }

		//!	@brief	Return count of elements.
		uint32_t size() const { return m_Count; }

	private:

		const Type *		m_Address;

		uint32_t			m_Count;
	};
}