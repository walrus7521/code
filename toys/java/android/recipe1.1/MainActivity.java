package com.example.cindygregory.helllo;

import android.os.Bundle;
import android.content.Intent;
import android.app.Activity;
import android.net.Uri;
import android.widget.Toast;
import android.util.Log;
import android.view.View;

public class MainActivity extends Activity {
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.i(TAG, "onCreatek() called");
        setContentView(R.layout.activity_main);
    }

    public void onClick(View view) {
        Intent i = new Intent("com.example.cindygregory.helllo.Activity2");

        Log.i(TAG, "onClick() called");

        i.putExtra("str1", "this is a string");
        i.putExtra("age1", 25);

        // let's get some data back from Activity2
        Bundle extras = new Bundle();
        extras.putString("str2", "this is another string");
        extras.putInt("age2", 35);
        i.putExtras(extras);


        MyCustomClass myObject = new MyCustomClass();
        myObject.setName("Bart Bartel");
        myObject.setEmail("bartb7@gmail.com");
        i.putExtra("MyObject", myObject);

        startActivityForResult(i, 1);
        
     }

    public void onActivityResult(int requestCode,
             int resultCode, Intent data)
    {
        Log.i(TAG, "onActivityResult() called");
        if (requestCode == 1) {
            if (resultCode == RESULT_OK) {
                Toast.makeText(this, Integer.toString(
                        data.getIntExtra("age3", 0)),
                        Toast.LENGTH_SHORT).show();

                Uri url = data.getData();
                Toast.makeText(this, url.toString(),
                        Toast.LENGTH_SHORT).show();

                 
             }
        }
    }

}
