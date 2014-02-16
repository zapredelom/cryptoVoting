#include"GmpWraper.h"
#include<random>
#ifndef PRIMALITY_H
#define PRIMALITY_H
namespace E_voting{

class Primality
{
public:
    typedef GmpWrapper key_type;
private:
        key_type prime ;
        Primality();
#ifdef __GNUC__
        Primality(const Primality&) = delete;
        Primality(Primality&&) = delete;
        Primality& operator=(const Primality &) = delete;
#else
		Primality(const Primality&);
        Primality(Primality&&);
        Primality& operator=(const Primality &);
#endif
        bool miller_rabin_test(const key_type & op, size_t sec_par=10);
public:
	    static Primality& instance();
		const key_type get_next_prime();
        const key_type get_random_prime();
		const key_type get_random_integer(key_type max = key_type::max());
        const key_type prime_by_miller_rabin(key_type max = key_type::max());  
		const key_type generator(const key_type& p);
};
}
#endif


