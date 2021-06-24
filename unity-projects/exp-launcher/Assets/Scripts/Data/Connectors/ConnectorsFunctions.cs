/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;
using System.Collections.Generic;

// unity
using UnityEngine;


namespace Ex{
    public class ConnectorsFunctions : MonoBehaviour {

        public enum TrigonometryFunction    : int { cos, sin, tan, acos, asin, atan, cosh, sinh, tanh};
        public enum DecimalOperator         : int { add, sub, multiply, divide, modulo, less, less_equal, superior, superior_equal, equal, different };
        public enum BinaryOperator          : int { and, or, xor, not};

        public enum StringOperator : int { add, remove, contains, do_not_contains, equals, not_equals, starts_with, ends_with, splits_with};

        public bool is_trigonometry_function(string name) {
            return strToTrigonometryFunction.ContainsKey(name);
        }
        public bool is_decimal_operator(string name) {
            return strToDecimalOperator.ContainsKey(name);
        }
        public bool is_string_operator(string name) {
            return strToStringOperators.ContainsKey(name);
        }

        public TrigonometryFunction get_trigonometry_function(string name) {

            if (is_trigonometry_function(name)) {
                return strToTrigonometryFunction[name];
            }
            ExVR.Log().error("Cannot convert " + name + " to trigonometry function.");
            return TrigonometryFunction.cos;

        }
        public DecimalOperator get_decimal_operator(string name) {

            if (is_decimal_operator(name)) {
                return strToDecimalOperator[name];
            }
            ExVR.Log().error("Cannot convert " + name + " to decimal operator.");
            return DecimalOperator.add;
        }

        public BinaryOperator get_binary_function(string name) {

            if (strToBinaryOperator.ContainsKey(name)){
                return strToBinaryOperator[name];
            }
            ExVR.Log().error("Cannot convert " + name + " to binary function.");
            return BinaryOperator.and;
        }
        public StringOperator get_string_operator(string name) {
            if (strToStringOperators.ContainsKey(name)) {
                return strToStringOperators[name];
            }
            ExVR.Log().error("Cannot convert " + name + " to string operator.");
            return StringOperator.add;
        }

        public Func<double, double> get(TrigonometryFunction t) {
            return trigonometryFunctions[t];
        }
        public Func<double, double, object> get(DecimalOperator o) {
            return decimalOperators[o];
        }

        public Func<bool, bool, bool> get(BinaryOperator b) {
            return binaryOperators[b];
        }
        public Func<string, string, object> get(StringOperator o) {
            return stringOperators[o];
        }
        

        public Action<object> get_logger(Type type) {
            if (logger.ContainsKey(type)){
                return logger[type];
            }
            return input => { ExVR.Log().message(input); };
        }

        private Dictionary<string, TrigonometryFunction> strToTrigonometryFunction = null;
        private Dictionary<string, DecimalOperator> strToDecimalOperator = null;
        private Dictionary<string, BinaryOperator> strToBinaryOperator = null;
        private Dictionary<string, StringOperator> strToStringOperators = null;        

        private Dictionary<TrigonometryFunction, Func<double, double>> trigonometryFunctions = null;
        private Dictionary<DecimalOperator, Func<double, double, object>> decimalOperators = null;
        private Dictionary<BinaryOperator, Func<bool, bool, bool>> binaryOperators = null;
        private Dictionary<StringOperator, Func<object, object, object>> stringOperators = null;

        private Dictionary<Type, Action<object>> logger = null;

        public void initialize() {

            // trigonometry functions
            strToTrigonometryFunction = new Dictionary<string, TrigonometryFunction>();
            strToTrigonometryFunction["Cos"]  = TrigonometryFunction.cos;
            strToTrigonometryFunction["Sin"]  = TrigonometryFunction.sin;
            strToTrigonometryFunction["Tan"]  = TrigonometryFunction.tan;
            strToTrigonometryFunction["Acos"] = TrigonometryFunction.acos;
            strToTrigonometryFunction["Asin"] = TrigonometryFunction.asin;
            strToTrigonometryFunction["Atan"] = TrigonometryFunction.atan;
            strToTrigonometryFunction["Cosh"] = TrigonometryFunction.cosh;
            strToTrigonometryFunction["Sinh"] = TrigonometryFunction.sinh;
            strToTrigonometryFunction["Tanh"] = TrigonometryFunction.tanh;

            trigonometryFunctions = new Dictionary<TrigonometryFunction, Func<double, double>>();
            trigonometryFunctions[TrigonometryFunction.cos]  = input => { return Math.Cos(input);  };
            trigonometryFunctions[TrigonometryFunction.sin]  = input => { return Math.Sin(input);  };
            trigonometryFunctions[TrigonometryFunction.tan]  = input => { return Math.Tan(input);  };
            trigonometryFunctions[TrigonometryFunction.acos] = input => { return Math.Acos(input); };
            trigonometryFunctions[TrigonometryFunction.asin] = input => { return Math.Asin(input); };
            trigonometryFunctions[TrigonometryFunction.atan] = input => { return Math.Atan(input); };
            trigonometryFunctions[TrigonometryFunction.cosh] = input => { return Math.Cosh(input); };
            trigonometryFunctions[TrigonometryFunction.sinh] = input => { return Math.Sinh(input); };
            trigonometryFunctions[TrigonometryFunction.tanh] = input => { return Math.Tanh(input); };

            // decimal operators
            strToDecimalOperator = new Dictionary<string, DecimalOperator>();
            strToDecimalOperator["Add"]                   = DecimalOperator.add;
            strToDecimalOperator["Substract"]             = DecimalOperator.sub;
            strToDecimalOperator["Multiply"]              = DecimalOperator.multiply;
            strToDecimalOperator["Divide"]                = DecimalOperator.divide;
            strToDecimalOperator["Modulo"]                = DecimalOperator.modulo;
            strToDecimalOperator["Inferior"]              = DecimalOperator.less;
            strToDecimalOperator["Inferior or equal?"]    = DecimalOperator.less_equal;
            strToDecimalOperator["Superior?"]             = DecimalOperator.superior;
            strToDecimalOperator["Superior or equal?"]    = DecimalOperator.superior_equal;
            strToDecimalOperator["Equal?"]                = DecimalOperator.equal;
            strToDecimalOperator["Not equal?"]            = DecimalOperator.different;

            decimalOperators = new Dictionary<DecimalOperator, Func<double, double, object>>();
            decimalOperators[DecimalOperator.add]            = (input1, input2) => { return input1 + input2; };
            decimalOperators[DecimalOperator.sub]            = (input1, input2) => { return input1 - input2; };
            decimalOperators[DecimalOperator.multiply]       = (input1, input2) => { return input1 * input2; };
            decimalOperators[DecimalOperator.divide]         = (input1, input2) => { if (Math.Abs(input2) < 0.001) { return 0.0; } else { return input1 / input2; } };
            decimalOperators[DecimalOperator.modulo]         = (input1, input2) => { if (Math.Abs(input2) < 0.001) { return 0.0; } else { return input1 % input2; } };
            decimalOperators[DecimalOperator.less]           = (input1, input2) => { return input1 < input2; };
            decimalOperators[DecimalOperator.less_equal]     = (input1, input2) => { return (input1 < input2) || Maths.is_almost_equal(input1, input2); };
            decimalOperators[DecimalOperator.superior]       = (input1, input2) => { return input1 > input2; };
            decimalOperators[DecimalOperator.superior_equal] = (input1, input2) => { return (input1 > input2) || Maths.is_almost_equal(input1, input2); };
            decimalOperators[DecimalOperator.equal]          = (input1, input2) => { return Maths.is_almost_equal(input1, input2); };
            decimalOperators[DecimalOperator.different]      = (input1, input2) => { return !Maths.is_almost_equal(input1, input2); };

            // binary operators
            strToBinaryOperator = new Dictionary<string, BinaryOperator>();
            strToBinaryOperator["AND"] = BinaryOperator.and;
            strToBinaryOperator["OR"]  = BinaryOperator.or;
            strToBinaryOperator["XOR"] = BinaryOperator.xor;
            strToBinaryOperator["NOT"] = BinaryOperator.not;

            binaryOperators = new Dictionary<BinaryOperator, Func<bool, bool, bool>>();
            binaryOperators[BinaryOperator.and] = (input1, input2) => { return input1 && input2; };
            binaryOperators[BinaryOperator.or]  = (input1, input2) => { return input1 || input2; };
            binaryOperators[BinaryOperator.xor] = (input1, input2) => { return input1 != input2; };
            binaryOperators[BinaryOperator.not] = (input1, input2) => { return !input1; };

            // string operators
            strToStringOperators = new Dictionary<string, StringOperator>();
            strToStringOperators["Add"]             = StringOperator.add;
            strToStringOperators["Remove"]          = StringOperator.remove;
            strToStringOperators["Contains"]        = StringOperator.contains;
            strToStringOperators["Do not contains"] = StringOperator.do_not_contains;
            strToStringOperators["Equals"]          = StringOperator.equals;
            strToStringOperators["Do not equals"]   = StringOperator.not_equals;
            strToStringOperators["Starts with"]     = StringOperator.starts_with;
            strToStringOperators["Ends with"]       = StringOperator.ends_with;
            strToStringOperators["Splits with"]     = StringOperator.splits_with;

            stringOperators = new Dictionary<StringOperator, Func<object, object, object>>();
            stringOperators[StringOperator.add]             = (input1, input2) => { return (string)input1 + (string)input2; };
            stringOperators[StringOperator.remove]          = (input1, input2) => { return ((string)input1).Replace((string)input2, ""); };
            stringOperators[StringOperator.contains]        = (input1, input2) => { return ((string)input1).Contains((string)input2); };
            stringOperators[StringOperator.do_not_contains] = (input1, input2) => { return !((string)input1).Contains((string)input2); };
            stringOperators[StringOperator.equals]          = (input1, input2) => { return (string)input1 == (string)input2; };
            stringOperators[StringOperator.not_equals]      = (input1, input2) => { return (string)input1 != (string)input2; };
            stringOperators[StringOperator.starts_with]     = (input1, input2) => { return ((string)input1).StartsWith((string)input2); };
            stringOperators[StringOperator.ends_with]       = (input1, input2) => { return ((string)input1).EndsWith((string)input2); };
            stringOperators[StringOperator.splits_with]     = (input1, input2) => { return new List<string>(((string)input1).Split(new string[] { (string)input2 }, StringSplitOptions.None)); };
            // logger
            logger = new Dictionary<Type, Action<object>>();
            logger[typeof(int)] = input => { ExVR.Log().message(input); };
            // ...
        }
    }
}
