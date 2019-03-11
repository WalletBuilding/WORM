#ifndef WORMUPDATER_WORMUPDATER_P_H
#define WORMUPDATER_WORMUPDATER_P_H

#include "wormupdater.h"
#include "simplescheduler_p.h"
#include "atomfeeder.h"
#include "downloadmanager.h"

#include <QtCore/QProcess>
#include <QtCore/QLoggingCategory>
#include <QtCore/QException>

#include <exception>

namespace QtWormUpdater
{

class WormUpdaterPrivate : public QObject
{
public:
	WormUpdater *q;

	QString currentVersion;
	QList<WormUpdater::WormUpdateInfo> updateInfos;
	bool normalExit;
	int lastErrorCode;
	QByteArray lastErrorLog;

	AtomFeeder *atomFeeder;
	int currentVersionPos;
	QString newVersion;
	DownloadManager *downloadManager;

	SimpleScheduler *scheduler;

	bool runOnExit;
	QStringList runArguments;
	QScopedPointer<AdminAuthoriser> adminAuth;

	WormUpdaterPrivate(WormUpdater *q_ptr);
	~WormUpdaterPrivate();

	bool startUpdateCheck();
	void stopUpdateCheck(int delay, bool async);

	void updaterError();

public Q_SLOTS:
	void onAppAboutToExit();
	void onUpdaterReady();
	void onDownloadProgress(DownloadManager::DownloadProgress progress);
	void onDownloadFinished(DownloadManager::DownloadProgress progress);
	void onDownloadCheckSize(DownloadManager::DownloadProgress progress);

private:
	QString getDownloadUrl(QString version);
};

}

Q_DECLARE_LOGGING_CATEGORY(logWormUpdater)

#endif // WORMUPDATER_WORMUPDATER_P_H
