package com.example.cindygregory.helllo;

import android.os.Bundle;
import android.widget.TextView;
import android.app.Activity;
import android.widget.Toast;
import android.net.Uri;
import android.content.Intent;
import android.util.Log;
import com.example.cindygregory.helllo.MyCustomClass;

public class Activity2 extends Activity {
    private static final String TAG = "Activity2";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.i(TAG, "onCreate() called");

        Bundle bundle = getIntent().getExtras();

        TextView text = new TextView(this);
        String str = "yo dude, you're " + bundle.getInt("age2");
        text.setText(str);
        setContentView(text);

        Toast.makeText(this, "dude you suck", Toast.LENGTH_SHORT).show();
        
        Intent i = new Intent();

        i.putExtra("age3", 56);
        i.setData(Uri.parse("http://www.microsoft.com"));
        setResult(RESULT_OK, i);

        MyCustomClass obj = (MyCustomClass) getIntent().getSerializableExtra("MyObject");
        Toast.makeText(this, obj.Name(), Toast.LENGTH_SHORT).show();
        Toast.makeText(this, obj.Email(), Toast.LENGTH_SHORT).show();
        finish();
   }

}
