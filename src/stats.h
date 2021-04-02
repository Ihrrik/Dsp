#pragma once
#include <numeric>
#include <vector>

#include "Signal.h"

/// @brief Functions for statistical calculations on std::vector and dsp::Signal
namespace dsp
{
	/// @brief Returns the mean value of the passed range
	/// @tparam InputIt Iterator type.
	/// @tparam T Type of the samples. Should be float, double, or long double. Other types will cause undefined behavior.
	/// @param begin Start of the range.
	/// @param end End of the range.
	/// @return Mean value of the range.
	template<class T, class InputIt>
	T mean(InputIt begin, InputIt end)
	{
		auto sum = std::accumulate(begin, end, T(0));
		return sum / std::distance(begin, end);
	}
	/// @brief Returns the mean value of a vector
	/// @tparam T Type of the samples. Should be float, double, or long double. Other types will cause undefined behavior.
	/// @param x Vector to calculate the mean of.
	/// @return Mean value of the vector.
	template<class T>
	T mean(const std::vector<T>& x)
	{
		return mean<T>(x.begin(), x.end());
	}

	/// @brief Returns the mean value of a signal
	/// @tparam T Type of the samples. Should be float, double, or long double. Other types will cause undefined behavior.
	/// @param x Signal to calculate the mean of.
	/// @return Mean value of the signal.
	template<class T>
	T mean(const Signal<T>& x)
	{
		return mean<T>(x.begin(), x.end());
	}

	/// @brief Calculate the variance or standard deviation based on a sample or based on the population
	enum class weight{sample, population};

	/// @brief Calculates the variance of a range
	/// @tparam T Type of the samples. Should be float, double, or long double. Other types will cause undefined behavior.
	/// @tparam InputIt Iterator type.
	/// @param begin Start of the range.
	/// @param end End of the range.
	/// @param w Denominator to use in the calculation: If w == weight::sample, the denominator is N-1; if it w == population, the denominator is N. Default: sample.
	/// @return Variance of the samples in the range.
	template<class T, class InputIt>
	T var(InputIt begin, InputIt end, weight w = weight::sample)
	{
		auto mu = mean<T>(begin, end);
		auto sum = std::transform_reduce(begin, end, T(0), std::plus<T>(), [mu](auto x) {return std::pow(x - mu, 2); });
		if(w == weight::sample)
		{
			return sum / (std::distance(begin, end) - 1);
		}
		return sum / static_cast<T>(std::distance(begin, end));		
	}

	/// @brief Calculates the variance of a vector.
	/// @tparam T Type of the values. Should be float, double, or long double. Other types will cause undefined behavior.
	/// @param x Vector to calculate the variance of.
	/// @param w Denominator to use in the calculation: If w == weight::sample, the denominator is N-1; if it w == population, the denominator is N. Default: sample.
	/// @return Variance of the samples in the vector.
	template<class T>
	T var(const std::vector<T>& x, weight w = weight::sample)
	{
		return var<T>(x.begin(), x.end(), w);
	}

	
	/// @brief Calculates the variance of a Signal.
	/// @tparam T Type of the samples. Should be float, double, or long double. Other types will cause undefined behavior.
	/// @param x Signal to calculate the variance of.
	/// @param w Denominator to use in the calculation: If w == weight::sample, the denominator is N-1; if it w == population, the denominator is N. Default: sample.
	/// @return Variance of the signal.
	template<class T>
	T var(const dsp::Signal<T>& x, weight w = weight::sample)
	{
		return var<T>(x.begin(), x.end(), w);
	}

	/// @brief Calculates the standard deviation of a range
	/// @tparam T Type of the samples. Should be float, double, or long double. Other types will cause undefined behavior.
	/// @tparam InputIt Iterator type.
	/// @param begin Start of the range.
	/// @param end End of the range.
	/// @param w Denominator to use in the calculation: If w == weight::sample, the denominator is N-1; if it w == population, the denominator is N. Default: sample.
	/// @return Standard deviation of the samples in the range.
	template<class T, class IterIt>
	T std(IterIt begin, IterIt end, weight w = weight::sample)
	{
		return std::sqrt(var(begin, end, w));
	}

	/// @brief Calculates the standard deviation of a vector.
	/// @tparam T Type of the values. Should be float, double, or long double. Other types will cause undefined behavior.
	/// @param x Vector to calculate the standard deviation of.
	/// @param w Denominator to use in the calculation: If w == weight::sample, the denominator is N-1; if it w == population, the denominator is N. Default: sample.
	/// @return Standard deviation of the samples in the vector.	
	template<class T>
	T std(const std::vector<T>& x, weight w = weight::sample)
	{
		return std<T>(x.begin(), x.end(), w);
	}

	/// @brief Calculates the standard deviation of a Signal.
	/// @tparam T Type of the samples. Should be float, double, or long double. Other types will cause undefined behavior.
	/// @param x Signal to calculate the standard deviation of.
	/// @param w Denominator to use in the calculation: If w == weight::sample, the denominator is N-1; if it w == population, the denominator is N. Default: sample.
	/// @return Standard deviation of the signal.
	template<class T>
	T std(const dsp::Signal<T>& x, weight w = weight::sample)
	{
		return std<T>(x.begin(), x.end(), w);
	}
}