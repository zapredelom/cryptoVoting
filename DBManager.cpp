#include"DBManager.h"
#include<iostream>
namespace E_voting
{
const Chiphertext_type DBManager::m_nullValue = "";
std::string DBManager::m_lastError("no error");
DBManager::DBManager():
    m_file("election.db",std::ios::out),
    m_secureNumber(),
    m_finalized(true)
{
    if(!m_file.is_open())
    {
        std::cerr<<"cant open file;\n";
        exit(1);
    }
    m_election = m_nullValue;
    m_elector = m_nullValue;
    m_secureNumber = m_nullValue;

}
int DBManager::init()
{
    if(m_finalized)
    {
        m_election = m_nullValue;
        m_elector = m_nullValue;
        m_secureNumber = m_nullValue;
        m_finalized = false;
    return 1;
    }
    else return 0;
}

void DBManager::addElection(const Chiphertext_type & value)
{
    if(!m_finalized)
    {
        if(m_election != m_nullValue)
        {
            std::cerr<<"election alrady setted";
            exit(1);
        }
        else
        {
            m_election = value;
        }
    }
    else
    {
        std::cerr<<"not finalized\n";
        exit(1);
    }
}

void DBManager::addElector(const Chiphertext_type & value)
{
    if(!m_finalized)
    {
        if(m_elector!= m_nullValue)
        {
            std::cerr<<"election alrady setted";
            exit(1);
        }
        else
        {
            m_elector = value;
        }
    }
    else
    {
        std::cerr<<"not finalized\n";
        exit(1);
    }
}
void DBManager::addSecureNumber(const std::string & value)
{
    if(!m_finalized)
    {
        if(m_secureNumber!= m_nullValue)
        {
            std::cerr<<"m_secureNumber alrady setted";
            exit(1);
        }
        else
        {
            m_secureNumber = value;
        }
    }
    else
    {
        std::cerr<<"not finalized\n";
        exit(1);
    }

}

bool DBManager::checkConsitency()
{
    if(m_election == m_nullValue)
    {
        m_lastError = "m_election value net seted, can\'t write nullvalue to db ";
        return false;
    }
    if(m_elector == m_nullValue)
    {
        m_lastError = "m_elector value net seted, can\'t write nullvalue to db ";
        return false;
    }
    if ( m_secureNumber == m_nullValue )
    {
        m_lastError = "m_secureNumber value net seted, can\'t write nullvalue to db ";
        return false;
    }
    return true;
}

void DBManager::writeToDB()
{
    if(m_finalized)
    {
        std::cerr<<"record allrady finalized\n";
        exit(1);
    }
    else
    {
        if(true == checkConsitency())
        {
            m_file<<"election-- "<<m_election<<std::endl;
            m_file<<"elector-- " << m_elector<<std::endl;
            m_file<<"secure number--"<<m_secureNumber<<std::endl;
        }
        else
        {
            std::cerr<<m_lastError;
            exit(1);
        }
    }
}

void DBManager::finalize()
{
    m_election = m_nullValue;
    m_elector = m_nullValue;
    m_finalized = true;
}
 DBManager::~DBManager()
 {
     m_file.close();
 }

}
