#ifndef OCEANSESSION_H
#define OCEANSESSION_H


#include <Wt/Dbo/FixedSqlConnectionPool>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/backend/Sqlite3>
#include "structdb.h"

class OceanSession: public dbo::Session{

public:
    OceanSession(dbo::SqlConnectionPool& pool);
    static dbo::SqlConnectionPool *createConnectionPool(const std::string& sqlite3Name);

private:
    dbo::SqlConnectionPool& connectionPool_;
};
#endif // OCEANSESSION_H
