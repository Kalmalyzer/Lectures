
#include <assert.h>
#include <float.h>
#include <stdio.h>

#include "FloatTypes.h"

SinglePrecisionFloat::SinglePrecisionFloat(double d)
	: m_floatValue((float) d)
{
}

SinglePrecisionFloat::SinglePrecisionFloat(uint sign, uint exponent, uint mantissa)
	: m_sign(sign), m_exponent(exponent), m_mantissa(mantissa)
{
	assert(sign == 0 || sign == 1);
	assert(exponent >= 0 && exponent <= MaxExponentValue);
	assert(mantissa >= 0 && mantissa <= MaxMantissaValue);
}

double SinglePrecisionFloat::getValue() const
{
	return (double) m_floatValue;
}

SinglePrecisionFloat& SinglePrecisionFloat::operator+=(const SinglePrecisionFloat& f)
{
	*this = *this + f;
	return *this;
}

SinglePrecisionFloat SinglePrecisionFloat::operator+(const SinglePrecisionFloat& f) const
{
	return SinglePrecisionFloat(getValue() + f.getValue());
}

SinglePrecisionFloat& SinglePrecisionFloat::operator*=(const SinglePrecisionFloat& f)
{
	*this = *this * f;
	return *this;
}

SinglePrecisionFloat SinglePrecisionFloat::operator*(const SinglePrecisionFloat& f) const
{
	return SinglePrecisionFloat(getValue() * f.getValue());
}

SinglePrecisionFloat& SinglePrecisionFloat::operator/=(const SinglePrecisionFloat& f)
{
	*this = *this / f;
	return *this;
}

SinglePrecisionFloat SinglePrecisionFloat::operator/(const SinglePrecisionFloat& f) const
{
	return SinglePrecisionFloat(getValue() / f.getValue());
}

HalfPrecisionFloat::HalfPrecisionFloat(double d)
{
	SinglePrecisionFloat f2(d);
	*this = HalfPrecisionFloat(f2);
}

HalfPrecisionFloat::HalfPrecisionFloat(SinglePrecisionFloat f)
{
	int newNormalizedExponent = (int) f.m_exponent - SinglePrecisionFloat::ExponentBias + HalfPrecisionFloat::ExponentBias;

	if (f.m_exponent == SinglePrecisionFloat::MaxExponentValue && f.m_mantissa != 0) // NAN
	{
		m_sign = f.m_sign;
		m_exponent = MaxExponentValue;
		m_mantissa = 0x0aa | ((f.m_mantissa >> (SinglePrecisionFloat::NumMantissaBits - HalfPrecisionFloat::NumMantissaBits)) & 0x200); // preserve qnan/snan type
	}
	else if (f.m_exponent == SinglePrecisionFloat::MaxExponentValue && f.m_mantissa == 0 // INF
			|| newNormalizedExponent > (1 << HalfPrecisionFloat::NumExponentBits)) // Normalized (very large) float -> INF half
	{
		m_sign = f.m_sign;
		m_exponent = MaxExponentValue;
		m_mantissa = 0;
	}
	else if (newNormalizedExponent > 0) // Normalized number
	{
		m_sign = f.m_sign;
		m_exponent = newNormalizedExponent;
		m_mantissa = (f.m_mantissa >> (SinglePrecisionFloat::NumMantissaBits - HalfPrecisionFloat::NumMantissaBits));
	}
	else if (newNormalizedExponent > -HalfPrecisionFloat::NumMantissaBits) // normalized (small) float -> denormalized half
	{
		m_sign = f.m_sign;
		m_exponent = 0;
		m_mantissa = (f.m_mantissa | (1 << SinglePrecisionFloat::NumMantissaBits)) >> ((SinglePrecisionFloat::NumMantissaBits - HalfPrecisionFloat::NumMantissaBits) - newNormalizedExponent + 1);
	}
	else // normalized (very small) , denormalized or zero float -> zero half
	{
		m_sign = f.m_sign;
		m_exponent = 0;
		m_mantissa = 0;
	}
}

HalfPrecisionFloat::HalfPrecisionFloat(uint sign, uint exponent, uint mantissa)
	: m_sign(sign), m_exponent(exponent), m_mantissa(mantissa)
{
	assert(sign == 0 || sign == 1);
	assert(exponent >= 0 && exponent <= MaxExponentValue);
	assert(mantissa >= 0 && mantissa <= MaxMantissaValue);
}

std::string getBinaryString(uint binaryValue, uint numExponentBits, uint numMantissaBits)
{
	uint maxExponentValue = (1 << numExponentBits) - 1;
	uint maxMantissaValue = (1 << numMantissaBits) - 1;
	std::string result;

	// Convert sign bit
	result += ((binaryValue >> (numExponentBits + numMantissaBits)) & 1) ? "1" : "0";
	result += "|";

	// Convert exponent field
	for (int digit = (int) (numExponentBits - 1 + numMantissaBits); digit >= (int) numMantissaBits; --digit)
		result += ((binaryValue >> digit) & 1) ? "1" : "0";
	result += "|";

	// Convert mantissa field
	for (int digit = (int) numMantissaBits - 1; digit >= 0; --digit)
		result += ((binaryValue >> digit) & 1) ? "1" : "0";

	return result;
}

double HalfPrecisionFloat::getValue() const
{
	double d = 0.0;
	if (m_exponent == MaxExponentValue && m_mantissa != 0) // NAN
	{
	}
	else if (m_exponent == MaxExponentValue && m_mantissa == 0) // inf
	{
		d = (m_sign ? DBL_MAX + DBL_MAX : -DBL_MAX - DBL_MAX);
	}
	else if (m_exponent > 0) // normal
	{
		int unBiasedExponent = m_exponent - ExponentBias - NumMantissaBits;
		double value = (m_mantissa | (1 << NumMantissaBits));
		if (unBiasedExponent > 0)
			value *= (1 << unBiasedExponent);
		else if (unBiasedExponent < 0)
			value /= (1 << -unBiasedExponent);
		if (m_sign)
			value = -value;
		d = value;
	}
	else if (m_exponent == 0 && m_mantissa != 0) // denormal
	{
		int unBiasedExponent = -ExponentBias - NumMantissaBits + 1;

		double value = ((double) m_mantissa) / (1 << -unBiasedExponent);

		if (m_sign)
			value = -value;

		d = value;
	}
	else // zero
	{
		d = (m_sign ? -0.0 : 0.0);
	}

	return d;
}

std::string SinglePrecisionFloat::getBinaryString() const
{
	return ::getBinaryString(m_binaryValue, NumExponentBits, NumMantissaBits);
}

std::string HalfPrecisionFloat::getBinaryString() const
{
	return ::getBinaryString(m_binaryValue, NumExponentBits, NumMantissaBits);
}

HalfPrecisionFloat& HalfPrecisionFloat::operator+=(const HalfPrecisionFloat& h)
{
	*this = *this + h;
	return *this;
}

HalfPrecisionFloat HalfPrecisionFloat::operator+(const HalfPrecisionFloat& h) const
{
	return HalfPrecisionFloat(getValue() + h.getValue());
}

