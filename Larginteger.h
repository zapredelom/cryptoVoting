#ifndef Larginteger_H
#define Larginteger_H
#define CHAR_BIT 8
class string;
class ostream;
class istream;
#include<string>
#include<utility>
namespace E_voting
{
typedef unsigned long long int val_type;
const val_type size =2048;
class Larginteger
{	
friend const ostream& operator<<(const ostream&,const Larginteger&);
friend const istream& operator>>(const istream&,Larginteger&);
private:
	static const size_t            lenght = size / (sizeof(val_type) *CHAR_BIT);
    val_type*         m_data;
    void                           fill_0();
    void                           copy(const Larginteger&);
    val_type                       get_big_digit(const std::string &);
    const val_type                 base() const;
    static Larginteger&			   shift_right(Larginteger& , unsigned int );
    static Larginteger&			   shift_left( Larginteger& , unsigned int );
	static val_type                reverse(val_type val);
public:
	const std::pair<const Larginteger,const Larginteger> div(const Larginteger&) const;
	const std::pair<const Larginteger,const Larginteger> div2(const Larginteger&) const;
	static const Larginteger zero; 
	static const Larginteger unit;
	static const size_t get_length()
	{
		return lenght;
	}
    const  bool                    is_odd()const;
    const  bool                    is_even()const;
    Larginteger();
    Larginteger(val_type);
    Larginteger(const std::string&);
    Larginteger(const Larginteger&);
    Larginteger(Larginteger&&);
    Larginteger&      operator=(const Larginteger&);
    Larginteger&      operator=(Larginteger&&);
    static const Larginteger max();
    const Larginteger operator+(const Larginteger &) const;
	const Larginteger operator++();
	const Larginteger operator++(int postfix);
    const Larginteger operator+=(const Larginteger& op2);
	const Larginteger operator>>(const unsigned int count) const;
    const Larginteger operator>>=(const unsigned int count);
	const Larginteger operator<<(const unsigned int count) const;
    const Larginteger operator<<=(const unsigned int count);
    const Larginteger operator-(const Larginteger&) const;
	const Larginteger operator--();
	const Larginteger operator--(int prefix );
    const Larginteger operator*(const Larginteger& op2)const;
    const Larginteger operator/ (const Larginteger&) const;
    const Larginteger operator% (const Larginteger&) const;
    bool              operator< (const Larginteger&) const;
    bool              operator> (const Larginteger&) const;
    bool              operator>= (const Larginteger&) const;
    bool              operator<= (const Larginteger&) const;
	bool			  operator== (const Larginteger&) const;
	bool			  operator!= ( const Larginteger& ) const;
    const Larginteger pow(const Larginteger& ) const;
    const Larginteger mod_exp(Larginteger , const Larginteger& mod);
    val_type& at(size_t);
	void print()const ;
	static const Larginteger rand(const Larginteger& m = Larginteger::max());
    ~Larginteger()
    {
        delete[]  m_data;
    }
};

}//end of namespace E_voting
#endif
