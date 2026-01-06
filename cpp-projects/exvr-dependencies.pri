
# /*******************************************************************************
# ** exvr                                                                    **
# ** MIT License                                                                **
# ** Copyright (c) [2024] [Florian Lance]                                       **
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

# include(../toolset/cpp-projects/ts-dependencies.pri)
include($$TOOLSET_REPOSITORY_DIR"/cpp-projects/ts-dependencies.pri")

########################################################### EXVR-BASE

EXVR_BASE_THIRDPARTY_INCLUDES =\

EXVR_BASE_THIRDPARTY_LIBS =\

########################################################### EXVR-EXPORT

EXVR_EXPORT_THIRDPARTY_INCLUDES =\
    $$PYTHON_INCLUDES \

EXVR_EXPORT_THIRDPARTY_LIBS =\
    $$PYTHON_LIBS \

########################################################### EXVR-DESIGNER

EXVR_DESIGNER_THIRDPARTY_INCLUDES =\
    $$PYTHON_INCLUDES \

EXVR_DESIGNER_THIRDPARTY_LIBS =\
    $$PYTHON_LIBS \

########################################################### EXVR-TEST

EXVR_TEST_THIRDPARTY_INCLUDES =\

EXVR_TEST_THIRDPARTY_LIBS =\
