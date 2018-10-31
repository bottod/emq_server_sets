#include "mqttsql.h"
#include <iostream>

MqttSql::MqttSql(QObject *parent) : QObject(parent)
{
    //sql Singleton Pattern
    if(QSqlDatabase::contains("qt_mqtt_connection"))
        db = QSqlDatabase::database("qt_mqtt_connection");
    else
        db = QSqlDatabase::addDatabase("QMYSQL","qt_mqtt_connection");  //uniqe connection name -> "qt_mqtt_connection"
}

void MqttSql::mq_insert(std::string tablename, std::string value)
{
    std::string real_query;
    format_string(tablename);
    real_query = "INSERT INTO `" + tablename + "` VALUES (" + value + ",DEFAULT )";

    if(db.isOpen())
        query = QSqlQuery(db);
    else
    {
        mysql_init_from_file();     //init
        query = QSqlQuery(db);
    }
     query.exec(real_query.c_str());
}

void MqttSql::mysql_init_from_file()
{
    std::ifstream mysql_info_file;
    int64_t count = 0;//string array count
    std::string mysql_info[4];//only 4 line; not start with '#' and not empty line
    mysql_info_file.open("conf/mysql_info.conf");
    if(mysql_info_file.is_open())
    {
        std::string line_info;
        while (getline(mysql_info_file,line_info))
        {
            if(count < 4)
            {
                if(line_info.size() && line_info.at(0) != '#' )
                {
                    mysql_info[count] = line_info;
                    ++count;
                }
            }
            else if(count >= 4 )
            {
                break;
            }
        }
        mysql_info_file.close();
        if(count >= 4)//must be 5
        {
            db.setHostName(mysql_info[0].c_str());
            db.setDatabaseName(mysql_info[1].c_str());
            db.setUserName(mysql_info[2].c_str());
            db.setPassword(mysql_info[3].c_str());

            db.open();
            if(!db.isOpen())
            {
                std::cout<<"Error: Check your conf be correct!!"<<std::endl;
                exit(0);
            }
        }
        else
        {
            std::cout<<"Error: your mysql_info conf not correct!!"<<std::endl;
            exit(0);
        }
    }
    else
    {
        std::cout<<"Error: Can't Open mysql_info conf! Please checkout this conf!!"<<std::endl;
        exit(0);
    }
}

void MqttSql::mysql_create_table()
{
    std::string column_info;            //column info
    column_info = mysql_get_column();


    std::ifstream mysql_table_file;
    mysql_table_file.open("conf/subscribe.conf");
    if(mysql_table_file.is_open())
    {
        std::string line_info;
        while (getline(mysql_table_file,line_info))
        {
            if(line_info.size() && line_info.at(0) != '#' )
            {
                format_string(line_info);
                std::string table_real_query = "";       //all query
                table_real_query += "CREATE TABLE IF NOT EXISTS ";
                table_real_query += line_info;
                table_real_query += " ( ";
                table_real_query += column_info;
                table_real_query += " ) DEFAULT CHARACTER SET=utf8 ENGINE=InnoDB COLLATE=utf8_bin;";

                if(db.isOpen())
                    query = QSqlQuery(db);
                else
                {
                    mysql_init_from_file();     //init
                    query = QSqlQuery(db);
                }
                 query.exec(table_real_query.c_str());
            }
        }
        std::cout<<"Info: Create table OK if your info are correct !!"<<std::endl;
        mysql_table_file.close();
    }
    else
    {
        std::cout<<"Error: Can't Open subscribe conf! Please checkout this conf!!"<<std::endl;
        exit(0);
    }
}

std::string MqttSql::mysql_get_column()
{
    std::string column_info = ""; //null
    std::ifstream mysql_column_file;
    mysql_column_file.open("conf/mysql_column.conf");
    if(mysql_column_file.is_open())
    {
        std::string line_info;
        while (getline(mysql_column_file,line_info))
        {
            if(line_info.size() && line_info.at(0) != '#' )
            {
                column_info +=  "`";
                column_info += line_info;
                column_info += "` TEXT CHARACTER SET utf8 COLLATE utf8_bin,";
            }
        }
        mysql_column_file.close();

    }
    else
    {
        std::cout<<"Error: Can't Open mysql_column conf! Please checkout this conf!!"<<std::endl;
        exit(0);
    }
    column_info += "ctime DATETIME DEFAULT CURRENT_TIMESTAMP";
    return column_info;
}

void MqttSql::format_string(std::string& input)
{
    size_t found = input.rfind('/');
    if(found != std::string::npos)
    {
        input.erase(0,found+1);
    }
}
