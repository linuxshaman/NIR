package com.android.wifi.navigator.map;


/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 11.03.13
 * Time: 7:48
 * To change this template use File | Settings | File Templates.
 */
public class MapObject {
    protected float width;
    protected float length;
    protected String name;
    protected float x;
    protected float y;
    protected int z;


    public MapObject(float width, float length, String name, float x, float y, int z) {
        this.width = width;
        this.length = length;
        this.name = name;
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public float getWidth() {
        return width;
    }

    public void setWidth(float width) {
        this.width = width;
    }

    public float getLength() {
        return length;
    }

    public void setLength(float length) {
        this.length = length;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public int getZ() {
        return z;
    }

    public void setZ(int z) {
        this.z = z;
    }
}
