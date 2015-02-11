
#ifndef FloatTypes_h
#define FloatTypes_h

#include <string>

typedef unsigned int uint;

class HalfPrecisionFloat;
class SinglePrecisionFloat;

class SinglePrecisionFloat
{
public:
	explicit SinglePrecisionFloat(double d);
	SinglePrecisionFloat(uint sign, uint exponent, uint mantissa);

	double getValue() const;
	std::string getBinaryString() const;

	SinglePrecisionFloat operator+(const SinglePrecisionFloat& f) const;
	SinglePrecisionFloat& operator+=(const SinglePrecisionFloat& f);

	SinglePrecisionFloat operator*(const SinglePrecisionFloat& f) const;
	SinglePrecisionFloat& operator*=(const SinglePrecisionFloat& f);

	SinglePrecisionFloat operator/(const SinglePrecisionFloat& f) const;
	SinglePrecisionFloat& operator/=(const SinglePrecisionFloat& f);

	enum { NumExponentBits = 8 };
	enum { NumMantissaBits = 23 };
	enum { ExponentBias = 127 };
	enum { MaxExponentValue = (1 << NumExponentBits) - 1 };
	enum { MaxMantissaValue = (1 << NumMantissaBits) - 1 };

	union
	{
		struct
		{
			uint m_mantissa : NumMantissaBits;
			uint m_exponent : NumExponentBits;
			uint m_sign : 1;
		};
		float m_floatValue;
		uint m_binaryValue;

	};
};

class HalfPrecisionFloat
{
public:
	explicit HalfPrecisionFloat(double d);
	HalfPrecisionFloat(SinglePrecisionFloat f);
	HalfPrecisionFloat(uint sign, uint exponent, uint mantissa);

	double getValue() const;
	std::string getBinaryString() const;

	HalfPrecisionFloat operator+(const HalfPrecisionFloat& h) const;
	HalfPrecisionFloat& operator+=(const HalfPrecisionFloat& h);

	enum { NumExponentBits = 5 };
	enum { NumMantissaBits = 10 };
	enum { ExponentBias = 15 };
	enum { MaxExponentValue = (1 << NumExponentBits) - 1 };
	enum { MaxMantissaValue = (1 << NumMantissaBits) - 1 };

	union
	{
		struct
		{
			uint m_mantissa : NumMantissaBits;
			uint m_exponent : NumExponentBits;
			uint m_sign : 1;
		};
		uint m_binaryValue;
	};
};


#endif // FloatTypes_h
