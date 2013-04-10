package com.android.wifi.navigator.map;

import java.util.ArrayList;

/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 11.03.13
 * Time: 7:49
 * To change this template use File | Settings | File Templates.
 */
public class Level {

    protected int z;
    protected ArrayList<MapObject> objects;

    public ArrayList<MapObject> getObjects() {
        return objects;
    }

    public void setObjects(ArrayList<MapObject> objects) {
        this.objects = objects;
    }

    public void addObject(MapObject object){
        objects.add(object);
    }

    public int getZ() {
        return z;
    }

    public void setZ(int z) {
        this.z = z;
    }

    public Level(int z) {
        this.z = z;
        objects = new ArrayList<MapObject>();
    }
}
