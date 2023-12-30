#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDebug>


class Utils
{
public:
    Utils();
    static char** convertQStringToCharStarStar(const QString& str){
        // Split the QString into a list of strings using a separator
        QStringList stringList = str.split(" ");

        // Allocate memory for an array of char*
        char** charArray = new char*[stringList.size() + 1]; // +1 for the nullptr at the end

        // Copy each string from the QStringList to the char array
        QByteArray byteArray = stringList[0].toUtf8();
        charArray[0] = new char[byteArray.size() + 1];
        qstrcpy(charArray[0], byteArray.constData());

        return charArray;
    };
};

#endif // UTILS_H
