/*************************************************************************
***********************    VisualVk_ArrayProxy    ************************
*************************************************************************/
#pragma once

#include <array>
#include <vector>
#include <vulkan/vulkan.h>

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
		ArrayProxy() : m_Count(0), m_Ptr(nullptr) {}

		//!	@brief	Created by a instance.
		ArrayProxy(Type & val) : m_Count(1), m_Ptr(&val) {}

		//!	@brief	Only used in this case: ArrayProxy<T> = nullptr.
		ArrayProxy(std::nullptr_t) : m_Count(0), m_Ptr(nullptr) {}

		//!	@brief	Created by specified data.
		explicit ArrayProxy(uint32_t count, Type * ptr) : m_Count(count), m_Ptr(ptr) {}

		//!	@brief	Constructed by std::initializer_list.
		ArrayProxy(std::initializer_list<Type> & _data) : m_Count(static_cast<uint32_t>(_data.size())), m_Ptr(_data.end()) {}

		//!	@brief	Constructed by std::array.
		template<size_t N> ArrayProxy(std::array<Type, N> & _data) : m_Count(static_cast<uint32_t>(_data.size())), m_Ptr(_data.data()) {}

		//!	@brief	Constructed by std::vector.
		template<class Allocator = std::allocator<Type>> ArrayProxy(std::vector<Type, Allocator> & _data) : m_Count(static_cast<uint32_t>(_data.size())), m_Ptr(_data.data()) {}

		//!	@brief	Convert to constant type of this object.
		operator ArrayProxy<const Type>() const { return ArrayProxy<const Type>(m_Count, m_Ptr); }

		//!	@brief	Get access to the specified element.
		const Type & operator[](uint32_t i) const { return m_Ptr[i]; }

		//!	@brief	Get access to the specified element.
		Type & operator[](uint32_t i) { return m_Ptr[i]; }

		//!	@brief	If the array is empty.
		bool empty() const { return m_Ptr == nullptr; }

		//!	@brief	Return constant address to the first element.
		const Type * data() const { return m_Ptr; }

		//!	@brief	Return count of elements.
		uint32_t size() const { return m_Count; }

		//!	@brief	Return address to the first element.
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
		ArrayProxy() : m_Count(0), m_Ptr(nullptr) {}

		//!	@brief	Created by a instance.
		ArrayProxy(const Type & val) : m_Count(1), m_Ptr(&val) {}

		//!	@brief	Only used in this case: ArrayProxy<const T> = nullptr.
		ArrayProxy(std::nullptr_t) : m_Count(0), m_Ptr(nullptr) {}

		//!	@brief	Created by specified data.
		explicit ArrayProxy(uint32_t count, const Type * ptr) : m_Count(count), m_Ptr(ptr) {}

		//!	@brief	Constructed by std::initializer_list.
		ArrayProxy(const std::initializer_list<Type> & _data) : m_Count(static_cast<uint32_t>(_data.size())), m_Ptr(_data.end()) {}
		
		//!	@brief	Constructed by std::array.
		template<size_t N> ArrayProxy(const std::array<Type, N> & _data) : m_Count(static_cast<uint32_t>(_data.size())), m_Ptr(_data.data()) {}

		//!	@brief	Constructed by std::vector.
		template<class Allocator = std::allocator<Type>> ArrayProxy(const std::vector<Type, Allocator> & _data) : m_Count(static_cast<uint32_t>(_data.size())), m_Ptr(_data.data()) {}

		//!	@brief	Get access to the specified element.
		const Type & operator[](uint32_t i) const { return m_Ptr[i]; }

		//!	@brief	If the array is empty.
		bool empty() const { return m_Ptr == nullptr; }

		//!	@brief	Return address to the first element.
		const Type * data() const { return m_Ptr; }

		//!	@brief	Return count of elements.
		uint32_t size() const { return m_Count; }

	private:

		const Type *		m_Ptr;

		uint32_t			m_Count;
	};
}