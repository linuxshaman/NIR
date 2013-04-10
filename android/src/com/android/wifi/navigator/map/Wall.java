package com.android.wifi.navigator.map;

/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 11.03.13
 * Time: 7:48
 * To change this template use File | Settings | File Templates.
 */
public class Wall extends MapObject {
    public Wall(float width, float length, float x, float y, int z) {
        super(width, length, "wall", x, y, z);
    }
}
