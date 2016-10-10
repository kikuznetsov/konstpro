#include "oceansession.h"

OceanSession::OceanSession(dbo::SqlConnectionPool& pool):
    connectionPool_(pool){

    setConnectionPool(connectionPool_);

    mapClass<Passport>("passport");
    mapClass<Rec>("exp");
    mapClass<Place>("place");

}

dbo::SqlConnectionPool *OceanSession::createConnectionPool(const std::string& sqliteDb)
{
  dbo::backend::Sqlite3 *connection = new dbo::backend::Sqlite3(sqliteDb);

//  connection->setProperty("show-queries", "true");
//  connection->setDateTimeStorage(Wt::Dbo::SqlDateTime,
//                 Wt::Dbo::backend::Sqlite3::PseudoISO8601AsText);

  return new dbo::FixedSqlConnectionPool(connection, 10);
}
