#ifndef DIALOGEXAMPLE_H
#define DIALOGEXAMPLE_H

#include <Wt/WApplication>
#include <Wt/WMessageBox>

using namespace Wt;

/**
 * \defgroup dialog Dialog example
 */
/*@{*/

/*! \brief An example illustrating usage of Dialogs
 */
class DialogExample : public WApplication
{
public:
  /*! \brief Create the example application.
   */
  DialogExample(const WEnvironment& env);

private:
  void messageBox1();
  void messageBox2();
  void messageBox3();
  void messageBox4();
  void custom();

  void messageBoxDone(StandardButton result);

  void setStatus(const WString& text);

  WMessageBox *messageBox_;
  WText *status_;
};

#endif // DIA#ifndef DIALOGEXAMPLE_H
