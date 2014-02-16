#include"ElGamalBase.h"
#include"Primality.h"

namespace E_voting
{
	//const Primalirit& ElGamalBase::primality( Primalirit::instance());
	ElGamalBase::ElGamalBase()
	{
	}
	ElGamalBase::~ElGamalBase()
	{
	}
void	ElGamalBase::set_generator(const key_type& op_generator)
	{
		m_generator = op_generator;
	}
void	ElGamalBase::set_base(const key_type& op_base)
	{
		m_prime = op_base;
	}
void	ElGamalBase::set_y(const key_type& op_y)
	{
		m_y = op_y;
	}
void	ElGamalBase::set_public_key(const key_type& op_prime,const key_type& op_generator,const key_type& op_y)
	{
		set_base(op_prime);
		set_generator(op_generator);
		set_y(op_y);
	}
void	ElGamalBase::get_public_key(ElGamalBase* op2)
	{
		this->set_public_key(op2->m_prime,op2->m_generator,op2->m_y);
	}
ElGamalBase::key_type ElGamalBase::getGenerator()const
{
    return m_generator;
}
ElGamalBase::key_type ElGamalBase::getBase() const
{
    return m_prime;
}

ElGamalBase::key_type ElGamalBase::getY() const 
{
    return m_y;
}


} //namespace end
