#ifndef UYGULAMAHAKKINDA_H
#define UYGULAMAHAKKINDA_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
class QToolButton;
QT_END_NAMESPACE

class UygulamaHakkinda : public QDialog
{
    Q_OBJECT
public:
    UygulamaHakkinda(QWidget *parent = nullptr);
    ~UygulamaHakkinda();

private slots:
    void btnGitHubTiklandi();
    void btnTwitterTiklandi();
    void btnLinkEdinTiklandi();
    void btnWebSitesiTiklandi();
    void btnEPostaTiklandi();

private:
    QLabel *lblUygulamaIsmi;
    QLabel *lblUygulamaSurumu;
    QLabel *lblHakkinda;

    QPushButton *btnKapat;

    QToolButton *btnGitHub;
    QToolButton *btnWebSitesi;
    QToolButton *btnEPosta;
    QToolButton *btnLinkEdin;
    QToolButton *btnTwitter;


};

#endif // UYGULAMAHAKKINDA_H
