#ifndef COMMON_H
#define COMMON_H

#include <QObject>

class common : public QObject
{
	Q_OBJECT

public:
	common(QObject *parent);
	~common();

private:
	
};

#endif // COMMON_H
