#include "site.h"
#include "content.h"
#include "homepage.h"
#include "cvpage.h"

using namespace Wt;

Site::Site(const WEnvironment& env)
  : WApplication(env)
{
    setTitle("Konstantin Kuznetsov");

    //set theme to Bootstrap
    WBootstrapTheme* wbtsp = new WBootstrapTheme();
    wbtsp->setVersion(WBootstrapTheme::Version3);
    setTheme(wbtsp);

    root()->setContentAlignment(AlignCenter); //set all content to center

    bodyContainer = new Wt::WContainerWidget(root());
    bodyContainer->setMaximumSize(900,10000);
    //WVBoxLayout* bodyLayout = new WVBoxLayout();


    navigation = new Wt::WNavigationBar(bodyContainer);
    navigation->setTitle("Konstantin Kuznetsov",
                 "http://konst.pro/");
    navigation->setResponsive(true);


    Wt::WStackedWidget* contentsStackBody = new Wt::WStackedWidget(bodyContainer);



    //Content cnt("homePage.html");
    //Setup a Left-aligned menu.
    leftMenuNav = new Wt::WMenu(contentsStackBody, bodyContainer);
    navigation->addMenu(leftMenuNav);

    //HomePage* hPage = new HomePage(bodyContainer);

    leftMenuNav->addItem("Home", new HomePage());
    leftMenuNav->addItem("CV", new CvPage());
    leftMenuNav->addItem("Publications", new Wt::WText("dfsf!"));
    leftMenuNav->addItem("Blog", new Wt::WText("sfsdfsss!"));
    leftMenuNav->addItem("Contacts", new Wt::WText("sfsdfsss!"));

    bodyContainer->addWidget(contentsStackBody);

}