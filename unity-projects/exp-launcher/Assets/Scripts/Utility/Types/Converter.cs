
/***********************************************************************************
** exvr-exp                                                                       **
** MIT License                                                                    **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                                **
** Permission is hereby granted, free of charge, to any person obtaining a copy   **
** of this software and associated documentation files (the "Software"), to deal  **
** in the Software without restriction, including without limitation the rights   **
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      **
** copies of the Software, and to permit persons to whom the Software is          **
** furnished to do so, subject to the following conditions:                       **
**                                                                                **
** The above copyright notice and this permission notice shall be included in all **
** copies or substantial portions of the Software.                                **
**                                                                                **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    **
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  **
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  **
** SOFTWARE.                                                                      **
************************************************************************************/

// system
using System;
using System.ComponentModel;
using System.Collections.Generic;

// unity
using UnityEngine;

namespace Ex{

    public static class Converter {

        private const string g4  = "G4";
        private const string g7  = "G7";
        private const string g15 = "G15";

        private static readonly string vector2StrF          = "{0}, {1}";
        private static readonly string vector3StrF          = "{0}, {1}, {2}";
        private static readonly string transformValueStrF   = "{0}\n{1}\n{2}";
        private static readonly string colorStrF            = "{0}, {1}, {2}";


        // pitch yaw roll (x y z)
        // yaw roll pitch (y z x)
        public enum AxisOrder {
            PitchYawRoll, YawRollPitch
        };

        private static void log_error(string error) {
            ExVR.Log().error(string.Format("[CONVERTER] {0}", error));
        }

        public static T to<T>(object value) {

            if (typeof(T) == typeof(bool)) {
                return (T)(object)to_bool(value);
            } else if (typeof(T) == typeof(byte)) {
                return (T)(object)to_byte(value);
            } else if (typeof(T) == typeof(char)) {
                return (T)(object)to_char(value);
            } else if (typeof(T) == typeof(int)) {
                return (T)(object)to_int(value);
            } else if (typeof(T) == typeof(long)) {
                return (T)(object)to_long(value);
            } else if (typeof(T) == typeof(float)) {
                return (T)(object)to_float(value);
            } else if (typeof(T) == typeof(double)) {
                return (T)(object)to_double(value);
            } else if (typeof(T) == typeof(string)) {
                return (T)(object)to_string(value);
            } else if (typeof(T) == typeof(DecimalValue)) {
                return (T)(object)to_decimal(value);
            } else if (typeof(T) == typeof(object)) {
                return (T)(object)value;
            } else if (typeof(T) == typeof(Color)) {
                return (T)(object)to_color(value);
            } else if (typeof(T) == typeof(List<float>)) {
                return (T)(object)to_float_list(value);
            } else if (typeof(T) == typeof(List<double>)) {
                return (T)(object)to_double_list(value);
            } else if (typeof(T) == typeof(List<string>)) {
                return (T)(object)to_string_list(value);
            }

            log_error(string.Format("Conversion to \"{0}\" not supported with type {1}.", typeof(T), value.GetType()));
            return default(T);
        }

        #region builtin_types

        #region to_bool
        public static bool to_bool(object value) {

            if (value is bool) {
                return (bool)value;
            } else if (value is byte) {
                return to_bool((byte)value);
            } else if (value is char) {
                return to_bool((char)value);
            } else if (value is int) {
                return to_bool((int)value);
            } else if (value is float) {
                return to_bool((float)value);
            } else if (value is long) {
                return to_bool((long)value);
            } else if (value is double) {
                return to_bool((double)value);
            } else if (value is string) {
                return to_bool((string)value);
            } else if (value is DecimalValue) {
                return ((DecimalValue)value).to_bool();
            }
            log_error(string.Format("Conversion to \"bool\" not supported with type {0}.", value.GetType()));
            return false;
        }
        public static bool to_bool(int value) {
            return Convert.ToBoolean(value);
        }
        public static bool to_bool(byte value) {
            return Convert.ToBoolean(value);
        }
        public static bool to_bool(char value) {
            return to_bool(to_int(value)); // ToBoolean(Char) not supported
        }
        public static bool to_bool(float value) {
            return Convert.ToBoolean(value);
        }
        public static bool to_bool(long value) {
            return Convert.ToBoolean(value);
        }
        public static bool to_bool(double value) {
            return Convert.ToBoolean(value);
        }
        public static bool to_bool(string strValue) {
            if (strValue.Length == 1) {
                if (strValue[0] == '0') {
                    return false;
                }
                return true;
            }
            if (!Boolean.TryParse(strValue, out bool result)) {
                log_error(string.Format("Cannot convert text [{0}] to bool.", strValue));
                return false;
            }
            return result;
        }

        #endregion

        #region to_byte
        public static byte to_byte(object value) {

            if (value is int) {
                return to_byte((int)value);
            } else if (value is bool) {
                return to_byte((bool)value);
            } else if (value is byte) {
                return (byte)value;
            } else if (value is char) {
                return to_byte((char)value);
            } else if (value is float) {
                return to_byte((float)value);
            } else if (value is long) {
                return to_byte((long)value);
            } else if (value is double) {
                return to_byte((double)value);
            } else if (value is string) {
                return to_byte((string)value);
            }

            log_error(string.Format("Conversion to \"byte\" not supported with type {0}.", value.GetType()));
            return (byte)0;
        }

        public static byte to_byte(bool value) {
            return Convert.ToByte(value);
        }
        public static byte to_byte(char value) {
            return Convert.ToByte(value);
        }
        public static byte to_byte(int value) {
            return Convert.ToByte(value);
        }
        public static byte to_byte(long value) {
            return Convert.ToByte(value);
        }
        public static byte to_byte(float value) {
            return Convert.ToByte(value);
        }
        public static byte to_byte(double value) {
            return Convert.ToByte(value);
        }
        public static byte to_byte(string strValue) {
            Byte.TryParse(strValue, out byte result);
            return result;
        }

        #endregion

        #region to_char
        public static char to_char(object value) {

            if (value is int) {
                return to_char((int)value);
            } else if (value is bool) {
                return to_char((bool)value);
            } else if (value is byte) {
                return to_char((byte)value);
            } else if (value is char) {
                return (char)value;
            } else if (value is float) {
                return to_char((float)value);
            } else if (value is long) {
                return to_char((long)value);
            } else if (value is double) {
                return to_char((double)value);
            } else if (value is string) {
                return to_char((string)value);
            }

            log_error(string.Format("Conversion to \"char\" not supported with type {0}.", value.GetType()));
            return (char)0;
        }

        public static char to_char(bool value) {
            return Convert.ToChar(value);
        }
        public static char to_char(byte value) {
            return Convert.ToChar(value);
        }
        public static char to_char(int value) {
            return Convert.ToChar(value);
        }
        public static char to_char(long value) {
            return Convert.ToChar(value);
        }
        public static char to_char(float value) {
            return Convert.ToChar(value);
        }
        public static char to_char(double value) {
            return Convert.ToChar(value);
        }
        public static char to_char(string strValue) {
            Char.TryParse(strValue, out char result);
            return result;
        }

        #endregion

        #region to_short

        public static short to_short(object value) {

            if (value is int) {
                return to_short((int)value);
            } else if (value is short) {
                return (short)value;
            } else if (value is bool) {
                return to_short((bool)value);
            } else if (value is byte) {
                return to_short((byte)value);
            } else if (value is char) {
                return to_short((char)value);
            } else if (value is float) {
                return to_short((float)value);
            } else if (value is long) {
                return to_short((long)value);
            } else if (value is double) {
                return to_short((double)value);
            } else if (value is string) {
                return to_short((string)value);
            }

            log_error("Conversion to \"short\" not supported with current input object value.");
            return (byte)0;
        }

        public static short to_short(bool value) {
            return Convert.ToInt16(value);
        }
        public static short to_short(char value) {
            return Convert.ToInt16(value);
        }
        public static short to_short(long value) {
            return Convert.ToInt16(value);
        }
        public static short to_short(float value) {
            return Convert.ToInt16(value);
        }
        public static short to_short(double value) {
            return Convert.ToInt16(value);
        }
        public static short to_short(string strValue) {
            Int16.TryParse(strValue, out short result);
            return result;
        }

        #endregion

        #region to_int
        public static int to_int(object value) {

            if (value is int) {
                return (int)value;
            } else if (value is bool) {
                return to_int((bool)value);
            } else if (value is byte) {
                return to_int((byte)value);
            } else if (value is char) {
                return to_int((char)value);
            } else if (value is float) {
                return to_int((float)value);
            } else if (value is long) {
                return to_int((long)value);
            } else if (value is double) {
                return to_int((double)value);
            } else if (value is string) {
                return to_int((string)value);
            }

            log_error("Conversion to \"int\" not supported with current input object value.");
            return 0;
        }
        public static int to_int(bool value) {
            return Convert.ToInt32(value);
        }
        public static int to_int(byte value) {
            return Convert.ToInt32(value);
        }
        public static int to_int(char value) {
            return Convert.ToInt32(value);
        }
        public static int to_int(float value) {
            try {
                return Convert.ToInt32(value);
            } catch (OverflowException e) {
                log_error(e.Message);
            }
            return 0;
        }
        public static int to_int(long value) {
            try {
                return Convert.ToInt32(value);
            } catch (OverflowException e) {
                log_error(e.Message);
            }
            return 0;
        }

        public static int to_int(double value) {
            try {
                return Convert.ToInt32(value);
            } catch (OverflowException e) {
                log_error(e.Message);
            }
            return 0;
        }
        public static int to_int(DecimalValue value) {
            return value.to_int();
        }

        public static int to_int(string strValue) {
            Int32.TryParse(strValue, out int result);
            return result;
        }

        #endregion

        #region to_long
        public static long to_long(object value) {

            if (value is int) {
                return to_long((int)value);
            } else if (value is bool) {
                return to_long((bool)value);
            } else if (value is byte) {
                return to_long((byte)value);
            } else if (value is char) {
                return to_long((char)value);
            } else if (value is float) {
                return to_long((float)value);
            } else if (value is long) {
                return (long)value;
            } else if (value is double) {
                return to_long((double)value);
            } else if (value is string) {
                return to_long((string)value);
            }

            log_error(string.Format("Conversion to \"long\" not supported with type {0}.", value.GetType()));
            return 0;
        }

        public static long to_long(bool value) {
            return Convert.ToInt64(value);
        }
        public static long to_long(byte value) {
            return Convert.ToInt64(value);
        }
        public static long to_long(char value) {
            return Convert.ToInt64(value);
        }

        public static long to_long(float value) {
            try {
                return Convert.ToInt64(value);
            } catch (OverflowException e) {
                log_error(e.Message);
            }
            return 0;
        }
        public static long to_long(long value) {
            try {
                return Convert.ToInt64(value);
            } catch (OverflowException e) {
                log_error(e.Message);
            }
            return 0;
        }

        public static long to_long(double value) {
            try {
                return Convert.ToInt64(value);
            } catch (OverflowException e) {
                log_error(e.Message);
            }
            return 0;
        }

        public static long to_long(string strValue) {
            Int64.TryParse(strValue, out long result);
            return result;
        }


        #endregion

        #region to_float
        public static float to_float(object value) {

            if (value is float) {
                return (float)value;
            } else if (value is bool) {
                return to_float((bool)value);
            } else if (value is byte) {
                return to_float((byte)value);
            } else if (value is char) {
                return to_float((char)value);
            } else if (value is int) {
                return to_float((int)value);
            } else if (value is long) {
                return to_float((long)value);
            } else if (value is double) {
                return to_float((double)value);
            } else if (value is string) {
                return to_float((string)value);
            }

            log_error(string.Format("Conversion to \"float\" not supported with type {0}.", value.GetType()));
            return 0f;
        }
        public static float to_float(bool value) {
            return Convert.ToSingle(value);
        }
        public static float to_float(byte value) {
            return Convert.ToSingle(value);
        }
        public static float to_float(char value) {
            return to_float((int)value); // ToSingle(Char) not supported
        }
        public static float to_float(int value) {
            return Convert.ToSingle(value);
        }
        public static float to_float(long value) {
            return Convert.ToSingle(value);
        }
        public static float to_float(double value) {
            return Convert.ToSingle(value);
        }
        public static float to_float(DecimalValue value) {
            return value.to_float();
        }

        public static float to_float(string strValue) {
            if (!Single.TryParse(strValue, out float result)) {
                if (!Single.TryParse(strValue.Replace(",", "."), out result)) {
                    log_error(string.Format("Float parse error: {0} -> {1}", strValue, result));
                }
            }
            return result;
        }


        #endregion

        #region to_double

        public static double to_double(object value) {

            if (value is double) {
                return (double)value;
            } else if (value is bool) {
                return to_double((bool)value);
            } else if (value is int) {
                return to_double((int)value);
            } else if (value is char) {
                return to_double((char)value);
            } else if (value is byte) {
                return to_double((byte)value);
            } else if (value is long) {
                return to_double((long)value);
            } else if (value is float) {
                return to_double((float)value);
            } else if (value is string) {
                return to_double((string)value);
            }

            log_error(string.Format("Conversion to \"double\" not supported with type {0}.", value.GetType()));
            return 0.0;
        }
        public static double to_double(bool value) {
            return Convert.ToDouble(value);
        }
        public static double to_double(byte value) {
            return Convert.ToDouble(value);
        }
        public static double to_double(char value) {
            return to_double((int)value); // ToDouble(Char) not supported
        }
        public static double to_double(int value) {
            return Convert.ToDouble(value);
        }
        public static double to_double(long value) {
            return Convert.ToDouble(value);
        }
        public static double to_double(float value) {
            return Convert.ToDouble(value);
        }
        public static double to_double(DecimalValue value) {
            return value.to_double();
        }
        public static double to_double(string strValue) {
            double.TryParse(strValue, out double result);
            return result;
        }

        #endregion

        #region to_decimal
        public static DecimalValue to_decimal(object value) {

            if (value is int) {
                return new DecimalValue((int)value);
            } else if (value is float) {
                return new DecimalValue((float)value);
            } else if (value is double) {
                return new DecimalValue((double)value);
            } else if (value is long) {
                return new DecimalValue((long)value);
            } else if (value is bool) {
                return new DecimalValue((bool)value);
            } else if (value is DecimalValue) {
                return (DecimalValue)value;
            }

            log_error(string.Format("Conversion to \"DecimalValue\" not supported with type {0}.", value.GetType()));

            return new DecimalValue(0);
        }

        public static DecimalValue to_decimal(short value) {
            return new DecimalValue(value);
        }
        public static DecimalValue to_decimal(int value) {
            return new DecimalValue(value);
        }
        public static DecimalValue to_decimal(float value) {
            return new DecimalValue(value);
        }
        public static DecimalValue to_decimal(double value) {
            return new DecimalValue(value);
        }
        public static DecimalValue to_decimal(string decimalStr) {

            var split = decimalStr.Split(':');
            int id = to_int(split[0]);
            if (id == 0) { // char
                return to_decimal(to_char(split[1]));
            } else if (id == 1) { // integer
                return to_decimal(to_int(split[1]));
            } else if (id == 2) { // float
                return to_decimal(to_float(split[1]));
            }
            // double
            return new DecimalValue(to_double(split[1]));
        }





        public static List<DecimalValue> to_decimal_list(DecimalValue value) {
            var list = new List<DecimalValue>(1);
            list.Add(value);
            return list;
        }

        #endregion

        #region to_string
        public static string to_string(object value) {

            if (value is string) {
                return (string)value;
            } else if (value is bool) {
                return to_string((bool)value);
            } else if (value is char) {
                return to_string((char)value);
            } else if (value is byte) {
                return to_string((byte)value);
            } else if (value is int) {
                return to_string((int)value);
            } else if (value is float) {
                return to_string((float)value);
            } else if (value is long) {
                return to_string((long)value);
            } else if (value is double) {
                return to_string((double)value);
            } else if (value is List<float>) {
                return to_string((List<float>)value);
            } else if (value is List<double>) {
                return to_string((List<double>)value);
            } else if (value is Vector2) {
                return to_string((Vector2)value);
            } else if (value is Vector3) {
                return to_string((Vector3)value);
            } else if (value is Color) {
                return to_string((Color)value);
            } else if (value is TransformValue) {
                return to_string((TransformValue)value);
            } else if (value is DecimalValue) {
                return to_string((DecimalValue)value);
            }

            log_error(string.Format("Conversion to \"string\" not supported with type {0}.", value.GetType()));
            return null;
        }

        public static string to_string(bool value, bool useLetters = true) {
            if (useLetters) {
                return value.ToString().ToLower();
            } else {
                return value ? "1" : "0";
            }
        }

        public static string to_string(char value) {
            return value.ToString();
        }
        public static string to_string(byte value) {
            return value.ToString();
        }
        public static string to_string(int value) {
            return value.ToString();
        }
        public static string to_string(long value) {            
            return value.ToString();
        }
        public static string to_string(float value, string format = g7) {
            return value.ToString(format);
        }
        public static string to_string(double value, string format = g7) {
            return value.ToString(format);
        }
        public static string to_string(List<float> values, string format = g7) {

            List<string> valuesStr = new List<string>(values.Count);
            foreach (var value in values) {
                valuesStr.Add(to_string(value, format));
            }
            return to_string(valuesStr, ",");
        }

        public static string to_string(List<double> values, string format = g7) {

            List<string> valuesStr = new List<string>(values.Count);
            foreach(var value in values) {
                valuesStr.Add(to_string(value, format));
            }
            return to_string(valuesStr, ",");
        }

        public static string to_string(Vector2 value, string format = g7) {
            return string.Format(vector2StrF, to_string(value.x, format), to_string(value.y, format));
        }
        public static string to_string(Vector3 value, string format = g7) {
            return string.Format(vector3StrF, to_string(value.x, format), to_string(value.y, format), to_string(value.z, format));
        }

        public static string to_string(TransformValue value) {
            return string.Format(transformValueStrF, to_string(value.position), to_string(value.rotation.eulerAngles), to_string(value.scale));
        }

        public static string to_string(Color value) {
            return string.Format(colorStrF, to_string(value.r, g4), to_string(value.g, g4), to_string(value.b, g4));
        }

        public static string to_string(DecimalValue value, string format = "G7") {
            if (value.has_int()) {
                return to_string(value.to_int());
            } else if (value.has_float()) {
                return to_string(value.to_float(), format);
            } else if (value.has_double()) {
                return to_string(value.to_double(), format);
            }
            return to_string(value.to_bool());
        }

        public static string to_string(List<string> value, string sep = " ") {
            return String.Join(sep, value.ToArray());
        }

        #endregion

        #region to_float_list
        public static List<float> to_float_list(object value) {

            if (value is float) {
                return to_float_list((float)value);
            } else if (value is int) {
                return to_float_list((int)value);
            } else if (value is double) {
                return to_float_list((double)value);
            } else if (value is string) {
                return to_float_list((string)value);
            } else if (value is DecimalValue) {
                return to_float_list((DecimalValue)value);
            } else if (value is List<double>) {
                return to_float_list((List<double>)value);
            } else if (value is List<float>) {
                return (List<float>)value;
            } else if (value is List<string>) {
                return to_float_list((List<string>)value);
            } else if (value is Vector2) {
                return to_float_list((Vector2)value);
            } else if (value is Vector3) {
                return to_float_list((Vector3)value);
            } else if (value is List<Vector2>) {
                return to_float_list((List<Vector2>)value);
            } else if (value is List<Vector3>) {
                return to_float_list((List<Vector3>)value);
            }
            log_error(string.Format("Conversion to \"List<float>\" not supported with type {0}.", value.GetType()));
            return new List<float>();
        }
        public static List<float> to_float_list(int value) {
            return new List<float>() { to_float(value) };
        }
        public static List<float> to_float_list(float value) {
            return new List<float>() { value };
        }
        public static List<float> to_float_list(double value) {
            return new List<float>() { to_float(value)};
        }
        public static List<float> to_float_list(DecimalValue value) {
            return new List<float>() { value.to_float()};
        }
        public static List<float> to_float_list(Vector2 value) {
            return new List<float>() { value.x,value.y};  
        }
        public static List<float> to_float_list(Vector3 value) {
            return new List<float>() { value.x, value.y, value.z };
        }
        public static List<float> to_float_list(List<Vector2> values) {
            var list = new List<float>(values.Count * 2);
            foreach (var value in values) {
                list.Add(value.x);
                list.Add(value.y);
            }
            return list;
        }
        public static List<float> to_float_list(List<Vector3> values) {
            var list = new List<float>(values.Count*3);
            foreach(var value in values) {
                list.Add(value.x);
                list.Add(value.y);
                list.Add(value.z);
            }
            return list;
        }

        public static List<float> to_float_list(string values, char sep = ',') {

            var split = Ex.Text.split(values, sep);
            List<float> list = new List<float>(split.Length);
            foreach (var strValue in split) {
                list.Add(to_float(strValue));
            }
            return list;
        }

        public static List<float> to_float_list(List<string> values) {
            var list = new List<float>(values.Count);
            foreach (var value in values) {
                list.Add(to_float(value));
            }
            return list;
        }

        public static List<float> to_float_list(List<double> values) {
            var list = new List<float>(values.Count);
            foreach (var value in values) {
                list.Add(to_float(value));
            }
            return list;
        }

        #endregion

        #region to_double_list
        public static List<double> to_double_list(object value) {

            if (value is float) {
                return to_double_list((float)value);
            } else if (value is int) {
                return to_double_list((int)value);
            } else if (value is double) {
                return to_double_list((double)value);
            } else if (value is string) {
                return to_double_list((string)value);
            } else if (value is DecimalValue) {
                return to_double_list((DecimalValue)value);
            } else if (value is List<float>) {
                return to_double_list((List<float>)value);
            } else if (value is List<double>) {
                return (List<double>)value;
            } else if (value is Vector2) {
                return to_double_list((Vector2)value);
            } else if (value is Vector3) {
                return to_double_list((Vector3)value);
            }

            log_error(string.Format("Conversion to \"List<double>\" not supported with type {0}.", value.GetType()));
            return new List<double>();
        }
        public static List<double> to_double_list(int value) {
            return new List<double>() { to_double(value)};
        }
        public static List<double> to_double_list(float value) {
            return new List<double>() { to_double(value) };
        }
        public static List<double> to_double_list(double value) {
            return new List<double>() { value };
        }
        public static List<double> to_double_list(DecimalValue value) {
            return new List<double>() { value.to_double() };
        }
        public static List<double> to_double_list(Vector2 value) {
            return new List<double>() { to_double(value.x), to_double(value.y) };
        }
        public static List<double> to_double_list(Vector3 value) {
            return new List<double>() { to_double(value.x), to_double(value.y), to_double(value.z)};
        }
        public static List<double> to_double_list(List<float> values) {
            var list = new List<double>(values.Count);
            foreach(var value in values) {
                list.Add(to_double(value));
            }
            return list;
        }
        public static List<double> to_double_list(string values, char sep = ',') {

            var split = Ex.Text.split(values, sep);
            List<double> list = new List<double>(split.Length);
            foreach (var strValue in split) {
                list.Add(to_double(strValue));
            }
            return list;
        }

        #endregion

        #region to_string_list
        public static List<string> to_string_list(object value) {

            if(value is List<string>) {
                return (List<string>)value;
            }else if(value is Vector2) {
                to_string_list((Vector2)value);
            } else if (value is Vector3) {
                to_string_list((Vector3)value);
            }

            log_error(string.Format("Conversion to \"List<string>\" not supported with type {0}.", value.GetType()));
            return new List<string>();
        }

        public static List<string> to_string_list(string value) {
            return new List<string>() { value };
        }
        public static List<string> to_string_list(Vector2 value) {
            return new List<string>() { to_string(value.x), to_string(value.y) };
        }
        public static List<string> to_string_list(Vector3 value) {
            return new List<string>() { to_string(value.x), to_string(value.y), to_string(value.z) };
        }

        #endregion

        #region to_list

        public static List<T> to_list<T>(object value) {
            if(value is List<object>) {
                return to_list<T>((List<object>)value);
            }
            return new List<T>() { (T)value};
        }

        public static List<T> to_list<T>(List<object> value) {

            List<T> array = new List<T>(value.Count);
            foreach (object elem in value) {
                array.Add((T)elem);
            }
            return array;
        }

        public static List<object> to_list(Vector2 value) {
            return new List<object>() { value.x, value.y };
        }

        public static List<object> to_list(Vector3 value) {
            return new List<object>() { value.x, value.y, value.z };
        }

        public static List<object> to_list(Color value) {
            return new List<object>() { value.a, value.r, value.g, value.b };
        }

        public static List<object> to_list(TransformValue value) {
            var eulerAngles = value.rotation.eulerAngles;
            return new List<object>() {
                value.position.x,
                value.position.y,
                value.position.z,
                eulerAngles.x,
                eulerAngles.y,
                eulerAngles.z,
                value.scale.x,
                value.scale.y,
                value.scale.z
            };
        }

        public static List<object> to_list(List<Vector2> values) {

            var list = new List<object>(values.Count * 2);
            foreach (var value in values) {
                list.Add(value.x);
                list.Add(value.y);
            }
            return list;
        }

        public static List<object> to_list(List<Vector3> values) {

            var list = new List<object>(values.Count*3);
            foreach(var value in values) {
                list.Add(value.x);
                list.Add(value.y);
                list.Add(value.z);
            }
            return list;
        }

        public static List<object> to_list(Transform value, bool local) {
            return new List<object>(){
                local ? value.localPosition.x    : value.position.x,
                local ? value.localPosition.y    : value.position.y,
                local ? value.localPosition.z    : value.position.z,
                local ? value.localEulerAngles.x : value.eulerAngles.x,
                local ? value.localEulerAngles.y : value.eulerAngles.y,
                local ? value.localEulerAngles.z : value.eulerAngles.z,
                value.localScale.x,
                value.localScale.y,
                value.localScale.z
            };
        }

        public static List<object> to_list(string listStr, string separator, TypeConverter converter) {
            string[] splitArg = listStr.Split(new string[] { separator }, StringSplitOptions.None);
            List<object> argList1D = new List<object>(splitArg.Length);
            foreach (string split in splitArg) {
                argList1D.Add(converter.ConvertFrom(split));
            }
            return argList1D;
        }

        #endregion

        #region to_2d_list

        public static List<List<object>> to_2D_list(string list2dStr, string separator, int rows, int cols, TypeConverter converter) {

            string[] splitArg = list2dStr.Split(new string[] { separator }, StringSplitOptions.None);
            List<List<object>> argList2D = new List<List<object>>(rows);
            if (splitArg.Length != rows * cols) {
                return null;
            }

            int id = 0;
            for (int ii = 0; ii < rows; ++ii) {
                argList2D.Add(new List<object>(cols));
                for (int jj = 0; jj < cols; ++jj) {
                    argList2D[ii].Add(converter.ConvertFrom(splitArg[id++]));
                }
            }

            return argList2D;
        }

        #endregion

        #endregion

        #region unity_types

        #region to_vector2
        public static Vector2 to_vector2(object value) {
            if (value is Vector2) {
                return (Vector2)value;
            } else if (value is Vector3) {
                var v3 = ((Vector3)value);
                return new Vector2(v3.x, v3.y);
            } else if (value is float) {
                var vf = (float)value;
                return new Vector2(vf, vf);
            } else if (value is double) {
                var vf = to_float((double)value);
                return new Vector2(vf, vf);
            } else if (value is int) {
                var vf = to_float((int)value);
                return new Vector2(vf, vf);
            }
            log_error(string.Format("Conversion to \"Vector2\" not supported with type {0}.", value.GetType()));
            return new Vector2();
        }

        public static Vector2 to_vector2(List<object> vector2List) {
            return new Vector2((float)vector2List[0], (float)vector2List[1]);
        }
        public static Vector2 to_vector2(string vector2Str) {
            var split = vector2Str.Split(' ');
            return new Vector2(to_float(split[0]), to_float(split[1]));
        }

        #endregion

        #region to_vector3
        public static Vector3 to_vector3(object value) {

            if (value is Vector3) {
                return (Vector3)value;
            }else if(value is Vector2) {
                var v = (Vector2)value;
                return new Vector3(v.x, v.y, 0);
            } else if(value is float) {
                var vf = (float)value;
                return new Vector3(vf, vf, vf);
            } else if(value is double) {
                var vf = to_float((double)value);
                return new Vector3(vf, vf, vf);
            } else if(value is int) {
                var vf = to_float((int)value);
                return new Vector3(vf, vf, vf);
            }
            log_error(string.Format("Conversion to \"Vector3\" not supported with type {0}.", value.GetType()));
            return new Vector3();
        }
        public static Vector3 to_vector3(List<object> vector3List) {
            return new Vector3((float)vector3List[0], (float)vector3List[1], (float)vector3List[2]);
        }

        public static Vector3 to_vector3(List<object> vector3List, AxisOrder order) {
            if (order == AxisOrder.PitchYawRoll) {
                return new Vector3((float)vector3List[0], (float)vector3List[1], (float)vector3List[2]);
            } else { // OrderRotation.YawRollPitch
                return new Vector3((float)vector3List[1], (float)vector3List[2], (float)vector3List[1]);
            }
        }

        public static Vector3 to_vector3(string vector3Str) {
            var split = vector3Str.Split(' ');
            return new Vector3(to_float(split[0]), to_float(split[1]), to_float(split[2]));
        }

        #endregion

        #region to_color

        public static Color to_color(object value) {

            if (value is Color) {
                return (Color)value;
            } else if (value is string) {
                return to_color((string)value);
            } else if (value is List<object>) {
                return to_color((List<object>)value);
            } 
            log_error(string.Format("Conversion to \"Color\" not supported with type {0}.", value.GetType()));
            return new Color();
        }

        public static Color to_color(string colorStr) {
            var split = colorStr.Split(' ');
            return new Color(to_float(split[1]), to_float(split[2]), to_float(split[3]), to_float(split[0]));
        }

        public static Color to_color(List<object> colorList) {
            return new Color((float)colorList[1], (float)colorList[2], (float)colorList[3], (float)colorList[0]);
        }

        #endregion

        #region to_animation_curve
        public static AnimationCurve to_curve(string curveStr) {
            return to_curve(to_float_list(curveStr, ' '));
        }

        public static AnimationCurve to_curve(List<float> values) {

            AnimationCurve curve = new AnimationCurve();
            if (values.Count % 2 == 0) {
                for (int ii = 0; ii < values.Count / 2; ++ii) {
                    curve.AddKey(values[ii * 2], values[ii * 2 + 1]);
                }
            } else {
                log_error("Invalid values for curve.");
            }

            return curve;
        }

        #endregion

        #endregion

        #region ex_types

        public static IdAny to_id_any(object value) {
            if (value is IdAny) {
                return (IdAny)value;
            }
            return new IdAny();
        }

        public static StringAny to_string_any(object value) {
            if (value is StringAny) {
                return (StringAny)value;
            }
            return new StringAny();
        }

        #region to_transform_value


        public static TransformValue to_transform_value(object value, AxisOrder order = AxisOrder.PitchYawRoll) {

            if (value is TransformValue trValue) {
                return trValue;
            } else if (value is Transform) {
                return to_transform_value((Transform)value);
            } else if (value is List<float>) {
                return to_transform_value((List<float>)value, order);
            } else if (value is List<double>) {
                return to_transform_value((List<double>)value, order);
            } else if (value is List<Vector3>) {
                return to_transform_value((List<Vector3>)value, order);
            } else if (value is List<string>) {
                return to_transform_value((List<string>)value, order);
            } else if (value is string) {
                return to_transform_value((string)value, order);
            } else if (value is List<object>) {

                var list = (List<object>)value;
                if (list.Count > 0) {
                    if (list[0] is float) {
                        return to_transform_value(to_list<float>(value));
                    } else if (list[0] is double) {
                        return to_transform_value(to_list<double>(value));
                    }
                }         
            }
            
            if (ExVR.GuiSettings().catchConverterExceptions) {
                throw new ArgumentException(string.Format("Conversion to \"TransformValue\" not supported with type {0}.", value.GetType()));
            } else {
                log_error(string.Format("Conversion to \"TransformValue\" not supported with type {0}.", value.GetType()));
            }

            return new TransformValue();
        }

        public static TransformValue to_transform_value(string values, AxisOrder order = AxisOrder.PitchYawRoll) {
            return to_transform_value(to_float_list(values, ' '));
        }
        public static TransformValue to_transform_value(List<string> values, AxisOrder order = AxisOrder.PitchYawRoll) {
            return to_transform_value(to_float_list(values), order);
        }

        public static TransformValue to_transform_value(List<double> values, AxisOrder order = AxisOrder.PitchYawRoll) {
            return to_transform_value(to_float_list(values), order);
        }

        public static TransformValue to_transform_value(List<Vector3> values, AxisOrder order = AxisOrder.PitchYawRoll) {
            return to_transform_value(to_float_list(values), order);
        }

        public static TransformValue to_transform_value(List<float> values, AxisOrder order = AxisOrder.PitchYawRoll) {
            TransformValue trV = new TransformValue();
            if (values.Count == 9) {

                trV.position.x = values[0];
                trV.position.y = values[1];
                trV.position.z = values[2];

                if (order == AxisOrder.PitchYawRoll) {
                    trV.rotation = Quaternion.Euler(values[3], values[4], values[5]);
                } else {
                    trV.rotation = Quaternion.Euler(values[4], values[5], values[3]);
                }

                trV.scale.x = values[6];
                trV.scale.y = values[7];
                trV.scale.z = values[8];
            } else {
                log_error("Invalid number of values for TransformValue.");
            }
            return trV;
        }

        public static TransformValue to_transform_value(Transform transform) {
            TransformValue trV = new TransformValue();
            trV.position = transform.position;
            trV.rotation = transform.rotation;
            trV.scale    = transform.localScale;
            return trV;
        }

        #endregion

        #endregion
    }
}
