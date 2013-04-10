package com.android.wifi.navigator;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import com.android.wifi.navigator.algorithms.Algorithm;
import com.android.wifi.navigator.algorithms.AlgorithmData;
import com.android.wifi.navigator.algorithms.Vector2D;
import com.android.wifi.navigator.json.JSONParser;
import com.android.wifi.navigator.log.TimeStepData;
import com.android.wifi.navigator.log.WiFILogger;
import com.android.wifi.navigator.map.Building;

import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

public class WiFiActivity extends Activity {
    /**
     * Called when the activity is first created.
     */


    WifiManager wifi;
    WiFiReciver reciver;
    TextView scanResult;
    Timer timer;
    JSONParser parser;
    boolean  started;
    private WiFILogger logger;


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        started = false;
        setContentView(R.layout.main);
        wifi = (WifiManager)getSystemService(Context.WIFI_SERVICE);
        reciver = new WiFiReciver();
        scanResult = (TextView)findViewById(R.id.textView);
    }

    public void startButton_click(View v){
        if(!started && JSONParser.getBuilding() != null)
            startScan();
    }

    public void endButton_click(View v){
        if(started)
            stopScan();
    }

    public void loadButton_click(View v){
        Intent intent = new Intent(this, MapChooser.class);
        startActivity(intent);
    }

    private void startScan(){
        logger = new WiFILogger(JSONParser.getFileName());
        registerReceiver(reciver, new IntentFilter(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION));
        started = true;
        timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                timerMethod();
            }
        }, 0, 6000);
    }

    private void stopScan(){
        started = false;
        timer.cancel();
        unregisterReceiver(reciver);
        logger.log();
    }

    private void timerMethod(){
          runOnUiThread(rTimer);
    }

    private Runnable rTimer = new Runnable() {
        @Override
        public void run() {
            wifi.startScan();
        }
    };


    class WiFiReciver extends BroadcastReceiver{

        @Override
        public void onReceive(Context context, Intent intent) {
            Building b = parser.getBuilding();
            if(b != null){
                StringBuilder sb = new StringBuilder(scanResult.getText());
                sb.append("\n------------------NEW-RESULT-------------------\n");
                List<ScanResult> results = wifi.getScanResults();
                for(ScanResult res : results){
                    sb.append(res.SSID);
                    sb.append(" | ");
                    sb.append(res.level);
                    sb.append("\n");
                }
                sb.append("------------------------------------------------\n");
                String s = sb.toString();
                scanResult.setText(s.toCharArray(), 0, s.length());

                AlgorithmData data = new AlgorithmData(b, results);
                Vector2D a1 = Algorithm.algorithm3(data);
                Vector2D a2 = Algorithm.algorithm4(data);
                Vector2D a3 = Algorithm.algorithm5(data);
                logger.addTimesStep(new TimeStepData(data, a1, a2, a3));
        }
}
    }
}
