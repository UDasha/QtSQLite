#include <QCoreApplication>
#include<iostream>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QVariant>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/db/test.db");

    if(!db.open())
    {
        cout<<"Error! Couldn't open db"<<endl;
        return 1;
    }

    QSqlQuery simpleSelectQuery(db);
    simpleSelectQuery.exec("SELECT * FROM test");

    while(simpleSelectQuery.next())
    {
        cout<<qPrintable(simpleSelectQuery.value(0).toString())<<" "<<qPrintable(simpleSelectQuery.value(1).toString())<<endl;
    }

    QSqlQuery InsertQuery(db);
    InsertQuery.prepare("INSERT INTO test(id, value) VALUES(:id, :value)");
    InsertQuery.bindValue(":id", 5);
    InsertQuery.bindValue(":value", 8);
    InsertQuery.exec();

    simpleSelectQuery.clear();
    cout<<endl;

    simpleSelectQuery.exec("SELECT * FROM test");

    while(simpleSelectQuery.next())
    {
        cout<<qPrintable(simpleSelectQuery.value(0).toString())<<" "<<qPrintable(simpleSelectQuery.value(1).toString())<<endl;
    }

    QSqlQuery DeleteQuery(db);
    DeleteQuery.exec("DELETE FROM test WHERE id=3");

    simpleSelectQuery.clear();
    cout<<endl;

    simpleSelectQuery.exec("SELECT * FROM test");

    while(simpleSelectQuery.next())
    {
        cout<<qPrintable(simpleSelectQuery.value(0).toString())<<" "<<qPrintable(simpleSelectQuery.value(1).toString())<<endl;
    }

    QSqlQuery UpdateQuery(db);
    UpdateQuery.exec("UPDATE test SET value=-2 WHERE value=8");

    simpleSelectQuery.clear();
    cout<<endl;

    simpleSelectQuery.exec("SELECT * FROM test");

    while(simpleSelectQuery.next())
    {
        cout<<qPrintable(simpleSelectQuery.value(0).toString())<<" "<<qPrintable(simpleSelectQuery.value(1).toString())<<endl;
    }

    db.close();

    return a.exec();
}
