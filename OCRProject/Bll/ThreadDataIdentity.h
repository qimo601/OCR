#ifndef ThreadDataIdentity_H
#define ThreadDataIdentity_H

#include <QThread>

class ThreadDataIdentity : public QThread
{
	Q_OBJECT

public:
	ThreadDataIdentity(QObject  *parent = 0);
	~ThreadDataIdentity();
	void run();
private:
	
};

#endif // ThreadDataIdentity_H
