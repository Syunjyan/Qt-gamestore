#ifndef USRSETTING_H
#define USRSETTING_H

#include <QWidget>

namespace Ui {
class usrSetting;
}

class usrSetting : public QWidget
{
    Q_OBJECT

public:
    explicit usrSetting(QWidget *parent = nullptr);
    ~usrSetting();

private:
    Ui::usrSetting *ui;
};

#endif // USRSETTING_H
