

# /*******************************************************************************
# ** exvr                                                                       **
# ** MIT License                                                                **
# ** Copyright (c) [2018] [Florian Lance]                                       **
# **                                                                            **
# ** Permission is hereby granted, free of charge, to any person obtaining a    **
# ** copy of this software and associated documentation files (the "Software"), **
# ** to deal in the Software without restriction, including without limitation  **
# ** the rights to use, copy, modify, merge, publish, distribute, sublicense,   **
# ** and/or sell copies of the Software, and to permit persons to whom the      **
# ** Software is furnished to do so, subject to the following conditions:       **
# **                                                                            **
# ** The above copyright notice and this permission notice shall be included in **
# ** all copies or substantial portions of the Software.                        **
# **                                                                            **
# ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR **
# ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   **
# ** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    **
# ** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER **
# ** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    **
# ** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        **
# ** DEALINGS IN THE SOFTWARE.                                                  **
# **                                                                            **
# ********************************************************************************/

PROJECT_NAME = all-exvr

TEMPLATE = subdirs

SUBDIRS =\
    base base-app base-test base-export base-export-app\
    opengl-utility opengl-utility-app \
    3d-engine \
    qt-utility qt-utility-app \
    nodes demos \
    scaner-component scaner-grabber guardian scaner-manager \
    dc-grabber dc-manager dc-monitoring \
    exvr-export exvr-export-app \
    exvr-designer \
    exvr-test \

# where to find the sub projects
## toolset
### base
base.subdir                     = toolset/cpp-projects/base
base-app.subdir                 = toolset/cpp-projects/base-app
base-test.subdir                = toolset/cpp-projects/base-test
base-export.subdir              = toolset/cpp-projects/base-export
base-export-app.subdir          = toolset/cpp-projects/base-export-app
### opengl-utility
opengl-utility.subdir           = toolset/cpp-projects/opengl-utility
opengl-utility-app.subdir       = toolset/cpp-projects/opengl-utility-app
### 3d-engine
3d-engine.subdir                = toolset/cpp-projects/3d-engine
### qt-utility
qt-utility.subdir               = toolset/cpp-projects/qt-utility
qt-utility-app.subdir           = toolset/cpp-projects/qt-utility-app
### nodes
nodes.subdir                    = toolset/cpp-projects/nodes
### demos
demos.subdir                    = toolset/cpp-projects/demos
scaner-component.subdir         = toolset/cpp-projects/scaner-component
scaner-grabber.subdir           = toolset/cpp-projects/scaner-grabber
scaner-manager.subdir           = toolset/cpp-projects/scaner-manager
guardian.subdir                 = toolset/cpp-projects/guardian
dc-grabber.subdir               = toolset/cpp-projects/dc-grabber
dc-manager.subdir               = toolset/cpp-projects/dc-manager
dc-monitoring.subdir            = toolset/cpp-projects/dc-monitoring
## exvr
### exvr-export
exvr-export.subdir              = cpp-projects/exvr-export
exvr-export-app.subdir          = cpp-projects/exvr-export-app
### exvr-designer
exvr-designer.subdir            = cpp-projects/exvr-designer
exvr-test.subdir                = cpp-projects/exvr-test

# dependencies
## toolset
### base
base-app.depends                = base
base-test.depends               = base
base-export.depends             = base
base-export-app.depends         = base-export
### opengl-utility
opengl-utility.depends          = base
opengl-utility-app.depends      = opengl-utility
### 3d-engine
3d-engine.depends               = opengl-utility
### qt-utility
qt-utility.depends              = opengl-utility
qt-utility-app.depends          = qt-utility
### nodes
nodes.depends                   = base
scaner-component.depends        = base
demos.depends                   = 3d-engine
scaner-grabber.depends          = qt-utility
guardian.depends                = qt-utility
scaner-manager.depends          = qt-utility
dc-grabber.depends              = 3d-engine
dc-manager.depends              = 3d-engine
dc-monitoring.depends           = qt-utility
## exvr
### exvr-export
exvr-export.depends             = scaner-component
exvr-export-app.depends         = exvr-export
### exvr-designer
exvr-designer.depends           = qt-utility nodes
exvr-test.depends               = exvr-designer
