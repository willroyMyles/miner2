#ifndef GRAPHICSCARD_H
#define GRAPHICSCARD_H

#include "minerchart.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

class GraphicsCard : public QWidget
{
    Q_OBJECT

    enum class MinerConnection{
        Connected,
        Connecting,
        NotConnected,
        Inactive,
    };

    enum class CardState{
        Enabled,
        Disabled,
    };

public:
    explicit GraphicsCard(QWidget *parent = nullptr);
    void setCardName(QString name);

        void expand();

        void contract();

        void setSpeed(double rate);

        void setArmed(bool armed);

		bool getState();

        void setDotColor(MinerConnection con);

        void setStarted(bool val);

        void setHighlight(bool val);

        void setMinerProcess(MinerProcess* process);

        void startMining();

        void stopMining();

        void setColor(MinerConnection status);

		bool isMining();

		void setOn(bool value);

private:
	bool on;
    QVBoxLayout *mainLayout;
    QVBoxLayout *statusLayout, *nameHolderlayout;
    QHBoxLayout *infoLayout;
    QLabel *cardName;
    QWidget *nameHolder, *infoHolder;
    QLabel *statusLabel, *poolLabel, *speedLabel;
    QCheckBox *box;
    MinerChart *graphHolder;
    bool armed=false, mining=false;
    MinerProcess* process;
    MinerChart * info;
    QColor color;
    CardState state;



    void configureUI();
    void configureConnections();
	void configureStyleSheet();

signals:
    void cardStatus(CardState state);

public slots:
};

#endif // GRAPHICSCARD_H
