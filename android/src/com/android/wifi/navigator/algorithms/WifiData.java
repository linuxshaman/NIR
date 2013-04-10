package com.android.wifi.navigator.algorithms;

import android.util.Log;
import com.android.wifi.navigator.map.WiFiSpot;

/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 11.03.13
 * Time: 21:11
 * To change this template use File | Settings | File Templates.
 */
public class WifiData {
    public WiFiSpot spot;
    public int rssi;

    public WifiData(WiFiSpot spot, int rssi) {
        this.spot = spot;
        this.rssi = rssi;
    }

    public WifiData() {
    }

    public String toString(){
        Log.i("INF", "2.2.1");
        StringBuilder sb = new StringBuilder();
        sb.append(spot.toString());
        Log.i("INF", "2.2.2");
        sb.append("|");
        sb.append(rssi);
        sb.append("|");
        Log.i("INF", "2.2.3");
        return sb.toString();
    }
}
