/*
 *  Copyright (C) 2015, Mike Walters <mike@flomp.net>
 *  Copyright (C) 2015, Jared Boone <jared@sharebrained.com>
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

#include <PythonQt.h>
#include <complex>
#include <QtCore/QObject>
#include "samplesource.h"
#include "plot.h"

class SampleAdapter {
public:
    virtual size_t sampleSize() = 0;
    virtual void copyRange(const void* const src, off_t start, off_t length, std::complex<float>* const dest) = 0;
};

class InputSource : public SampleSource<std::complex<float>>
{
private:
    FILE *inputFile = nullptr;
    off_t fileSize = 0;
    off_t sampleCount = 0;
    off_t sampleRate = 0;
    void *mmapData = nullptr;
    std::unique_ptr<SampleAdapter> sampleAdapter;

public:
    InputSource();
    ~InputSource();
    void cleanup();
    void openFile(const char *filename);
    std::unique_ptr<std::complex<float>[]> getSamples(off_t start, off_t length);
    off_t count() {
        return sampleCount;
    };
    void setSampleRate(off_t rate);
    off_t rate();
};


class InputSourceWrapper : public QObject {
    Q_OBJECT
public Q_SLOTS:
    InputSource* new_InputSource() { return new InputSource(); };
    void delete_InputSource(InputSource *obj) { delete obj; };
    void openFile(InputSource *o, const char *filename) { o->openFile(filename); };
    void setSampleRate(InputSource *o, size_t rate) { o->setSampleRate(rate); };
    size_t rate(InputSource *o) { o->rate(); };

//    std::vector<float> static_Plot_getSamples(Plot* obj, int index) { return std::vector<float>() = {1,2,3} ;}

};