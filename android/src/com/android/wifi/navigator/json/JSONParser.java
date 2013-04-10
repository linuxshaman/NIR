package com.android.wifi.navigator.json;

import android.util.Log;
import com.android.wifi.navigator.map.Building;
import com.android.wifi.navigator.map.Level;
import com.android.wifi.navigator.map.Wall;
import com.android.wifi.navigator.map.WiFiSpot;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 11.03.13
 * Time: 8:10
 * To change this template use File | Settings | File Templates.
 */
public class JSONParser {

    private static Building building = null;
    private static String text = null;
    private static String fileName;


    public static Building getBuilding(){
        if(building == null) building = loadBuildingData();
        return building;
    }

    public static void setText(String t){
        text = t;
        building = loadBuildingData();
    }

    private static Building loadBuildingData(){
        if(text == null){
            building = null;
        }else{
            try {
                JSONObject jObject = new JSONObject(text);
                JSONObject buildingObject = jObject.getJSONObject("building");
                float w = (float) buildingObject.getDouble("w");
                float l = (float)buildingObject.getDouble("l");
                int h = buildingObject.getInt("h");
                building = new Building(w, l, h);
                JSONArray wallArray = buildingObject.getJSONArray("Wall");
                for(int i = 0; i < wallArray.length();  i++){
                    JSONObject wallObject = wallArray.getJSONObject(i).getJSONObject("wall");
                    float x = (float)wallObject.getDouble("x");
                    float y = (float)wallObject.getDouble("y");
                    float width = (float)wallObject.getDouble("w");
                    float height = (float)wallObject.getDouble("l");
                    building.addWall(new Wall(x, y, w, h, 1));
                }
                JSONArray wifiArray = buildingObject.getJSONArray("WiFi");
                for(int i = 0; i < wifiArray.length(); i ++){
                    JSONObject wifiObject =  wifiArray.getJSONObject(i);
                    String objectString = wifiObject.toString();
                    String wifiName  = objectString.split("\\{")[1].replace(":", "").replace("\"", "");
                    JSONObject realObject = wifiObject.getJSONObject(wifiName);
                    float x = (float)realObject.getDouble("x");
                    float y = (float)realObject.getDouble("y");
                    building.addWiFi(new WiFiSpot(x, y, 1, wifiName));
                }

            }catch (JSONException e){
                Log.d("JSONERROR", e.toString());
            }
        }
        return building;
    }

    public static void setFileName(String fn){
       fileName = fn;
    }

    public static String getFileName(){
        return fileName;
    }
}
