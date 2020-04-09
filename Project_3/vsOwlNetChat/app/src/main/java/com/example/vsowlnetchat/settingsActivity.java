package com.example.vsowlnetchat;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Patterns;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class settingsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.settings_activity);

        // UI components
        final EditText editIpAddress = findViewById(R.id.editIP);
        final EditText editPort = findViewById(R.id.editPort);
        Button settingDoneButton = findViewById(R.id.settingDoneButton);
        Intent fromMain = getIntent();

        editIpAddress.setText((fromMain.getStringExtra("ip")));
        editPort.setText(fromMain.getStringExtra("port"));

        // change settings
        settingDoneButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                try {
                    int port = Integer.parseInt(editPort.getText().toString());
                    String ipAddr = editIpAddress.getText().toString();
                    if (Patterns.IP_ADDRESS.matcher(ipAddr).matches() && port >= 0 && port <= 65535) {
                        Intent toMain = new Intent();
                        toMain.putExtra("ip", ipAddr);
                        toMain.putExtra("port", String.valueOf(port));
                        setResult(Activity.RESULT_OK, toMain);
                        finish();
                    } else {
                        setResult(Activity.RESULT_CANCELED);
                        finish();
                    }
                } catch (NumberFormatException e) {
                    setResult(Activity.RESULT_CANCELED);
                    finish();
                }
            }
        });
    }
}
