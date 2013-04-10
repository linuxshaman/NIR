package com.android.wifi.navigator.algorithms;

/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 11.03.13
 * Time: 21:03
 * To change this template use File | Settings | File Templates.
 */
public class Vector2D {
    public float x;
    public float y;

    public Vector2D(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public Vector2D(){
        x = 0.f;
        y = 0.f;
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append(x);
        sb.append("|");
        sb.append(y);
        sb.append("|");
        return sb.toString();
    }
}
