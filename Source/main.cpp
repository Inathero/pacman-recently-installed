#include <QCoreApplication>

#include <QFile>
#include <QDebug>
#include <QStringList>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList ListOfInstalls;

    // Load pacman log
    QFile LogFile("/var/log/pacman.log");

    //
    if(!LogFile.open(QIODevice::ReadOnly))
    {
        ListOfInstalls.append("Error opening file");
        qDebug() << "error opening log file";

        // kill app if fail to open log
        return 0;
    }

    // load file into a text stream
    QTextStream in(&LogFile);
    // while we're not at end..
    while (!LogFile.atEnd())
    {
      // get each line, cut off the '\n' at the end of it
      QString line = LogFile.readLine();
      line.chop(1);
      // if installed is present, add to list
      if(line.contains("installed"))
          ListOfInstalls.append(line);
    }
    // close used file
        LogFile.close();
    //Makes the most recent items being presented first
    //but in retrospec, probably better to not flip it.
    /**
    for(int k = 0; k < (ListOfInstalls.size() / 2); k++)
        ListOfInstalls.swap( k, ListOfInstalls.size() - (1 + k) );
    */

    // print out all files
    foreach (QString InstalledItem, ListOfInstalls)
        qDebug () << InstalledItem;

    return 0;
}
