/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

namespace Ex {

    public class IdAny {

        public IdAny() { }

        public IdAny(int id, object value) {
            this.id = id;
            this.value = value;
        }

        public int id = 0;
        public object value = null;
    }

    public class StringAny {

        public StringAny() { }

        public StringAny(string str, object value) {
            this.str = str;
            this.value = value;
        }

        public string str = "default";
        public object value = null;
    }
}