#ifndef JSONMODEL_H
#define JSONMODEL_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QVariant>

class JSonNode;
class JSonModel;

class JSonNode: public QObject
{
    Q_OBJECT

public:
    enum SetError{
        SameValue = -1,
        NoError = 0,
        DoesNotExist,
        ReadOnly,
        WrongArg
    };

public:
    QVariant get(const QString& name);
    bool getToString(const QString& name, QString &result) const;
    SetError set(const QString& name, const QString& value);
    bool call(const QString& functionName, const QStringList& arg, QString &result);

public:
    const QString&      name()          const {return _name;}
    JSonNode*           nodeAt(QString name);
    JSonNode*           parentNode()    const {return _parentNode;}

    QString             address() const;

    virtual ~JSonNode();

    virtual bool createSubNode(QString name, QJsonValueRef data);
    bool populateNode(QJsonValueRef &data);
    bool populateNode(QJsonObject data);

signals:
    void out(QString data);

protected:
    JSonNode(QString name, JSonNode *parent);

    virtual void updateParentJSon();
    void addSubNode(JSonNode* node);
    void clearJsonData();

    virtual SetError setValue(QString name, QString value);
    JSonNode::SetError setString(QString name, QString value);
    SetError setNumber(QString name, QString value);
    SetError setBool(QString name, QString value);

    virtual bool execFunction(QString function, QStringList args, QString& result) {return false;}
    virtual QString print() const;

    QString _name;
    QJsonObject _jsonData;
    JSonNode* _parentNode;

private:
    QList<JSonNode*> _subnodes;

    void valueChanged(QString name);
};


#define JSON QDir::current().filePath(_name+".json")
class JSonModel : public JSonNode
{
    Q_OBJECT

public:
    JSonNode *nodeByAddress(QString address);

    virtual ~JSonModel(){}

signals:
    void out(QString data);

public slots:
    bool loadFile(QString path);
    bool saveToFile(QString path);
    bool resetFile();
    bool initFile();


protected:
    explicit JSonModel(QString name);
    void initModel();
    void updateParentJSon();

protected slots:
    bool parseJSonFile();
    bool writeJSonFile();

private:
    void cleanJSon();

    QJsonDocument _jsonDoc;
    QFileSystemWatcher _watch;
    QTimer timer;

};

#endif // JSONMODEL_H