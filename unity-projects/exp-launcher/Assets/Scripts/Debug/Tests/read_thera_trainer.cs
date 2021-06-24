/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/


//using UnityEngine;
//using System.Collections.Generic;
//using System.IO;
//using System;
//using System.Globalization;
//public class read_thera_trainer : MonoBehaviour
//{

//    // Use this for initialization
//    DateTime firstDate;
//    List<Tuple<double,Vector2>> data = new List<Tuple<double, Vector2>>();

//    void Start() {
//        string path = "D:/EPFL/test_projects/Thera_3.txt";
//        StreamReader reader = new StreamReader(path);
//        string firstLine = reader.ReadLine();
//        int nbColumns = firstLine.Split(' ').Length;

//        string dataLine = reader.ReadLine();
//        //nbColumns = dataLine.Split(' ').Length;

//        var format = "HH.mm.ss.ffffff";
//        DateTime date = DateTime.Now;

//        while (true) {
//            dataLine = reader.ReadLine();
//            if(dataLine == null) {
//                break;
//            }

//            var split = dataLine.Split(' ');
//            string dateStr = split[0];
//            var pos = new Vector2(Ex.Converter.to_float(split[1]), Ex.Converter.to_float(split[2]));
//            DateTime.TryParseExact(dateStr, format, CultureInfo.InvariantCulture, DateTimeStyles.None, out date);

//            if(data.Count == 0) {
//                firstDate = date;
//                data.Add(new Tuple<double,Vector2>(0, pos));
//            } else {
//                var currDate = date - firstDate;
//                data.Add(new Tuple<double, Vector2>(currDate.TotalMilliseconds, pos));
//                //Debug.Log("-> " + currDate.TotalMilliseconds + " -> " + pos.x + " " + pos.y);

//            }            
//        }
//        reader.Close();
//    }

//    // Update is called once per frame
//    void Update() {

//    }
//}
