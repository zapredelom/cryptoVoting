#include "ElGamalEncrypter.h"
#include "Primality.h"

namespace E_voting{

ElGamalEncrypter::ElGamalEncrypter():ElGamalBase()
{
}

std::pair<ElGamalEncrypter::key_type,ElGamalEncrypter::key_type> ElGamalEncrypter::encrypt(const key_type& op_message)
{
	key_type first, second;
//	m_sessionRandom = Primality::instance().get_random_integer();
	first = m_generator.mod_exp(m_sessionRandom,m_prime);
	second = m_y.mod_exp(m_sessionRandom,m_prime);
	second = ( op_message * second) %  m_prime;
	return std::make_pair(first,second);
}

void ElGamalEncrypter::generateSessionPrivateKey()
{
    m_sessionRandom = Primality::instance().get_random_integer();
}

}
