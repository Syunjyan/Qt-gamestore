#ifndef USRSETTING_H
#define USRSETTING_H

#include <QDialog>

namespace Ui {
class usrSetting;
}

class usrSetting : public QDialog
{
    Q_OBJECT

public:
    explicit usrSetting(QWidget *parent = nullptr);
    ~usrSetting();

private:
    Ui::usrSetting *ui;
};

#endif // USRSETTING_H
