#ifndef MINERUI_H
#define MINERUI_H

#include "QtAwesome.h"
#include "graphicscard.h"
#include "minerprocess.h"
#include "settingsmanager.h"


#include <QComboBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QWidget>

class MinerManager;
class SettingsManager;
class MinerProcess;
class MinerUI : public QWidget
{
    Q_OBJECT

public:
    MinerUI(QWidget *parent = Q_NULLPTR);
    ~MinerUI();

    bool isMining();
	void startMining();
	void stopMining();
	void restartMining();
	bool shouldAutoMine();

private:
    bool mining;
	bool autoStart;

    MinerManager* minerMan;
    SettingsManager *settingsMan;
    QtAwesome *fontIcon;

    QHBoxLayout *topLayout;
    QVBoxLayout *leftLayout, *mainLayout;
    QVBoxLayout *rightLayout;
    QWidget *buttonHolder;
    QVBoxLayout *buttonLayout;



    QStackedWidget *stack;

    QWidget *dashPage, *settingsPage, *blogPage, *aboutPage;
    QPushButton *dashBtn, *settingsBtn, *blogBtn, *aboutBtn;
    QPushButton *startBtn, *confirmBtn, *cancelBtn;
    GraphicsCard *card;

    QScrollArea *scrollArea;
    QWidget *scrollContents;
    QVBoxLayout *scrollLayout;
    QVBoxLayout *scrollareaLayout;

    QVBoxLayout *dashLayout;

    QLineEdit *walletEdit, *passwordEdit, *poolEdit, *identifierEdit;
    QComboBox *currency;

    QString walletIdText, poolText, passwordText, identifierText;



    void configureUI();
    void configureDash();
    void configureSettings();
    void configureBlog();
    void configureAbout();
    void configureConnections();
    void saveAndApplySettings();
    void restoreSettings();
	void configureStyleSheet();
	void configureFontIcons();

    

    void resetSettings();
signals:
    void indexChanged(int);

};

#endif // MINERUI_H
