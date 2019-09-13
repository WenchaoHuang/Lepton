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
	************************    ArrayProxy<T>    *************************
	*********************************************************************/

	/**
	 *	@brief	Template for array data.
	 */
	template<typename Type> class ArrayProxy
	{

	public:

		//!	@brief	Default constructor.
		constexpr ArrayProxy() : m_Count(0), m_Ptr(nullptr) {}

		//!	@brief	Only used in this case: ArrayProxy<T> = nullptr.
		constexpr ArrayProxy(std::nullptr_t) : m_Count(0), m_Ptr(nullptr) {}

		template<size_t N>
		ArrayProxy(std::array<Type, N> & _data) : m_Count(static_cast<uint32_t>(_data.size())), m_Ptr(_data.data()) {}


		template<class Allocator = std::allocator<Type>>
		ArrayProxy(std::vector<Type, Allocator> & _data) : m_Count(static_cast<uint32_t>(_data.size())), m_Ptr(_data.data()) {}


		ArrayProxy(std::initializer_list<Type> & _data) : m_Count(static_cast<uint32_t>(_data.size())), m_Ptr(_data.data()) {}


		operator ArrayProxy<const Type>() const { return ArrayProxy<const Type>(m_Count, m_Ptr); }

		//!	@brief	Constructed by a pointer to instance.
		explicit ArrayProxy(uint32_t count, Type * ptr) : m_Count(count), m_Ptr(ptr) {}

		const Type & operator[](uint32_t i) const { return m_Ptr[i]; }

		Type & operator[](uint32_t i) { return m_Ptr[i]; }

		//!	@brief	Constructed by a pointer to instance.
		ArrayProxy(Type * ptr) : m_Count(1), m_Ptr(ptr) {}

		uint32_t size() const { return m_Count; }

		bool empty() const { return m_Ptr == nullptr; }

		const Type * data() const { return m_Ptr; }

		Type * data() { return m_Ptr; }

	private:
		
		Type *			m_Ptr;

		uint32_t		m_Count;
	};

	/*********************************************************************
	*********************    ArrayProxy<const T>    **********************
	*********************************************************************/

	/**
	 *	@brief	Special template for const array data.
	 */
	template<typename Type> class ArrayProxy<const Type>
	{

	public:

		//!	@brief	Default constructor.
		constexpr ArrayProxy() : m_Count(0), m_Ptr(nullptr) {}

		//!	@brief	Only used in this case: ArrayProxy<const T> = nullptr.
		constexpr ArrayProxy(std::nullptr_t) : m_Count(0), m_Ptr(nullptr) {}

		//!	@brief	Constructed by a pointer to instance.
		explicit ArrayProxy(uint32_t count, const Type * ptr) : m_Count(count), m_Ptr(ptr) {}


		template<size_t N> ArrayProxy(const std::array<Type, N> & _data) : m_Count(static_cast<uint32_t>(_data.size())), m_Ptr(_data.data()) {}

		//!	@brief	Constructed by a pointer to instance.
		ArrayProxy(const Type * ptr) : m_Count(1), m_Ptr(ptr) {}

		const Type & operator[](uint32_t i) const { return m_Ptr[i]; }

		bool empty() const { return m_Ptr == nullptr; }

		const Type * data() const { return m_Ptr; }

		uint32_t size() const { return m_Count; }

	private:

		const Type *		m_Ptr;

		uint32_t			m_Count;
	};
}