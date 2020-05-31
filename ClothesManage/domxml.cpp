#include "domxml.h"
#include<QFile>
#include<QDomDocument>
#include<QDomElement>
#include<QDomProcessingInstruction>
#include<QDebug>
#include<QTextStream>
#include<QDateTime>
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"
DomXml::DomXml()
{

}
void DomXml::createXML(QString filePath)
{
    QFile file(filePath);
    if(file.exists())
    {
        cout<<"文件已存在";
        return;
    }
    else
    {
        bool isOk=file.open(QIODevice::WriteOnly);
        if(isOk)
        {
            QDomDocument doc;
            QDomProcessingInstruction ins;
            ins=doc.createProcessingInstruction("xml","version=\'1.0\' encoding=\'utf-8\'");
            doc.appendChild(ins);
            QDomElement root;
            root=doc.createElement("日销售清单");
            doc.appendChild(root);
            QTextStream stream(&file);
            doc.save(stream,4);
            file.close();
        }
        else
        {
            cout<<"writeonly error";
            return;
        }
    }
}

void DomXml::appendXML(QString filePath, QStringList list)
{
    QFile file(filePath);
    bool isOk=file.open(QIODevice::ReadOnly);
    if(isOk)
    {
        QDomDocument doc;
        isOk=doc.setContent(&file);
        if(isOk)
        {
            file.close();
            QDomElement root=doc.documentElement();
            QDateTime date=QDateTime::currentDateTime();
            QString dataStr=date.toString("yyyy-MM-dd");
            if(root.hasChildNodes())
            {
                QDomElement lastEmt=root.lastChildElement();
                if(lastEmt.attribute("date")==dataStr)
                {
                    writeXML(doc,lastEmt,list);
                }
                else
                {
                    QDomElement dateEmt=doc.createElement("日期");
                    QDomAttr dateAttr=doc.createAttribute("date");
                    dateAttr.setNodeValue(dataStr);
                    dateEmt.setAttributeNode(dateAttr);
                    root.appendChild(dateEmt);
                    writeXML(doc,dateEmt,list);
                }
            }else
            {
                QDomElement dateEmt=doc.createElement("日期");
                QDomAttr dateAttr=doc.createAttribute("date");
                dateAttr.setNodeValue(dataStr);
                dateEmt.setAttributeNode(dateAttr);
                root.appendChild(dateEmt);
                writeXML(doc,dateEmt,list);
            }
            isOk=file.open(QIODevice::WriteOnly);
            if(isOk)
            {
                QTextStream stream(&file);
                doc.save(stream,4);
                file.close();
            }
        }else
        {
            cout<<"setcontent error";
            return;
        }
    }
    else
    {
        cout<<"readonly error";
        return;
    }
}

void DomXml::writeXML(QDomDocument &doc, QDomElement &root, QStringList &list)
{
    QDateTime time=QDateTime::currentDateTime();
    QString timrStr=time.toString("hh-mm-ss");

    QDomElement timeEmt=doc.createElement("时间");
    QDomAttr timeAttr=doc.createAttribute("time");
    timeAttr.setNodeValue(timrStr);
    timeEmt.setAttributeNode(timeAttr);
    root.appendChild(timeEmt);

    QDomElement factory=doc.createElement("厂家");
    QDomElement brand=doc.createElement("品牌");
    QDomElement price=doc.createElement("报价");
    QDomElement num=doc.createElement("数量");
    QDomElement total=doc.createElement("金额");

    QDomText text=doc.createTextNode(list.at(0));
    factory.appendChild(text);

    text=doc.createTextNode(list.at(1));
    brand.appendChild(text);

    text=doc.createTextNode(list.at(2));
    price.appendChild(text);

    text=doc.createTextNode(list.at(3));
    num.appendChild(text);

    text=doc.createTextNode(list.at(4));
    total.appendChild(text);

    timeEmt.appendChild(factory);
    timeEmt.appendChild(brand);
    timeEmt.appendChild(price);
    timeEmt.appendChild(num);
    timeEmt.appendChild(total);
}

void DomXml::readXML(QString filePath, QStringList &fList, QStringList &bList, QStringList &pList, QStringList &nList, QStringList &tList)
{
    QFile file(filePath);
    bool isOk=file.open(QIODevice::ReadOnly);
    if(isOk)
    {
        QDomDocument doc;
        isOk=doc.setContent(&file);
        if(isOk)
        {
            file.close();
            QDomElement root=doc.documentElement();
            QDateTime date=QDateTime::currentDateTime();
            QString dataStr=date.toString("yyyy-MM-dd");
            if(root.hasChildNodes())
            {
                QDomElement lastEmt=root.lastChildElement();
                if(lastEmt.attribute("date")==dataStr)
                {
                    QDomNodeList list=lastEmt.childNodes();
                    for(int i=0;i<list.size();i++)
                    {
                        QDomNodeList subList= list.at(0).toElement().childNodes();
                        QString factory= subList.at(0).toElement().text();
                        fList.append(factory);
                        QString brand= subList.at(1).toElement().text();
                        bList.append(brand);
                        QString price= subList.at(2).toElement().text();
                        pList.append(price);
                        QString num= subList.at(3).toElement().text();
                        nList.append(num);
                        QString total= subList.at(4).toElement().text();
                        tList.append(total);
                    }
                }else
                {
                    cout<<"没有当天日期";
                    return;
                }
            }
            else
            {
                cout<<"没有子节点";
                return;
            }
        }
        else
        {
            cout<<"setcontent error";
            return;
        }
    }
    else
    {
        cout<<"readonly error";
        return;
    }
}
