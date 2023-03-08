#pragma once
#include <vector>
#include "Matrix.hpp"
namespace rn
{
	namespace algorithm
	{
		template<class T>
		bool in(const T &value, const std::vector<T> &values)
		{
			return std::find(values.begin(), values.end(), value) != values.end();
		}


		template<class T>
		bool contains(const Matrix<T> &matrix, typename Matrix<T>::ConstRow::ConstIterator iterator)
		{
			for (auto i = matrix.begin_row(); i != matrix.end_row(); ++i)
			{
				for (auto j = i.begin(); j != i.end(); ++j)
				{
					if (j == iterator)
						return true;
				}
			}
			return false;
		}

		template<class T>
		std::vector<T> operator+(const std::vector<T> &u, const std::vector<T> &v)
		{
			std::vector<T> a;
			for (auto &i : u) a.push_back(i);
			for (auto &i : v) a.push_back(i);
			return a;
		}
		template<class T>
		std::vector<T *> operator+(const std::vector<T *> &u, const std::vector<T *> &v)
		{
			std::vector<T*> a;
			for (auto &i : u) a.push_back(i);
			for (auto &i : v) a.push_back(i);
			return a;
		}

		template<class T>
		std::vector<T> &operator+=(std::vector<T> &left, const std::vector<T> &right)
		{
			left = left + right;
			return left;
		}
	}
}