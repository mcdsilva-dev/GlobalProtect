#ifndef PORTALAUTHENTICATOR_H
#define PORTALAUTHENTICATOR_H

#include <QtCore/QObject>

#include "portalconfigresponse.h"
#include "standardloginwindow.h"
#include "samlloginwindow.h"
#include "preloginresponse.h"


class PortalAuthenticator : public QObject
{
    Q_OBJECT
public:
    explicit PortalAuthenticator(const QString& portal, const QString& clientos);
    ~PortalAuthenticator();

    void authenticate();

signals:
    void success(const PortalConfigResponse response, const QString region);
    void fail(const QString& msg);
    void preloginFailed(const QString& msg);
    void portalConfigFailed(const QString msg);

private slots:
    void onPreloginFinished();
    void onPerformNormalLogin(const QString &username, const QString &password);
    void onLoginWindowRejected();
    void onLoginWindowFinished();
    void onSAMLLoginSuccess(const QMap<QString, QString> samlResult);
    void onSAMLLoginFail(const QString &code, const QString &msg);
    void onFetchConfigFinished();

private:
    static const auto MAX_ATTEMPTS{ 5 };

    QString portal;
    QString clientos;
    QString preloginUrl;
    QString configUrl;
    QString username;
    QString password;

    int attempts{ 0 };
    PreloginResponse preloginResponse;

    bool isAutoLogin{ false };

    StandardLoginWindow *standardLoginWindow { nullptr };

    void tryAutoLogin();
    void normalAuth();
    void samlAuth();
    void fetchConfig(QString username, QString password, QString preloginCookie = "", QString userAuthCookie = "");
    void emitFail(const QString& msg = "");
};

#endif // PORTALAUTHENTICATOR_H
