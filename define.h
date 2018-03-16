#ifndef DEFINE_H
#define DEFINE_H

#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#define MASTER_ID "admin"
#define MASTER_PASSWORD "admin"

#define MENU_MAIN tr("Main")
#define MENU_CONFIGURATION tr("Configuration")

#define APPLICATION_EXIT 0
#define APPLICATION_LOGOUT 1

extern QString g_UserID;
extern QString g_Password;

#endif // DEFINE_H
