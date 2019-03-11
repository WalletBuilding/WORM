#ifndef QTWORMUPDATER_ADMINAUTHORIZATION_P_H
#define QTWORMUPDATER_ADMINAUTHORIZATION_P_H

#include "wormupdater/adminauthoriser.h"

namespace QtWormUpdater
{

class AdminAuthorization : public AdminAuthoriser
{
public:
	bool hasAdminRights() override;
	bool executeAsAdmin(const QString &program, const QStringList &arguments) override;
};

}

#endif // QTWORMUPDATER_ADMINAUTHORIZATION_P_H
