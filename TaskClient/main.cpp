#include <QtWidgets/QApplication>
#include "TRAuthForm.h"
//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TRAuthForm auth_form;
    auth_form.show();

    return a.exec();
}
//-----------------------------------------------------------------------------
