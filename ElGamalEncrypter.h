#include"ElGamalBase.h"

#ifndef EL_GAMAL_ENCRYPTER_H
#define EL_GAMAL_ENCRYPTER_H
namespace E_voting
{
class ElGamalEncrypter: public ElGamalBase
{	
public:
	using ElGamalBase::key_type;
	ElGamalEncrypter();
	std::pair<key_type,key_type> encrypt(const key_type &);
    void generateSessionPrivateKey();

private:
    key_type m_sessionRandom;

};

}//namaespace end


#endif
