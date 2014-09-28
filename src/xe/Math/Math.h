#ifndef __MATH_MATH_H__
#define __MATH_MATH_H__
#include <common.h>
#include <omp.h>

namespace xe
{
	namespace Math
	{

template<typename T>
class XESHARED_EXPORT Math
{
public:
	static bool GetMinAndMax(T* pData, int count, T& min, T& max)
	{
		min = *pData;
		max = *pData;

		int coreNum = omp_get_max_threads();//��ô���������
		T* minArray = new T[coreNum];//��Ӧ������������������һ������
		T* maxArray = new T[coreNum];
		for (int i = 0; i < coreNum; ++i)
		{
			minArray[i] = *pData;
			maxArray[i] = *pData;
		}


#pragma omp parallel for
		for (int i = 0; i<count; ++i)
		{
			int k = omp_get_thread_num();
			if (pData[i] > maxArray[k])
			{
				maxArray[k] = pData[i];
			}
			if (pData[i] < minArray[k])
			{
				minArray[k] = pData[i];
			}
		}


		for (int i = 0; i < coreNum; ++i)
		{
			if (max < maxArray[i])
				max = maxArray[i];
			if (min > minArray[i])
				min = minArray[i];
		}

		delete maxArray;
		delete minArray;

		return true;
	}
};

	}
}

#endif //__MATH_MATH_H__