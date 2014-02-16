#include<string>
#include<fstream>
#include<cstdlib>
#ifndef DBMANAHER_H
#define DBMANAGER_H

namespace E_voting
{
typedef std::string Chiphertext_type ;

class DBManager
{

public:
    DBManager();
    int init();
    void addElection(const Chiphertext_type&);
    void addElector(const Chiphertext_type&);
    void addSecureNumber(const std::string&);
    void  writeToDB();
    void finalize();
    ~DBManager();
private:
    bool checkConsitency();
    static std::string m_lastError;
    static const Chiphertext_type m_nullValue;
    std::ofstream m_file;
    Chiphertext_type m_election;
    Chiphertext_type m_elector;
    std::string m_secureNumber;
    bool m_finalized;
};

}
#endif

