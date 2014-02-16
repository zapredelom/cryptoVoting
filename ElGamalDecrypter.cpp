#include"ElGamalDecrypter.h"
#include"Primality.h"
#include<iostream>
namespace E_voting
{
	ElGamalDecrypter::ElGamalDecrypter():ElGamalBase()
	{ 
		key_type tmp(3ul);
		set_private_key(tmp);
	}
	ElGamalDecrypter::ElGamalDecrypter(const key_type& op_prvatekey)
	{
		set_private_key(op_prvatekey);
	}
	ElGamalDecrypter::~ElGamalDecrypter()
	{
	}
	void ElGamalDecrypter::set_private_key(const key_type& op_privatekey) 
	{
		m_privatkey = op_privatekey;
	}
	const ElGamalDecrypter::key_type ElGamalDecrypter::decrypt(const std::pair<key_type,key_type> & op_chiphertext)const 
	{
		key_type ret;
		key_type inv = op_chiphertext.first.mod_exp(m_privatkey,m_prime).inverte(m_prime);
		ret = (op_chiphertext.second*inv) % m_prime;
		return ret;
	}
    void ElGamalDecrypter::set_public_key(const key_type& op_prime,const key_type& op_generator,const key_type& op_y) 
	{
		ElGamalBase::set_public_key(op_prime,op_generator,op_y);
	}
	void ElGamalDecrypter::generate_private_key()
	{
		key_type prime = Primality::instance().get_next_prime();
		m_privatkey = Primality::instance().get_random_integer(prime - ElGamalDecrypter::key_type::unit);
		key_type generator =  Primality::instance().get_random_integer(prime);
		key_type y = generator.mod_exp(m_privatkey,prime);
		set_public_key(prime,generator,y);
	}

}

