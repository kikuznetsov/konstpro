#include "mapocean.h"

MapOcean::MapOcean(Wt::WContainerWidget* parent)
    :Wt::WContainerWidget(parent){

    map_ = new Wt::WGoogleMap(Wt::WGoogleMap::Version3, parent);

    map_->setMapTypeControl(Wt::WGoogleMap::DefaultControl);
    map_->enableScrollWheelZoom();
    map_->setWidth(600);
    map_->setHeight(500);

    map_ ->openInfoWindow(Wt::WGoogleMap::Coordinate(50.9082, 4.66056),
               "<img src=\"http://www.emweb.be/css/emweb_small.jpg\" />"
               "<p><strong>Emweb office</strong></p>");
    Wt::WColor clr; clr.setName("red");
    map_->addCircle(Wt::WGoogleMap::Coordinate(50.9082, 4.66056),50,clr,1);
    Wt::WText* p = new Wt::WText("rgdrgrg",parent);
}
