#include"ElGamalBase.h"
#ifndef EL_GAMAL_DECRYPTER_H
#define EL_GAMAL_DECRYPTER_H
namespace E_voting
{

	class ElGamalDecrypter: public ElGamalBase
	{
	public:
		using ElGamalBase::key_type;
	private:
		key_type m_privatkey;
	public:
		ElGamalDecrypter();
		ElGamalDecrypter(const key_type &);
		~ElGamalDecrypter();
		void set_private_key(const key_type& op_privateKey) ;
		const key_type decrypt(const std::pair<key_type,key_type>& op_chpihertext) const ;
		virtual void set_public_key(const key_type& op_prime,const key_type& op_generator,const key_type& op_y) ;
		void generate_private_key();
	};
}
#endif
