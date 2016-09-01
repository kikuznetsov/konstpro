#ifndef HOME_H
#define HOME_H

#include <Wt/WApplication>
#include <Wt/WLineEdit>
#include <Wt/WMenu>
#include <Wt/WMessageBox>
#include <Wt/WNavigationBar>
#include <Wt/WPopupMenu>
#include <Wt/WPopupMenuItem>
#include <Wt/WStackedWidget>
#include <Wt/WText>
#include <Wt/WBootstrapTheme>

using namespace Wt;

class Site : public WApplication
{
public:

  Site(const WEnvironment& env);

private:
  Wt::WContainerWidget *bodyContainer;
  Wt::WNavigationBar *navigation;
  Wt::WMenu *leftMenuNav;
  //Wt::WMenu *menuModule;

};

#endif // HOME_H
