package com.android.wifi.navigator;

import android.app.Activity;
import android.app.ListActivity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import com.android.wifi.navigator.json.JSONParser;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: linuxshaman
 * Date: 08.04.13
 * Time: 20:09
 * To change this template use File | Settings | File Templates.
 */
public class MapChooser extends ListActivity {
    private List<String> fileList;
    File root;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        fileList = new ArrayList<String>();
        root = new File(Environment.getExternalStorageDirectory().getAbsolutePath().concat("/WiFiMaps"));
        for(File f : root.listFiles()){
            if(!f.isDirectory()){
                String fileName = f.getName();
                fileName = fileName.replace(".json", "");
                fileList.add(fileName);
            }
        }
        ArrayAdapter<String> directoryList = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, fileList);
        setListAdapter(directoryList);
    }

    @Override
    public void onListItemClick(ListView parent, View v, int position, long id) {
        File fileToRead = new File(root.getPath() + "/" + fileList.get(position) + ".json");
        FileInputStream fis = null;
        String text = "";
        try{
            fis = new FileInputStream(fileToRead);
            char current;
            while(fis.available() > 0){
                current = (char)fis.read();
                text += String.valueOf(current);
            }
        }catch (Exception e){
            Log.d("Error", e.toString());
        }finally {
            if(fis != null){
                try {
                    fis.close();
                }catch (IOException ignored){

                }
            }
        }
        JSONParser.setFileName(fileList.get(position));
        JSONParser.setText(text);
        finish();
    }
}