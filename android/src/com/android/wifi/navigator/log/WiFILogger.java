package com.android.wifi.navigator.log;

import android.os.Environment;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 10.04.13
 * Time: 19:47
 * To change this template use File | Settings | File Templates.
 */
public class WiFILogger {

    private String fileName;
    private ArrayList<TimeStepData> data;

    public WiFILogger(String fileName){
        this.fileName = fileName;
        data = new ArrayList<TimeStepData>();
    }

    public void addTimesStep(TimeStepData tsData){
        data.add(tsData);
    }

    public void log(){
        Date date = Calendar.getInstance().getTime();
        DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        DateFormat timeFormat = new SimpleDateFormat("HH:mm:ss");
        String ds = dateFormat.format(date);
        String ts = timeFormat.format(date);
        StringBuilder pathBuilder = new StringBuilder();
        pathBuilder.append("/WiFiMaps/");
        pathBuilder.append(fileName);
        pathBuilder.append("/");
        pathBuilder.append(ds);
        pathBuilder.append("/");
        String path = Environment.getExternalStorageDirectory().getAbsolutePath().concat(pathBuilder.toString());
        String logName = ts + ".log";
        File outputDir = new File(path);
        outputDir.mkdirs();
        File logFile = new File(outputDir, logName);
        try{
            FileOutputStream fos = new FileOutputStream(logFile);
            fos.write(string().getBytes());
            fos.close();
        }catch (Exception e){
            Log.d("INF", e.toString());
        }

    }

    private String string(){
        StringBuilder sb = new StringBuilder();

        for(TimeStepData tsData : data){
            sb.append(tsData.toString());
            sb.append("\n");
        }
        return sb.toString();
    }
}
