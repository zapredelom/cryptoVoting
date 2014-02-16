
#include<string>
#include<gmp.h>
#ifndef GMP_WRAPPER_H
#define GMP_WRAPPER_H

namespace E_voting
{
class GmpWrapper
{
private:
	mpz_t m_data;
public:
	static const size_t lenght;
	static const GmpWrapper zero;
	static const GmpWrapper unit;
	GmpWrapper();
	explicit GmpWrapper(unsigned long int op);
	explicit GmpWrapper(const char*,const size_t& base =10);
	explicit GmpWrapper(const std::string&,const size_t& base =10);
	GmpWrapper(const GmpWrapper& op);
	GmpWrapper& operator=(const GmpWrapper&);
	const GmpWrapper operator+ ( const GmpWrapper& op2) const ;
	const GmpWrapper operator+= ( const GmpWrapper& op2) ;
	const GmpWrapper operator* ( const GmpWrapper& op2) const ;
	const GmpWrapper operator*= ( const GmpWrapper& op2) ;
	const GmpWrapper operator-(const GmpWrapper& op2)const ;
	const GmpWrapper operator-=(const GmpWrapper& op2) ;
	const GmpWrapper operator++();
	const GmpWrapper operator++(const int prefix);
	const GmpWrapper operator--();
	const GmpWrapper operator--(const int prefix);
	const GmpWrapper operator/(const GmpWrapper&) const;
	const GmpWrapper operator/=(const GmpWrapper&);
	const GmpWrapper operator%(const GmpWrapper&) const;
	const GmpWrapper operator%=(const GmpWrapper&);
	const GmpWrapper operator>>(const mp_bitcnt_t&) const;
	const GmpWrapper operator>>=(const mp_bitcnt_t&);
	const GmpWrapper operator<<(const mp_bitcnt_t&) const;
	const GmpWrapper operator<<=(const mp_bitcnt_t&);
	const bool operator == (const GmpWrapper& op) const;
	const bool operator != (const GmpWrapper& op) const;
	const bool operator >  (const GmpWrapper& op) const;
	const bool operator >= (const GmpWrapper& op) const;
	const bool operator <  (const GmpWrapper& op) const;
	const bool operator <= (const GmpWrapper& op) const;
	const bool is_odd() const;
	const bool is_even() const;
	const std::string toString(int base = 10)const;
	const GmpWrapper pow(const unsigned long int & op_exp) const;
	const GmpWrapper mod_exp(const GmpWrapper& exp,const GmpWrapper & mod) const;
	const GmpWrapper inverte(const GmpWrapper& base) const;
	const GmpWrapper get_next_prime(const GmpWrapper & op) const;
	static const bool miller_rabin(const GmpWrapper &,size_t sec_par = 10);
	static const GmpWrapper rand(const GmpWrapper & m = max());
	static const GmpWrapper max();
	void print() const;
	~GmpWrapper();
};

}
#endif
