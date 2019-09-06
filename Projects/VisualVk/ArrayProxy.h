/*************************************************************************
***********************    VisualVk_ArrayProxy    ************************
*************************************************************************/
#pragma once

#include <array>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace Vk
{
	/*********************************************************************
	**************************    ArrayProxy    **************************
	*********************************************************************/

	/**
	 *	@brief	Template for array data.
	 */
	template<typename Type> class ArrayProxy
	{

	public:

		//!	@brief	Default constructor.
		constexpr ArrayProxy() : m_Count(0), m_Ptr(nullptr) {}

		//!	@brief	Constructed by a instance.
		ArrayProxy(const Type & instance) : m_Count(1), m_Ptr(&instance) {}

		//!	@brief	Constructed by pointer.
		ArrayProxy(uint32_t count, const Type * ptr) : m_Count(count), m_Ptr(ptr) {}

		//!	@brief	Constructed by array.
		template<size_t N> ArrayProxy(const std::array<Type, N> & _data) : m_Count(N), m_Ptr(_data.data()) {}

		//!	@brief	Constructed by vector.
		template <class Allocator = std::allocator<Type>>
		ArrayProxy(const std::vector<Type, Allocator> & _data) : m_Count(static_cast<uint32_t>(_data.size())), m_Ptr(_data.data()) {}

		//!	@brief	Constructed by initializer_list.
		ArrayProxy(const std::initializer_list<Type> & _data) : m_Count(static_cast<uint32_t>(_data.end() - _data.begin())), m_Ptr(_data.begin()) {}

		//!	@brief	Test if sequence is empty.
		bool empty() const { return (m_Count == 0) || (m_Ptr == nullptr); }

		//!	@brief	Get end of list.
		const Type * end() const { return m_Ptr + m_Count; }

		//!	@brief	Get beginning of list.
		const Type * begin() const { return m_Ptr; }

		//!	@brief	Return address of first element.
		const Type * data() const { return m_Ptr; }

		//!	@brief	Return element count.
		uint32_t size() const { return m_Count; }

	private:

		Type * const		m_Ptr;

		const uint32_t		m_Count;
	};
}