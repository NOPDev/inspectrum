/*
 *  Copyright (C) 2015, Mike Walters <mike@flomp.net>
 *
 *  This file is part of inspectrum.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QCommandLineParser>
#include <PythonQt.h>
#include <gui/PythonQtScriptingConsole.h>
#include <PythonQtConversion.h>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("inspectrum");
    MainWindow mainWin;

    QCommandLineParser parser;
    parser.setApplicationDescription("spectrum viewer");
    parser.addHelpOption();
    parser.addPositionalArgument("file", QCoreApplication::translate("main", "File to view."));

    // Add options
    QCommandLineOption rateOption(QStringList() << "r" << "rate",
                                  QCoreApplication::translate("main", "Set sample rate."),
                                  QCoreApplication::translate("main", "Hz"));
    parser.addOption(rateOption);

    // Process the actual command line
    parser.process(a);

    const QStringList args = parser.positionalArguments();
    if (args.size()>=1)
        mainWin.openFile(args.at(0));

    if (parser.isSet(rateOption)) {
        bool ok;
        // Use toDouble just for scientific notation support
        int rate = parser.value(rateOption).toDouble(&ok);
        if(!ok) {
            fputs("ERROR: could not parse rate\n", stderr);
            return 1;
        }
        mainWin.setSampleRate(rate);
    }
    PythonQt::init(PythonQt::RedirectStdOut);
    PythonQtObjectPtr ctx = PythonQt::self()->getMainModule();
    PythonQtScriptingConsole console(NULL, ctx);

    PythonQtRegisterListTemplateConverterForKnownClass(std::vector, PlotPtr);

    PythonQt::self()->addDecorators(new InputSourceWrapper());
    PythonQt::self()->addDecorators(new TracePlotWrapper());

    PythonQt::priv()->registerCPPClass("InputSource", "", "inspectrum", PythonQtCreateObject<InputSourceWrapper>);
    PythonQt::priv()->registerCPPClass("TracePlot", "", "inspectrum", PythonQtCreateObject<TracePlotWrapper>);
    PythonQt::priv()->registerCPPClass("PlotPtr", "", "inspectrum", PythonQtCreateObject<PlotWrapper>);

    PythonQt::self()->registerClass(&MainWindow::staticMetaObject, "inspectrum");

    qRegisterMetaType<std::shared_ptr<AbstractSampleSource> >("std::shared_ptr<AbstractSampleSource>");

    ctx.addObject("app", &a);
    ctx.addObject("main", &mainWin);
    ctx.evalFile("/usr/share/inspectrum/python/init.py");
    mainWin.show();

    return a.exec();
}
