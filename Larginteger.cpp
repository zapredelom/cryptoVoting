#include<iostream>
#include"Larginteger.h"
#include<memory.h>
#include<limits>
#include<iomanip>
#include<assert.h>
#include<cstdlib>
#include<cmath>
#include<stdexcept>
#include<random>
#include<functional>


namespace E_voting{
const  Larginteger Larginteger::zero = Larginteger(0);
const  Larginteger Larginteger::unit = Larginteger(1);

const bool Larginteger::is_odd() const
{
    return 0 != ( m_data[0] & val_type(1) );
}
const bool Larginteger::is_even() const
{
    return 0 == ( m_data[0] & val_type(1) );
}

Larginteger& Larginteger::shift_right(Larginteger & val,const unsigned int count)
{
	assert( (count <= sizeof(val_type) * CHAR_BIT) && val != zero );
    unsigned int  current = lenght-1;
    while(0 == val.m_data[current] && 0 != current)
        --current;
	if (0 == current && 0 == val.m_data[current] )
        return val;
   const unsigned int nedded_bits =  ( (sizeof(val_type) * CHAR_BIT) - count);
   val_type current_ned_bits = 0;
   val_type temp;
   while(0 != current + 1)
   {
       temp =val.m_data[current];
       val.m_data[current] >>= count;
       val.m_data[current] |= current_ned_bits;
       current_ned_bits = ( temp << nedded_bits );
       //current_ned_bits = ( temp << nedded_bits ) >> nedded_bits;
       --current;
   }
	return val;
}

Larginteger& Larginteger::shift_left( Larginteger & val, const unsigned int count)
{
    assert( (count <= sizeof(val_type) * CHAR_BIT) );
    assert ( val != zero );
    unsigned int current = lenght - 1;
    while(0 == val.m_data[current] && 0 != current)
        --current;
    if (0 == current && 0 == val.m_data[current] )
        return val;
    const unsigned int nedded_bits =  ( (sizeof(val_type) * CHAR_BIT) - count);
    val_type current_ned_bits = 0;
    val_type temp;
    if(lenght - 1 == current)
    {
        val.m_data[current] <<= count;
        --current;
    }
    while (0 != current+1)
    {
        temp = val.m_data[current];
        val.m_data[current] <<= count;
        current_ned_bits = (temp >> nedded_bits);
        val.m_data[current+1] = val.m_data[current+1] | current_ned_bits;
        --current;
    }
    return val;
}

const std::pair<const Larginteger,const Larginteger> Larginteger::div(const Larginteger& op2) const
{
// Larginteger d = 0;           // частное, d = x / y
// Larginteger c = 0;           //остаток от деления, c = x % y
//// for i = maxbit(x) to 0  -- от старшего бита к младшему
//
//
// {
//     d = d << 1                //-- сдвиг влево на 1 бит, shl
//     c = c << 1                //-- сдвиг влево на 1 бит, shl
//     c = c | *this.bit[i]          -- | значит OR, копируем i-й бит x в 0й бит c
//     if (c >= y)
//     {
//         c = c - y             -- % y
//         d = d | 1             -- вычли y из c, добавим 1 к d
//     }
// }
    if(zero == *this)
        return std::make_pair(zero,zero);
	std::pair<Larginteger,Larginteger> ret  =  (*this>>1).div(op2);
	(ret.first)<<=1;
	(ret.second)<<=1;
    if(this->is_odd())
        ++(ret.second);
    if(ret.second>= op2)
    {
        ++(ret.first);
        ret.second =ret.second - op2;
    }

    return ret;
}
const std::pair<const Larginteger,const Larginteger> Larginteger::div2(const Larginteger& op2) const
{
	std::pair<Larginteger,Larginteger> ret  = std::make_pair(zero,zero);//= (*this>>1).div(op2);
	/*Larginteger tmp(*this);
	while (zero != tmp)
	{
		tmp >>=1;
		(ret.first)<<=1;
		(ret.second)<<=1;
		if(tmp.is_odd())
			++(ret.second);
		if(ret.second>= op2)
		{
			++(ret.first);
			ret.second =ret.second - op2;
		}
	}*/
	 Larginteger dividend (*this); 
     Larginteger  divisor (op2); 


    long shiftcnt (0);

    // --- Check for attempt to divide by zero ---
    if (divisor == zero)
    {
		throw std::overflow_error("dodivizion to zero");
    }

    Larginteger  quotient (zero);
    // --- Left shift divisor until it is greater than or equal to dividend ---
    // while ( divisor < dividend && ((divisor.m_units.back() & ULONG_MSB) == 0))
    while ( divisor < dividend)
    { 	
        divisor <<= 1;
        shiftcnt++;
    }

    if (divisor > dividend)      // If divisor is greater than dividend, right shift divisor
    {
        divisor >>= 1;
        shiftcnt--;   
    }

    if (shiftcnt >= 0)
    { 	
        for(long i = 0; i <= shiftcnt; i++)
        {    	
            if ( divisor <= dividend)  // If divisor is greater than dividend, then the bit is a 1 
            {       	
                dividend = dividend - divisor;     // Subtract divisor from dividend 
                divisor  >>= 1;          // Right shift divisor 
                quotient <<= 1;          // Left shift quotient
                quotient++;              // Increment quotient           // Increment quotient 
            }
            else
            {      	
                divisor >>= 1;             // Bit is 0, right shift divisor, left shift quotient
                quotient <<= 1;
            }
        }
    }

    Larginteger remainder (dividend);
	return std::make_pair(quotient,remainder);

}
//return the max value of long long int(logiclly it's the base in which integer represented in array)
const val_type Larginteger::base() const
{
    return std::numeric_limits<val_type>::max();
}

val_type Larginteger::get_big_digit(const std::string& digit)

{
    if(digit.size()> 2*sizeof(val_type))
    {
        throw (std::runtime_error("digit is too long "));
    }
    char tmp;
    val_type ret(0);
	for( unsigned int i = 0; i<digit.size();++i)
    {
       tmp = digit.at(i); 
       if(tmp >= '0'&& tmp <= '9')
       {
		   ret*=16;
           ret+= static_cast<val_type>(tmp - '0');
       }
       else if ( (tmp >= 'a' && tmp <= 'f') ||
                 (tmp >= 'A' && tmp <= 'F') )
       {
		  ret*=16;
          ret+=( (tmp >= 'a' && tmp <= 'f' ) ? static_cast<val_type>(tmp- 'a' +10) : static_cast<val_type>(tmp- 'A' +10));
       }
       else
       {
		   std::string message = digit;
		   message +=" string containas non nomeric charecter";
           throw(std::runtime_error(message));
       }
	}
    return ret;
}
//private method for filling m_data with 0
void    Larginteger::fill_0()
{
    memset(m_data, 0 ,sizeof(val_type) * lenght/ sizeof(char));
}

const Larginteger Larginteger::max()
{
    Larginteger ret;
    for(size_t i=0;i<lenght;i++)
        ret.m_data[i] = std::numeric_limits<val_type>::max();
    return ret;
}
//conversion constructor from long long int
Larginteger::Larginteger(val_type data)
{
    m_data= new val_type[lenght];
    fill_0();
    m_data[0] = data;
}
//default constructor, by default Larginteger is 0
Larginteger::Larginteger()
{
    m_data= new val_type[lenght];
    fill_0();
}
//private method for using in copy constructor and assignment operator
void	    Larginteger::copy(const Larginteger& op2)
{
   // memcpy(m_data,op2.m_data,sizeof(long long int) * 32/ sizeof(char));
	for(unsigned int i=0;i<lenght;++i)
	{
		m_data[i] = op2.m_data[i];
	}
}
//copy constructor
Larginteger::Larginteger(const Larginteger& op2)
{
    m_data= new val_type[lenght];
    copy(op2);
}
Larginteger::Larginteger(Larginteger&& op2)
{
    m_data = op2.m_data;
    op2.m_data=nullptr;
}
//casting constructor from std::string to long integer
Larginteger::Larginteger(const std::string& number)
{
    m_data= new val_type[lenght];
    fill_0();
    unsigned int digit_leght = (sizeof(val_type) * 2);
	
    if(number.size() > lenght * digit_leght )
    {
        throw(std::runtime_error("too big integer, max limit is 2^2048"));
    }

	if(number.size() % digit_leght)
	{
		m_data[number.size() / digit_leght]  = get_big_digit(number.substr(0,number.size() % digit_leght) );
	}
	int digits = number.size() / digit_leght;
	for(int i = 0;i< digits;i++)
	{
		m_data[number.size()/digit_leght-i-1] =get_big_digit( number.substr(number.size() % digit_leght +i*digit_leght, digit_leght) );
	}
}
//copy assignmet opreator
Larginteger& Larginteger::operator=(const Larginteger& op2)
{
	copy(op2);
	return *this;
}
Larginteger& Larginteger::operator=(Larginteger&& op2)
{
    m_data = op2.m_data;
    op2.m_data = nullptr;
    return *this;
}
//big operator
bool Larginteger::operator>(const Larginteger& op2) const
{
	int i;
	for(i=lenght-1; i>=0 && op2.m_data[i] == m_data[i] ; --i);
	return (-1 == i ? false : (m_data[i] > op2.m_data[i]));
}
//less operatro
bool Larginteger::operator<(const Larginteger & op2)const
{
	int i;
	for(i=lenght-1 ; i>=0 && op2.m_data[i] == m_data[i] ; --i);

return (-1 == i ? false: (m_data[i] < op2.m_data[i]));
}
//big or equal operator
bool Larginteger::operator<=(const Larginteger& op2) const
{
	return !(this->operator>(op2));
}
bool Larginteger::operator>=(const Larginteger& op2)const
{
	return !(this->operator<(op2));
}
bool Larginteger::operator==(const Larginteger& op2) const
{
	return 0 == memcmp(m_data,op2.m_data,lenght * sizeof(val_type));
}
bool Larginteger::operator!=(const Larginteger& op2)const
{
	return 0 != memcmp(m_data,op2.m_data,lenght * sizeof(val_type));
}
const Larginteger Larginteger::operator+(const Larginteger& op2) const
{
	const Larginteger & max = (this->operator>(op2) ? *this : op2);
	const Larginteger & min = (this->operator<=(op2) ? *this : op2);
	Larginteger ret(0);
	val_type over = 0;
//cheek for overflow
#ifdef NDEBUG
    if( (0 != max.m_data[lenght -1] && 0 != min.m_data[lenght - 1])  && 
      ( (max.m_data[lenght -1] * min.m_data [lenght - 1] <max.m_data[lenght -1]) ||
        (max.m_data[lenght -1] * min.m_data [lenght - 1] < min.m_data[lenght -1]) ) )
        throw (std::runtime_error("integer too big, max limit is 2^64")) ;
#endif        
	for(unsigned int i= 0 ;i<lenght; ++i)
	{
		ret.m_data [i] = max.m_data[i] + min.m_data[i]+over;
		if(ret.m_data[i] < min.m_data[i] )
		{
			if( lenght == i+1 )
			{
				throw (std::overflow_error("integer too big, max limit is 2^64")) ;
			}
			else
			{
				over++;
			}
		}
		else
			over = 0;
	}
	return ret;
}
const Larginteger Larginteger::operator-(const Larginteger& op2) const
{
    Larginteger ret = *this;
    const Larginteger& les = op2;
#ifdef NDEBUG
    if(*this < op2)
        throw std::overflow_error("return value is less then zero");
#endif
    size_t i=0;
    val_type tmp=0;
    while(i< lenght)
    {
        if(ret.m_data[i] >= les.m_data[i] +tmp )
        {
            ret.m_data[i] =ret.m_data[i]- les.m_data[i]-tmp;
            tmp =  0;
        }
        else
        {
            ret.m_data[i] = ret.m_data[i]  - les.m_data[i] - tmp;
            tmp = 1;
        }
        ++i;
    }
    return ret;
}

const Larginteger Larginteger::operator++()
{
    size_t i=0;
    val_type tmp = m_data[i];
    while(tmp > ++m_data[i] && i<lenght)
    {
        i++;
        tmp=m_data[i];
    }
	return *this;
}

const Larginteger Larginteger::operator++(int postfix)
{
    Larginteger ret = *this;
    size_t i=0;
    val_type tmp = m_data[i];
    while(tmp > ++m_data[i] && i<lenght)
    {
        i++;

        tmp=m_data[i];

    }

	return ret;
}
const Larginteger Larginteger::operator--()
{
    size_t i =0;
    while(0 == m_data[i] && i<=lenght)
    { 
        m_data[i] = std::numeric_limits<val_type>::max();
        i++;
    }
    if(i == lenght)
    {
#ifdef NDEBUG
        throw std::overflow_error("return value is less then zero");
#endif
        return max();
    }
    else
        --m_data[i];
return *this;
}
const Larginteger Larginteger::operator--(const int prefix)
{
    Larginteger tmp = *this;
    size_t i =0;
    while(0 == m_data[i] && i<=lenght)
    {
        m_data[i] = std::numeric_limits<val_type>::max();
        i++;
    }
    if(i == lenght)
    {
#ifdef NDEBUG
        throw std::overflow_error("return value is less then zero");
#endif
        return max();
    }
    else
        --m_data[i];
return tmp;
}

const Larginteger Larginteger::operator+=(const Larginteger& op2)
{
    *this = *this + op2;
    return *this;
}
const Larginteger Larginteger::operator>>(const unsigned int count) const 
{
    if(this->operator==(zero) )
        return *this;
    unsigned int shift = count /  (sizeof ( m_data[0] ) * CHAR_BIT);
    Larginteger ret;
    for (unsigned int i = 0; i + shift < lenght; i++)
    {
       ret.m_data[i] = m_data[i+shift];
    }
    if(count % (sizeof(val_type) * CHAR_BIT) )
        shift_right(ret,count % (sizeof(val_type) * CHAR_BIT));
    return ret;
}
const Larginteger Larginteger::operator>>=(const unsigned int count)
{
    *this = this->operator>>(count);
    return *this;
}
const Larginteger Larginteger::operator<<(const unsigned int count) const
{

    if( this->operator==( zero ) )
        return *this;
	Larginteger ret;
	unsigned int shift = count / (sizeof ( m_data[0] ) * CHAR_BIT);
    for(unsigned int i =0; i+shift<lenght; i++)
    {
        ret.m_data[i+shift] = m_data[i];
    }
    if(Larginteger (0) == ret)
        return ret;
    if(count % (sizeof(m_data[0]) * CHAR_BIT))
        shift_left(ret,count % (sizeof(m_data[0]) * CHAR_BIT));
    return ret;
}

const Larginteger Larginteger::operator<<=(const unsigned int count)
{
    *this = this->operator<<(count);
    return *this;
}

const Larginteger Larginteger::operator*(const Larginteger& op2) const
{
    Larginteger ret;
    Larginteger big = *this;
    Larginteger less = op2;
    while (zero != less)
    {
        if( less.is_odd() )
            ret += big;
        less>>=1;
        big<<=1;
    }
    return ret;
}

const Larginteger Larginteger::operator/(const Larginteger& op2) const
{
    return (this->div(op2)).first;
}

const Larginteger Larginteger::operator%(const Larginteger& op2) const
{
	
	/*if(zero  ==  *this) 
		return zero;
	Larginteger rem = ((*this)>>1)%op2;
	rem <<= 1;
	if(this->is_odd())
		++rem;
	if(rem < op2)
		return rem;
	return rem - op2;
*/

    return (this->div(op2)).second;
}

const Larginteger Larginteger::pow(const Larginteger& op2) const
{
    if(zero == *this)
        return *this;
    if(zero == op2)
        return unit;
    Larginteger ret = *this;
    Larginteger exp=op2;
    Larginteger additional(1);
    while( unit != exp )
    {
        if( exp.is_odd()  )
            additional=additional * ret;
        ret = ret * ret;
        exp>>=1;
    }
    ret=ret * additional;
    return ret;
}
const Larginteger Larginteger::mod_exp(Larginteger exp , const Larginteger& mod)
{
    Larginteger ret = unit;
    if(unit == exp)
        return ret;
    if(exp.is_odd())
        ret = *this;
    Larginteger additional = *this;
    while( zero != exp)
    {
       additional = (additional *additional)%mod;
       exp >>= 1;
       if(exp.is_odd())
           ret = (ret* additional )% mod;
    }
    return ret;
}
    
val_type& Larginteger::at(size_t i)
{
#ifdef NDEBUG
    if(i>lenght)
        throw (std::out_of_range("index is out of Larginteger bounds"));
#endif
    return m_data[i];
}
void Larginteger::print() const
{
    int i=lenght-1;
    while(0 == m_data[i] && 0 != i)
        --i;
	for(;i>=0;--i) 
		std::cout<<std::setbase(16)<<m_data[i]<<" ";
    std::cout<<std::endl;
}
const Larginteger Larginteger::rand(const Larginteger& m  )
{
	std::uniform_int_distribution<val_type> dist;
	std::mt19937_64 eng;
	eng.seed(clock());
	static auto rand  = std::bind(dist,eng);
    Larginteger ret;
    for(size_t i=0; i < get_length(); i++)
	{
        ret.at(i) = rand();
	}
    ret.at(0) = ret.at(0) | val_type(1);
	if(m == Larginteger::max() )
	return ret;
    Larginteger tmp;
    
    tmp  = ret%m;
    tmp = tmp +1;
    return tmp;
}

}//end of namspace E_voting
