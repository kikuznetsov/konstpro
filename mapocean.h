#ifndef MAPOCEAN_H
#define MAPOCEAN_H

#include <Wt/WInteractWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WGoogleMap>
#include <Wt/WPushButton>

class MapOcean: public Wt::WContainerWidget{
public:
    MapOcean(Wt::WContainerWidget *parent = 0);
private:
    Wt::WGoogleMap *map_;

};
#endif // MAPOCEAN_H
