/*************************************************************************
************************    Lepton_ArrayProxy    *************************
*************************************************************************/
#pragma once

#include <array>
#include <vector>
#include <assert.h>

namespace Lepton
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
		ArrayProxy() noexcept : m_address(nullptr), m_count(0) {}

		//!	@brief	Only used in this case: ArrayProxy<T> = nullptr.
		ArrayProxy(std::nullptr_t) noexcept : m_address(nullptr), m_count(0) {}

		//!	@brief	Construct with an instance.
		ArrayProxy(const Type & inst) noexcept : m_address(&inst), m_count(1) {}

		//!	@brief	Construct with a list of data.
		explicit ArrayProxy(const Type * address, uint32_t count) : m_address(address), m_count(count) {}

		//!	@brief	Construct with std::initializer_list.
		ArrayProxy(const std::initializer_list<Type> & rhs) : m_address(rhs.begin()), m_count(static_cast<uint32_t>(rhs.size())) {}

		//!	@brief	Construct with std::array.
		template<size_t N> ArrayProxy(const std::array<typename std::remove_const<Type>::type, N> & rhs) : m_address(rhs.data()), m_count(static_cast<uint32_t>(rhs.size())) {}

		//!	@brief	Construct with std::vector.
		template<class Alloc> ArrayProxy(const std::vector<typename std::remove_const<Type>::type, Alloc> & rhs) : m_address(rhs.data()), m_count(static_cast<uint32_t>(rhs.size())) {}

	public:

		//!	@brief	Test if the array is empty.
		bool empty() const noexcept { return (m_address == nullptr) || (m_count == 0); }

		//!	@brief	Return reference to the specified element.
		const Type & operator[](size_t pos) const { assert(pos < m_count); return m_address[pos]; }

		//!	@brief	Return last element of this array.
		const Type & back() const { assert(m_count > 0); return *(m_address + m_count - 1); }

		//!	@brief	Return first element of this array.
		const Type & front() const { assert(m_count > 0); return *m_address; }

		//!	@brief	Get end of the list.
		const Type * end() const { return m_address + m_count; }

		//!	@brief	Get beginning of the list.
		const Type * begin() const { return m_address; }

		//!	@brief	Return address to the first element.
		const Type * data() const { return m_address; }

		//!	@brief	Return count of elements.
		uint32_t size() const { return m_count; }

	private:

		const Type *	m_address;

		uint32_t		m_count;
	};
}