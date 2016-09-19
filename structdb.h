#ifndef STRUCTDB_H
#define STRUCTDB_H

#include <string.h>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/WDateTime>

using namespace std;
namespace dbo = Wt::Dbo;

class Rec;
class Passport;

//Place
class Place{
public:
    std::string placeId; //natural ID, max 3 simbols, like "IZM"
    std::string fullName;
    double lat;
    double log;
    std::string notes;

    Wt::Dbo::collection< Wt::Dbo::ptr<Passport> > exps;

    //Relations: one place has many experiments
    template<class Action>
    void persist(Action& a)
    {
        Wt::Dbo::id(a, placeId,     "id", 3); //natural ID
        Wt::Dbo::field(a, fullName, "fullname");
        Wt::Dbo::field(a, lat,      "lat");
        Wt::Dbo::field(a, log,      "log");
        Wt::Dbo::field(a, notes,    "notes");

        Wt::Dbo::hasMany(a, exps, Wt::Dbo::ManyToOne, "place");
    }
    Place(){
        this->placeId = "IZM";
        this->fullName = "";
        this->lat=0;
        this->log=0;
        this->notes="";
    }
    Place(std::string placeId_){
        this->placeId = placeId_;
        this->fullName = placeId_;
        this->lat = 0;
        this->log = 0;
        this->notes = "-";
    }
};

namespace Wt {
    namespace Dbo {
    //settings for place
    template<> struct dbo_traits<Place> : public dbo_default_traits {
        typedef std::string IdType;
        static IdType invalidId() {
            return std::string();
        }
        static const char *surrogateIdField() { return 0; }
    };

    }
}

//Passport
class Passport{
public:
    //string place;
    dbo::ptr<Place> place;
    double lat;
    double lon;
    double depth;
    string nameGauge;
    double hz;
    Wt::WDateTime begTime;
    Wt::WDateTime endTime;
    string notes;

    dbo::collection< dbo::ptr<Rec> > recs; //needed for relations with records

    //Relations
    template<class Action>
    void persist(Action& a)
    {
//      dbo::field(a, place,     "place");
        dbo::belongsTo(a, place, "place");

        dbo::field(a, nameGauge, "nameGauge");
        dbo::field(a, lat,       "lat");
        dbo::field(a, lon,       "lon");
        dbo::field(a, depth,     "depth");
        dbo::field(a, hz,        "hz");
        dbo::field(a, begTime,   "begTime");
        dbo::field(a, endTime,   "endTime");
        dbo::field(a, notes,     "notes");

        dbo::hasMany(a, recs, dbo::ManyToOne, "exp");
    }
};
namespace Wt {
    namespace Dbo {
    //Settings for Passport
    template<> struct dbo_traits<Passport> : public dbo_default_traits {
        static const char *versionField() {
            return 0;
        }
    };
    }
}

//Rec
class Rec{
public:

    Wt::WDateTime time;
    double press;
    double temp;

    dbo::ptr<Passport> exp; //relations with separate experiment

    //Constructors
    Rec(){
        time = Wt::WDateTime();
        press = 0;
        temp = 0;
        //Passport* exp1 = new Passport();
        //exp = dbo::ptr<Passport>(NULL);
    }
    Rec(std::string& time1, double press1, double temp1){
        time = Wt::WDateTime::fromString(time1,"dd.MM.yy HH:mm:ss");
        press = press1;
        temp = temp1;
    }
    Rec(Wt::WDateTime time1, double pr1, double temp1){
        time = time1;
        press = pr1;
        temp = temp1;
    }
    ~Rec(){
        //std::cout<<"destructor";
    }
    //Relations
    template<class Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, time, "time");
        Wt::Dbo::field(a, press,"press");
        Wt::Dbo::field(a, temp, "temp");

        dbo::belongsTo(a, exp,  "exp");
    }
};

namespace Wt {
    namespace Dbo {
    //Settings for Rec
    template<> struct dbo_traits<Rec> : public dbo_default_traits {
        static const char *versionField() {
            return 0;
        }
    };
    }
}


#endif // STRUCTDB_H
