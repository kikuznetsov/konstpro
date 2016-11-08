#ifndef OCEANSESSION_H
#define OCEANSESSION_H


#include <Wt/Dbo/FixedSqlConnectionPool>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/backend/Sqlite3>
#include "structdb.h"
#include "resultchoose.h"

class OceanSession: public dbo::Session{

public:
    OceanSession(dbo::SqlConnectionPool& pool);
    static dbo::SqlConnectionPool *createConnectionPool(const std::string& sqlite3Name);

    bool getData(const Datatype type,const int exp_id, const Wt::WDateTime beg, const Wt::WDateTime end, std::vector<double>& res);
    bool getData(const Datatype type, const int exp_id, const Wt::WDateTime beg, const Wt::WDateTime end, std::vector<std::pair<Wt::WDateTime, double>>& res);

    bool getDataFast(const Datatype type,const int exp_id, const Wt::WDateTime beg, const Wt::WDateTime end, std::vector<double>& res);
    bool getDataFast(const Datatype type, const int exp_id, const Wt::WDateTime beg, const Wt::WDateTime end, std::vector<std::pair<Wt::WDateTime, double>>& res);

    bool getData(const Result& resChoose, std::vector<double>& res);
    bool getData(const Result& resChoose, std::vector<std::pair<Wt::WDateTime,double>>& res);

private:
    dbo::SqlConnectionPool& connectionPool_;
};
#endif // OCEANSESSION_H
