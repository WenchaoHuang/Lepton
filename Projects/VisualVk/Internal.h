/*************************************************************************
************************    VisualVk_Internal    *************************
*************************************************************************/
#pragma once

#include <set>
#include <vector>

namespace Vk
{
	/*********************************************************************
	***************************    Convert    ****************************
	*********************************************************************/

	template<typename Type> inline std::vector<Type> Convert(const std::set<Type> & Input)
	{
		std::vector<Type>	Output;

		Output.reserve(Input.size());

		for (auto & iter : Input)
		{
			Output.push_back(iter);
		}

		return Output;
	}
}