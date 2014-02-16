#include <random>
#include <functional>
#include<iostream>
#include<random>
#include"Primality.h"
#include<time.h>
#include<iomanip>
#include<vector>

namespace E_voting{



Primality::Primality():prime(3)
{
	key_type tmp;
	key_type two(2ul);
	tmp = two.pow(9*(key_type::lenght/10) );
	prime = get_random_integer(tmp);
}

Primality& Primality::instance()
{
    static Primality only_one;
    return only_one;
}

const  Primality::key_type Primality::get_random_integer(key_type max)
{
   /* static auto rand  = std::bind(dist,eng);
    key_type ret;
    for(size_t i=0; i < key_type::get_length(); i++)
	{
        ret.at(i) = rand();
	}
    ret.at(0) = ret.at(0) | val_type(1);
	if(max == key_type::max() )
	return ret;
    key_type tmp;
    
    tmp  = ret%max;
    tmp = tmp +1;
    return tmp;*/
	return key_type::rand(max);


}
bool    Primality::miller_rabin_test(const key_type & op, size_t sec_par)
{
    /*key_type witness;     
    key_type decrement(op - key_type::unit);
    key_type tmp;
    key_type s(key_type::zero);
    key_type r;
    while(decrement.is_even())
    {
        decrement >>=1;
        s++;
    }
    for(size_t i = 0;i<sec_par;i++)
    {
        std::cout<<"security loop\n";
        witness = get_random_integer(op - key_type(2));
        tmp = witness.mod_exp(decrement,op);
        if(tmp != key_type::unit && tmp != op - key_type::unit)
        {
			for(key_type i(key_type::zero); i < s && tmp != op - key_type::unit; ++i)
            {
                tmp = tmp*tmp;
                if(key_type::unit == tmp)
                    return false;
                if(tmp ==  op - key_type::unit)
                    continue;
                return false;
            }
        }
    }
    return true;*/
	return key_type::miller_rabin(op,sec_par);
}
const Primality::key_type Primality::prime_by_miller_rabin(key_type max)
{
    do
    {
        prime = get_random_integer(max);
    }
    while(!miller_rabin_test(prime));

    return prime;
}
const Primality::key_type Primality::get_next_prime()
{
	return prime = prime.get_next_prime(prime);

   /* do
    {
        do
        {
            prime = get_random_integer();
        }
        while(is_prime(prime));
        prime = construct_special_prime(prime);
    }
    while(is_prime(prime));
    return prime;*/
}
const Primality::key_type Primality::get_random_prime()
{
    prime = get_random_integer();
    return get_next_prime();
}
const Primality::key_type Primality::generator(const key_type& p) {
	std::vector<key_type> fact;
	key_type phi = p-key_type::unit,  n = phi;
	for (key_type i(2ul); i*i <= n; ++i)
		if (n % i == key_type::zero) 
		{
			fact.push_back (i);
			while (n % i == key_type::zero )
				n /= i;
		}
	if (n > key_type::unit)
		fact.push_back (n);
 
	for (key_type res(2ul); res<=p; ++res) {
		bool ok = true;
		for (size_t i=0; i<fact.size() && ok; ++i)
			ok &= res.mod_exp( phi / fact[i], p) != key_type::unit;
		if (ok)  return res;
	}
	return key_type::zero;
}

} 
