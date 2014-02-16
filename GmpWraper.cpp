#include"GmpWraper.h"
#include<iostream>
#include<time.h>
#include<stdexcept>
#include<assert.h>
namespace E_voting
{
	const size_t GmpWrapper::lenght =1024;
	GmpWrapper::GmpWrapper()
	{
		mpz_init(m_data);
	}
	GmpWrapper::GmpWrapper(unsigned long int op)
	{
		mpz_init_set_ui(m_data,op);
	}
	GmpWrapper::GmpWrapper(const std::string& op,const size_t& base)
	{
         std::cout<<"GmpWrapper(const std::string& op,const size_t& base)\n";
		mpz_init(m_data);
		if( 0 != mpz_set_str(m_data,op.c_str(),base) )
        {
            throw (new std::logic_error("not walid number"));
        }

	}
	GmpWrapper::GmpWrapper(const char* op, const size_t& base )
	{
		mpz_init(m_data);
		if(0 != mpz_set_str(m_data,op,base))
            throw (new std::logic_error("not walid number"));
    
	}
	GmpWrapper::GmpWrapper(const GmpWrapper& op)
	{
		mpz_init_set(m_data,op.m_data);
	}
	GmpWrapper& GmpWrapper::operator=(const GmpWrapper& op)
	{

        mpz_set(m_data,op.m_data);
		return *this;
	}
	const GmpWrapper GmpWrapper::operator+(const GmpWrapper & op) const
	{
		GmpWrapper ret;
		mpz_add(ret.m_data,m_data,op.m_data);
		return ret;
	}
	const GmpWrapper GmpWrapper::operator+=(const GmpWrapper & op)
	{
		mpz_add(m_data,m_data,op.m_data);
		return *this;
	}
	const GmpWrapper GmpWrapper::operator* ( const GmpWrapper& op2) const 
	{
		GmpWrapper ret;
		mpz_mul(ret.m_data,m_data,op2.m_data);
		return ret;
	}
	const GmpWrapper GmpWrapper::operator*=(const GmpWrapper& op)
	{
		mpz_mul(m_data,m_data,op.m_data);
		return *this;
	}
	const GmpWrapper GmpWrapper::operator-(const GmpWrapper& op)const 
	{
		GmpWrapper ret;
		mpz_sub(ret.m_data,m_data,op.m_data);
		return ret;
	}
	const GmpWrapper GmpWrapper::operator-=(const GmpWrapper& op)
	{
		mpz_sub(m_data,m_data,op.m_data);
		return *this;
	}
	const GmpWrapper GmpWrapper::operator++()
	{
		mpz_add_ui(m_data,m_data,1u);
		return *this;		
	}
	const GmpWrapper GmpWrapper::operator++(const int prefix)
	{
		GmpWrapper ret(*this);
		mpz_add_ui(m_data,m_data,1u);
		return ret;
	}
	const GmpWrapper GmpWrapper::operator--()
	{
		mpz_sub_ui(m_data,m_data,1u);
		return *this;
	}
	const GmpWrapper GmpWrapper::operator--(const int prefix)
	{
		GmpWrapper ret(*this);
		mpz_sub_ui(m_data,m_data,1u);
		return ret;
	}
	const GmpWrapper GmpWrapper::operator/(const GmpWrapper& op) const
	{
	
		GmpWrapper ret;
		mpz_fdiv_q(ret.m_data,m_data,op.m_data);
		return ret;
	}
	const GmpWrapper GmpWrapper::operator/=(const GmpWrapper& op)
	{
		mpz_fdiv_q(m_data,m_data,op.m_data);
		return *this;
	}
	const GmpWrapper GmpWrapper::operator%(const GmpWrapper& op) const
	{
		GmpWrapper ret;
		mpz_mod(ret.m_data,m_data,op.m_data);
		return ret;
	}
	const GmpWrapper GmpWrapper::operator%=(const GmpWrapper & op)
	{
		mpz_mod(m_data,m_data,op.m_data);
		return *this;
	}
	const GmpWrapper GmpWrapper::operator>>(const mp_bitcnt_t& op) const
	{
		GmpWrapper ret;
		mpz_div_2exp(ret.m_data,m_data,op);
		return ret;
	}
	const GmpWrapper GmpWrapper::operator>>=(const mp_bitcnt_t& op)
	{
		mpz_div_2exp(m_data,m_data,op);
		return *this;
	}
	const GmpWrapper GmpWrapper::operator<<(const mp_bitcnt_t& op) const
	{
		GmpWrapper ret;
		mpz_mul_2exp(ret.m_data,m_data,op);
		return ret;
	}
	const GmpWrapper GmpWrapper::operator<<=(const mp_bitcnt_t& op)
	{
		mpz_mul_2exp(m_data,m_data,op);
		return *this;
	}
	const bool GmpWrapper::operator == (const GmpWrapper& op) const
	{
		return 0 == mpz_cmp(m_data,op.m_data);
	}
	const bool GmpWrapper::operator != (const GmpWrapper& op) const
	{
		return 0 != mpz_cmp(m_data,op.m_data);
	}
	const bool GmpWrapper::operator >  (const GmpWrapper& op) const
	{
		return 0 > mpz_cmp(m_data,op.m_data);
	}
	const bool GmpWrapper::operator >= (const GmpWrapper& op) const
	{
		return 0 >= mpz_cmp(m_data,op.m_data);
	}
	const bool GmpWrapper::operator <  (const GmpWrapper& op) const
	{
		return 0 < mpz_cmp(m_data,op.m_data);
	}
	const bool GmpWrapper::operator <= (const GmpWrapper& op) const
	{
		return 0 >= mpz_cmp(m_data,op.m_data);
	}
	const bool GmpWrapper::is_even() const
	{
		return 0 != mpz_even_p(m_data);
	}
	const bool GmpWrapper::is_odd() const
	{
		return 0 != mpz_odd_p(m_data);
	}
	const GmpWrapper GmpWrapper::mod_exp(const GmpWrapper & exp,const GmpWrapper& mod)const
	{
		GmpWrapper ret;
		assert(mod != GmpWrapper::zero );
		mpz_powm(ret.m_data,m_data,exp.m_data,mod.m_data);
		return ret;
	}
	const GmpWrapper GmpWrapper::pow(const unsigned long int & op_exp) const
	{
		GmpWrapper ret;
		mpz_pow_ui(ret.m_data,m_data,op_exp);
		return ret;
	}
	const GmpWrapper GmpWrapper::inverte(const GmpWrapper & base)const
	{
		GmpWrapper ret;
		mpz_invert(ret.m_data,m_data,base.m_data);
		return ret;
	}
	const GmpWrapper GmpWrapper::get_next_prime(const GmpWrapper& op)const
	{
		GmpWrapper ret;
		mpz_nextprime(ret.m_data,op.m_data);
		return ret;
	}
	const GmpWrapper GmpWrapper::max()
	{
        static const GmpWrapper two(2);
		static const GmpWrapper m = two.pow(lenght);
		return m;
	}
	const GmpWrapper GmpWrapper::unit = GmpWrapper(1u);
	const GmpWrapper GmpWrapper::zero = GmpWrapper(0ul);
	const bool GmpWrapper::miller_rabin(const GmpWrapper & op, size_t  sec_par)
	{
		return 0 != mpz_probab_prime_p(op.m_data,sec_par);
	}
	const GmpWrapper GmpWrapper::rand(const GmpWrapper & m)
	{
		static gmp_randstate_t state;
		static bool is_set(false);
		if(!is_set)
		{
			gmp_randinit_mt(state);
			gmp_randseed(state,GmpWrapper(time(nullptr)).m_data);
			is_set = true;
		}
		GmpWrapper ret;
		mpz_urandomb(ret.m_data,state,lenght);
		return ret;
	}
	const std::string GmpWrapper::toString(int base) const
	{
		return mpz_get_str(nullptr,base,m_data);
	}
	void GmpWrapper::print() const
	{
		mpz_out_str(stdout,10,m_data);
	}
	GmpWrapper::~GmpWrapper()
	{
		mpz_clear(m_data);
	}
} //namespace end


