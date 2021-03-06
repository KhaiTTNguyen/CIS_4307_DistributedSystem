package com.example.vsowlnetchat;


import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.os.StrictMode;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.util.UUID;

import a3.message.ErrorCodes;
import a3.udpclient.NetworkConsts;

public class MainActivity extends AppCompatActivity {

    public int port = NetworkConsts.UDP_PORT;
    public String ip = NetworkConsts.SERVER_ADDRESS;
    public int buffSize = NetworkConsts.PAYLOAD_SIZE;
    public int timeout = NetworkConsts.SOCKET_TIMEOUT;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_activity);

        //Allow network on main thread
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        //Elements in the UI
        final EditText userName = findViewById(R.id.userName);
        Button joinButton = findViewById(R.id.joinButton);
        Button settingButton = findViewById(R.id.settingButton);

        //Setting
        settingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent toSetting = new Intent(MainActivity.this, settingsActivity.class);
                toSetting.putExtra("ip", ip);
                toSetting.putExtra("port", String.valueOf(port));
                MainActivity.this.startActivityForResult(toSetting, 1);
            }
        });

        //Join chat room
        joinButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    //Set up socket
                    InetAddress address = InetAddress.getByName(ip);
                    DatagramSocket socket = new DatagramSocket();
                    socket.setReuseAddress(true);
                    socket.setSoTimeout(timeout);

                    //Send packet
                    String user = userName.getText().toString();
                    byte[] buf = registerUser(user).toString().getBytes();
                    DatagramPacket packet = new DatagramPacket(buf, buf.length, address, port);
                    socket.send(packet);

                    //Receive ack
                    byte[] buf2 = new byte[buffSize];
                    DatagramPacket getack = new DatagramPacket(buf2, buf2.length);
                    socket.receive(getack);
                    buf2 = getack.getData();
                    JSONObject received = new JSONObject(new String(buf2));

                    //Error message
                    if (received.getJSONObject("header").getString("type").equals("error")) {
                        String errorText = "Reply received. Error: ";
                        errorText += ErrorCodes.getStringError(received.getJSONObject("body").getInt("content"));
                        Toast.makeText(MainActivity.this, errorText, Toast.LENGTH_SHORT).show();
                    }

                    //ACK message
                    if (received.getJSONObject("header").getString("type").equals("ack")) {
                        Toast.makeText(MainActivity.this, "Reply received. ACK", Toast.LENGTH_SHORT).show();
                        Intent changeToChat = new Intent(MainActivity.this, chatActivity.class);
                        changeToChat.putExtra("user", user);
                        MainActivity.this.startActivity(changeToChat);
                    }
                    socket.close();
                } catch (UnknownHostException e) {
                    Toast.makeText(MainActivity.this, "IP address error", Toast.LENGTH_SHORT).show();
                    e.printStackTrace();
                } catch (SocketException e) {
                    Toast.makeText(MainActivity.this, "Socket error", Toast.LENGTH_SHORT).show();
                    e.printStackTrace();
                } catch (JSONException e) {
                    Toast.makeText(MainActivity.this, "JSON error", Toast.LENGTH_SHORT).show();
                    e.printStackTrace();
                } catch (SocketTimeoutException e) {
                    Toast.makeText(MainActivity.this, "Socket timeout", Toast.LENGTH_SHORT).show();
                } catch (IOException e) {
                    Toast.makeText(MainActivity.this, "I/O error", Toast.LENGTH_SHORT).show();
                    e.printStackTrace();
                }
            }
        });
    }

    //Make JSON user object
    public JSONObject registerUser(String userName) throws JSONException {
        String uuid = UUID.nameUUIDFromBytes(userName.getBytes()).toString();
        JSONObject obj = new JSONObject();
        JSONObject header = new JSONObject();
        header.put("username", userName);
        header.put("uuid", uuid);
        header.put("timestamp", "{}");
        header.put("type", "register");
        obj.put("header", header);
        obj.put("body", new JSONObject());
        return obj;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // Check which request we're responding to
        if (requestCode == 1) {
            // Make sure the request was successful
            if (resultCode == RESULT_OK) {
                Toast.makeText(MainActivity.this, "Change ip and port success", Toast.LENGTH_SHORT).show();
                ip = data.getStringExtra("ip");
                port = Integer.parseInt(data.getStringExtra("port"));
            } else if (resultCode == RESULT_CANCELED) {
                Toast.makeText(MainActivity.this, "Change ip and port fail", Toast.LENGTH_SHORT).show();
                ip = NetworkConsts.SERVER_ADDRESS;
                port = NetworkConsts.UDP_PORT;
            }
        }
    }

}
