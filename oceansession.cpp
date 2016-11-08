#include "oceansession.h"

typedef dbo::collection<dbo::ptr<Rec>> PtrRec;
typedef dbo::collection<dbo::ptr<FiltRec>> PtrFiltRec;

OceanSession::OceanSession(dbo::SqlConnectionPool& pool):
    connectionPool_(pool){

    setConnectionPool(connectionPool_);

    mapClass<Passport>("passport");
    mapClass<Rec>("exp");
    mapClass<FiltRec>("filtexp");
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

bool OceanSession::getData(const Datatype type, const int exp_id, const Wt::WDateTime beg, const Wt::WDateTime end, std::vector<double>& res){
    switch (type) {
    case Datatype::pressure_meters:
        try {
            dbo::Transaction tr(*this);
            PtrFiltRec recs = this->find<FiltRec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.clear();
            //res.resize(recs.size());
            for(PtrFiltRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back((*i)->press);
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::pressure_mmhg:
        try {
            dbo::Transaction tr(*this);
            PtrRec recs = this->find<Rec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.resize(recs.size());
            for(PtrRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back((*i)->press);
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::surface_rec:
        try {
            dbo::Transaction tr(*this);
            PtrFiltRec recs = this->find<FiltRec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.clear();
            //res.resize(recs.size());
            for(PtrFiltRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back((*i)->press);
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::temperature :
        try {
            dbo::Transaction tr(*this);
            PtrRec recs = this->find<Rec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.resize(recs.size());
            for(PtrRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back((*i)->temp);
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    default:
        return false;
    }
}

bool OceanSession::getData(const Datatype type, const int exp_id, const Wt::WDateTime beg, const Wt::WDateTime end, std::vector<std::pair<Wt::WDateTime, double>>& res){
    switch (type) {
    case Datatype::pressure_meters:
        try {
            dbo::Transaction tr(*this);
            PtrFiltRec recs = this->find<FiltRec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.clear();
            //res.resize(recs.size());
            for(PtrFiltRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back(std::make_pair((*i)->time,(*i)->press));
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::pressure_mmhg:
        try {
            dbo::Transaction tr(*this);
            PtrRec recs = this->find<Rec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.resize(recs.size());
            for(PtrRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back(std::make_pair((*i)->time,(*i)->press));
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::surface_rec:
        try {
            dbo::Transaction tr(*this);
            PtrFiltRec recs = this->find<FiltRec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.clear();
            //res.resize(recs.size());
            for(PtrFiltRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back(std::make_pair((*i)->time,(*i)->press));
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::temperature :
        try {
            dbo::Transaction tr(*this);
            PtrRec recs = this->find<Rec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.resize(recs.size());
            for(PtrRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back(std::make_pair((*i)->time,(*i)->temp));
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    default:
        return false;
    }
}
bool OceanSession::getDataFast(const Datatype type, const int exp_id, const Wt::WDateTime beg, const Wt::WDateTime end, std::vector<std::pair<Wt::WDateTime, double>>& res){
    switch (type) {
    case Datatype::pressure_meters:
        try {
            dbo::Transaction tr(*this);
//            PtrFiltRec recs = this->find<FiltRec>().where("exp_id = ? and time >= ? and time <= ?")
//                                                            .bind(exp_id)
//                                                            .bind(beg)
//                                                            .bind(end);
            int begId = this->query<int>("select id from filtexp").where("exp_id=? and time=?")
                                                            .bind(exp_id)
                                                            .bind(beg);
            PtrFiltRec recs= this->find<FiltRec>().where("id >= ? and id <= ?")
                                                            .bind(begId)
                                                            .bind(begId+beg.secsTo(end));
            res.clear();
            //res.resize(recs.size());
            for(PtrFiltRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back(std::make_pair((*i)->time,(*i)->press));
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::pressure_mmhg:
        try {
            dbo::Transaction tr(*this);
            PtrRec recs = this->find<Rec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.resize(recs.size());
            for(PtrRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back(std::make_pair((*i)->time,(*i)->press));
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::surface_rec:
        try {
            dbo::Transaction tr(*this);
            int begId = this->query<int>("select id from filtexp").where("exp_id=? and time=?")
                                                            .bind(exp_id)
                                                            .bind(beg);
            PtrFiltRec recs= this->find<FiltRec>().where("id >= ? and id <= ?")
                                                            .bind(begId)
                                                            .bind(begId+beg.secsTo(end));
            res.clear();
            //res.resize(recs.size());
            for(PtrFiltRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back(std::make_pair((*i)->time,(*i)->press));
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::temperature :
        try {
            dbo::Transaction tr(*this);
            PtrRec recs = this->find<Rec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.resize(recs.size());
            for(PtrRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back(std::make_pair((*i)->time,(*i)->temp));
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    default:
        return false;
    }
}

bool OceanSession::getDataFast(const Datatype type, const int exp_id, const Wt::WDateTime beg, const Wt::WDateTime end, std::vector<double>& res){
    switch (type) {
    case Datatype::pressure_meters:
        try {
            dbo::Transaction tr(*this);
//            PtrFiltRec recs = this->find<FiltRec>().where("exp_id = ? and time >= ? and time <= ?")
//                                                            .bind(exp_id)
//                                                            .bind(beg)
//                                                            .bind(end);
            int begId = this->query<int>("select id from filtexp").where("exp_id=? and time=?")
                                                            .bind(exp_id)
                                                            .bind(beg);
            PtrFiltRec recs= this->find<FiltRec>().where("id >= ? and id <= ?")
                                                            .bind(begId)
                                                            .bind(begId+beg.secsTo(end));
            res.clear();
            //res.resize(recs.size());
            for(PtrFiltRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back((*i)->press);
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::pressure_mmhg:
        try {
            dbo::Transaction tr(*this);
            PtrRec recs = this->find<Rec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.resize(recs.size());
            for(PtrRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back((*i)->press);
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::surface_rec:
        try {
            dbo::Transaction tr(*this);
            int begId = this->query<int>("select id from filtexp").where("exp_id=? and time=?")
                                                            .bind(exp_id)
                                                            .bind(beg);
            PtrFiltRec recs= this->find<FiltRec>().where("id >= ? and id <= ?")
                                                            .bind(begId)
                                                            .bind(begId+beg.secsTo(end));
            res.clear();
            //res.resize(recs.size());
            for(PtrFiltRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back((*i)->press);
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    case Datatype::temperature :
        try {
            dbo::Transaction tr(*this);
            PtrRec recs = this->find<Rec>().where("exp_id = ? and time >= ? and time <= ?")
                                                            .bind(exp_id)
                                                            .bind(beg)
                                                            .bind(end);
            res.resize(recs.size());
            for(PtrRec::const_iterator i = recs.begin();i!=recs.end();++i){
                res.push_back((*i)->temp);
            }
            tr.commit();
            return true;

        } catch (std::exception& e) {
            return false;
        }
    default:
        return false;
    }
}
bool OceanSession::getData(const Result& resCh, std::vector<double>& res){
    return this->getData(resCh.getType(),resCh.getId(),resCh.getBegTime(),resCh.getEndTime(),res);
}
bool OceanSession::getData(const Result& resCh, std::vector<std::pair<Wt::WDateTime,double>>& res){
    return this->getData(resCh.getType(),resCh.getId(),resCh.getBegTime(),resCh.getEndTime(),res);
}
