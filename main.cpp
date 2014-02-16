#include"GmpWraper.h"
#include<iostream>
#include"Primality.h"
#include"ElGamalDecrypter.h"
#include "ElGamalEncrypter.h"
#include<time.h>
int main(int argc,char* argv[])
{
  
    try
    {
	E_voting::Primality& inst = E_voting::Primality::instance();
	E_voting::ElGamalDecrypter dec ;
	dec.generate_private_key();
	E_voting::ElGamalEncrypter enc;
    E_voting::ElGamalBase::key_type a ("abcdefghijklmn",65);
	enc.get_public_key(&dec);
	E_voting::ElGamalBase::key_type message;
	int fails = 0;
    message =  inst.get_random_integer() % inst.get_random_integer();
	for(int i =0;i<500;i++)
	{
		auto chiphertext = enc.encrypt(message);
		//clock_t t = clock();
		E_voting::ElGamalBase::key_type decrypted_message = dec.decrypt(chiphertext);
		if( message != decrypted_message)
		{
			fails++;
			std::cout <<"FAIL on ";
            message.print();
            std::cout<<std::endl;
			//message.print();
			//std::cout<<"\n";
			//decrypted_message.print();
		}
	}
	std::cout<<"fails count is "<<fails<<std::endl;
    }
    catch(std::exception* x)
    {
        std::cout<<x->what();
    }


}
