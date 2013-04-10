package com.android.wifi.navigator.map;

import java.util.ArrayList;

/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 11.03.13
 * Time: 7:46
 * To change this template use File | Settings | File Templates.
 */
public class Building {
    protected float width;
    protected float length;
    protected int height;
    protected ArrayList<Level> levels;

    public ArrayList<Level> getLevels() {
        return levels;
    }

    public void setLevels(ArrayList<Level> levels) {
        this.levels = levels;
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

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public Building(float width, float length, int height) {
        this.width = width;
        this.length = length;
        this.height = height;
        levels = new ArrayList<Level>();
        levels.add(new Level(1));
    }

    public void addLevel(Level level){
        if(level.getZ() <= height){
            levels.add(level);
        }
    }

    public WiFiSpot getSpotBy(String networkName){
        for(Level l : levels){
              for(MapObject o : l.getObjects()){
                  if(o.getName().equals("wifi")){
                      WiFiSpot wifi = (WiFiSpot)o;
                      if(wifi.getNetworkName().equals(networkName)) return wifi;
                  }
              }
        }
        return null;
    }

    public void addWall(Wall wall){
        levels.get(0).addObject(wall);
    }

    public void addWiFi(WiFiSpot wifi){
        levels.get(0).addObject(wifi);
    }
}
