package com.android.wifi.navigator.algorithms;

import android.net.wifi.ScanResult;
import com.android.wifi.navigator.map.Building;
import com.android.wifi.navigator.map.WiFiSpot;

import java.util.ArrayList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 11.03.13
 * Time: 21:10
 * To change this template use File | Settings | File Templates.
 */
public class AlgorithmData {
    public ArrayList<WifiData> spotsData;
    public int width;
    public int length;


    public AlgorithmData(Building building, List<ScanResult> scanResults) {
        spotsData = new ArrayList<WifiData>();
        width = (int)building.getWidth();
        length = (int)building.getLength();

        for(ScanResult res : scanResults){
            String networkName  = res.SSID;
            WiFiSpot spot = building.getSpotBy(networkName);
            if(spot != null){
                spotsData.add(new WifiData(spot, res.level));
            }
        }
    }
}
