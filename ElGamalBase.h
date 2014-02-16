#include "GmpWraper.h"
#ifndef EL_GAMAL_BASE_H
#define EL_GAMAL_BASE_H
class Primalirit;

namespace E_voting
{

class ElGamalBase
{
public:
typedef GmpWrapper key_type;
protected:
	key_type m_prime;
	key_type m_generator;
	key_type m_y;
	//static const Primalirit& primality;
public:
	ElGamalBase();
	virtual void get_public_key(ElGamalBase*);
    virtual key_type getGenerator() const ;
    virtual key_type getBase()const;
    virtual key_type getY()const;
	virtual void set_public_key(const key_type& op_prime,const key_type& op_generator,const key_type& op_y);
	virtual void set_base(const key_type&);
	virtual void set_generator(const key_type&);
	virtual void set_y(const key_type&);
	virtual ~ElGamalBase();
};
}//namespace end

#endif
