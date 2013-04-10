package com.android.wifi.navigator.log;

import android.util.Log;
import com.android.wifi.navigator.algorithms.AlgorithmData;
import com.android.wifi.navigator.algorithms.Vector2D;
import com.android.wifi.navigator.algorithms.WifiData;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 10.04.13
 * Time: 19:56
 * To change this template use File | Settings | File Templates.
 */
public class TimeStepData {

    public AlgorithmData algorithmData;
    public Vector2D firstAlgorithm;
    public Vector2D secondAlgorithm;
    public Vector2D thirdAlgorithm;
    public Date date;

    public TimeStepData(AlgorithmData data, Vector2D a1, Vector2D a2, Vector2D a3){
        this.algorithmData = data;
        this.firstAlgorithm = a1;
        this.secondAlgorithm = a2;
        this.thirdAlgorithm = a3;
        date = Calendar.getInstance().getTime();
    }

    public String toString(){
        Log.i("INF", "2.1");
        StringBuilder sb = new StringBuilder();
        DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
        sb.append(dateFormat.format(date));
        sb.append("|");
        Log.i("INF", "2.2");
        for (WifiData wd : algorithmData.spotsData){
            sb.append(wd.toString());

        }
        sb.append(firstAlgorithm.toString());
        sb.append(secondAlgorithm.toString());
        sb.append(thirdAlgorithm.toString());
        Log.i("INF", "2.3");
        return sb.toString();
    }
}
