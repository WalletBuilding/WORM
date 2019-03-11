#ifndef QTWORMUPDATER_UPDATECONTROLLER_P_H
#define QTWORMUPDATER_UPDATECONTROLLER_P_H

#include "updatecontroller.h"
#include "updateinfodialog_p.h"
#include "progressdialog_p.h"

#include "wormupdater/wormupdater.h"
#include "updatecontroller.h"
#include "wormupdater/simplescheduler_p.h"

#include <QtCore/QPointer>
#include <atomic>

extern QtWormUpdater::ProgressDialog *gUpdatesProgress;
extern std::atomic<bool> running;
extern std::atomic<bool> wasCanceled;
extern QPointer<QWidget> win;
extern QtWormUpdater::UpdateController::DisplayLevel gDisplayLevel;
extern std::atomic<bool> isUpdaterRunning;


namespace QtWormUpdater
{

class UpdateControllerPrivate
{
public:
	typedef QPair<UpdateController::DisplayLevel, bool> UpdateTask;

	static QIcon getUpdatesIcon();

	UpdateController *q;

	QPointer<QWidget> window;

	WormUpdater *mainUpdater;
	bool runAdmin;
	bool adminUserEdit;
	QStringList runArgs;
	bool detailedInfo;

	QPointer<ProgressDialog> checkUpdatesProgress;

	SimpleScheduler *scheduler;

	UpdateControllerPrivate(UpdateController *q_ptr, QWidget *window);
	UpdateControllerPrivate(UpdateController *q_ptr, const QString &version, QWidget *window);
	~UpdateControllerPrivate();
};

}

#endif // QTWORMUPDATER_UPDATECONTROLLER_P_H
