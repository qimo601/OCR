#ifndef ThreadAcq_H
#define ThreadAcq_H

#include <QThread>

class ThreadAcq : public QThread
{
	Q_OBJECT

public:
	ThreadAcq(QObject  *parent = 0);
	~ThreadAcq();
	void run();
private:
	
};

#endif // ThreadAcq_H
