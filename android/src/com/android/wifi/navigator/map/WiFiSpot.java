package com.android.wifi.navigator.map;

/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 11.03.13
 * Time: 7:48
 * To change this template use File | Settings | File Templates.
 */
public class WiFiSpot extends MapObject {

    protected String networkName;

    public WiFiSpot(float x, float y, int z, String networkName) {
        super(0, 0, "wifi", x, y, z);
        this.networkName = networkName;
    }

    public String getNetworkName() {
        return networkName;
    }

    public void setNetworkName(String networkName) {
        this.networkName = networkName;
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append(networkName);
        sb.append("|");
        sb.append(x);
        sb.append("|");
        sb.append(y);
        sb.append("|");
        return sb.toString();
    }
}
