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

#pragma once

#include <QMainWindow>
#include <QScrollArea>
#include "spectrogramcontrols.h"
#include "plotview.h"
#include "plots.h"
#include "plot.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    PlotView *plots;
    virtual QSize sizeHint() const override;

public slots:
    void openFile(QString fileName);
    void setSampleRate(QString rate);
    void setSampleRate(int rate);
    std::vector<PlotPtr> getPlots() const { return plots->getPlots(); };
    std::vector<float> symbols(PlotPtr *plot) { return plots->getSymbols((*plot)->output()); };
    void addDock(QDockWidget *dockWidget) { this->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, dockWidget); }

private:
    SpectrogramControls *dock;
    InputSource *input;

};
