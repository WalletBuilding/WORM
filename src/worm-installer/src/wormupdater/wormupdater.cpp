#include "wormupdater.h"
#include "wormupdater_p.h"
#include "../updatecontroller_p.h"

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QMap>

using namespace QtWormUpdater;

const QStringList WormUpdater::NormalUpdateArguments = {QStringLiteral("--updater")};
const QStringList WormUpdater::PassiveUpdateArguments = {QStringLiteral("--updater"), QStringLiteral("skipPrompt=true")};
const QStringList WormUpdater::HiddenUpdateArguments = {QStringLiteral("--silentUpdate")};

WormUpdater::WormUpdater(QObject *parent) :
	WormUpdater("", parent)
{}

WormUpdater::WormUpdater(const QString &currentVersion, QObject *parent) :
	QObject(parent),
	d(new WormUpdaterPrivate(this))
{
	d->currentVersion = currentVersion;
}

WormUpdater::~WormUpdater() {}

bool WormUpdater::exitedNormally() const
{
	return d->normalExit;
}

int WormUpdater::errorCode() const
{
	return d->lastErrorCode;
}

QByteArray WormUpdater::errorLog() const
{
	return d->lastErrorLog;
}

bool WormUpdater::willRunOnExit() const
{
	return d->runOnExit;
}

QString WormUpdater::currentVersion() const
{
	return d->currentVersion;
}

bool WormUpdater::isRunning() const
{
	return isUpdaterRunning;
}

QList<WormUpdater::WormUpdateInfo> WormUpdater::updateInfo() const
{
	return d->updateInfos;
}

bool WormUpdater::checkForUpdates()
{
	return d->startUpdateCheck();
}

void WormUpdater::abortUpdateCheck(int maxDelay, bool async)
{
	d->stopUpdateCheck(maxDelay, async);
}

int WormUpdater::scheduleUpdate(int delaySeconds, bool repeated)
{
	if((((qint64)delaySeconds) * 1000ll) > (qint64)INT_MAX) {
		qCWarning(logWormUpdater) << "delaySeconds to big to be converted to msecs";
		return 0;
	}
	return d->scheduler->startSchedule(delaySeconds * 1000, repeated);
}

int WormUpdater::scheduleUpdate(const QDateTime &when)
{
	return d->scheduler->startSchedule(when);
}

void WormUpdater::cancelScheduledUpdate(int taskId)
{
	d->scheduler->cancelSchedule(taskId);
}

void WormUpdater::runUpdaterOnExit(AdminAuthoriser *authoriser)
{
	runUpdaterOnExit(NormalUpdateArguments, authoriser);
}

void WormUpdater::runUpdaterOnExit(const QStringList &arguments, AdminAuthoriser *authoriser)
{
	d->runOnExit = true;
	d->runArguments = arguments;
	d->adminAuth.reset(authoriser);
}

void WormUpdater::cancelExitRun()
{
	d->runOnExit = false;
	d->adminAuth.reset();
}



WormUpdater::WormUpdateInfo::WormUpdateInfo() :
	name(),
	version(),
	size(0ull)
{}

WormUpdater::WormUpdateInfo::WormUpdateInfo(const WormUpdater::WormUpdateInfo &other) :
	name(other.name),
	version(other.version),
	size(other.size)
{}

WormUpdater::WormUpdateInfo::WormUpdateInfo(QString name, QString version, quint64 size) :
	name(name),
	version(version),
	size(size)
{}

QDebug &operator<<(QDebug &debug, const WormUpdater::WormUpdateInfo &info)
{
	QDebugStateSaver state(debug);
	Q_UNUSED(state);

	debug.noquote() << QStringLiteral("{Name: \"%1\"; Version: %2; Size: %3}")
					   .arg(info.name)
					   .arg(info.version.toUtf8().constData())
					   .arg(info.size);
	return debug;
}
