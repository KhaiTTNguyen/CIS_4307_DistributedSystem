package com.example.vsowlnetchat;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.util.PriorityQueue;
import java.util.UUID;

import a3.message.ErrorCodes;
import a3.message.Message;
import a3.message.MessageComparator;
import a3.udpclient.NetworkConsts;

public class chatActivity extends AppCompatActivity {
    public int port = NetworkConsts.UDP_PORT;
    public String ip = NetworkConsts.SERVER_ADDRESS;
    public int buffSize = NetworkConsts.PAYLOAD_SIZE;
    public int timeout = NetworkConsts.SOCKET_TIMEOUT;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.chat_activity);

        Intent fromMain = getIntent();
        final String userName = fromMain.getStringExtra("user");
        Button deregisterButton = findViewById(R.id.deregisterButton);
        Button retreiveChatLogButton = findViewById(R.id.retreiveChatLogButton);

        // deregister
        deregisterButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    byte[] buf = deregisterUser(userName).toString().getBytes();
                    InetAddress address = InetAddress.getByName(ip);
                    DatagramSocket socket = new DatagramSocket();
                    socket.setReuseAddress(true);
                    socket.setSoTimeout(2000);

                    //Send packet
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
                        Toast.makeText(chatActivity.this, errorText, Toast.LENGTH_SHORT).show();
                    }

                    //ACK message
                    if (received.getJSONObject("header").getString("type").equals("ack")) {
                        Toast.makeText(chatActivity.this, "Reply received. ACK", Toast.LENGTH_SHORT).show();
                        finish();
                    }
                    socket.close();

                } catch (JSONException e) {
                    e.printStackTrace();
                } catch (UnknownHostException e) {
                    e.printStackTrace();
                } catch (SocketException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        // retreiveChatLogButton.
        retreiveChatLogButton.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v) {
                try {
                    PriorityQueue<Message> messageQueue = new PriorityQueue<Message>(10, new MessageComparator());
                    byte[] buf = retrieveChat(userName).toString().getBytes();

                    // Set up socket
                    InetAddress address = InetAddress.getByName(ip);
                    DatagramSocket socket = new DatagramSocket();
                    socket.setReuseAddress(true);
                    socket.setSoTimeout(2000);

                    //Send packet
                    DatagramPacket packet = new DatagramPacket(buf, buf.length, address, port);
                    socket.send(packet);

                    //Receive packet
                    byte[] buf2 = new byte[buffSize];

                    DatagramPacket getack = new DatagramPacket(buf2, buf2.length);
                    while (true) {
                        try {
                            socket.receive(getack);
                            buf2 = getack.getData();
                            JSONObject received = new JSONObject(new String(buf2));
                            Message ms = new Message(received);
                            messageQueue.add(ms);
                        } catch (SocketTimeoutException e) {
                            break;
                        }
                    }
                    socket.close();
                    TextView messageList = findViewById(R.id.chatLogView);
                    messageList.setText(messageQueue.toString());
                    // display on text view
                    // ................
                } catch (JSONException e) {
                    Toast.makeText(chatActivity.this, "JSON error", Toast.LENGTH_SHORT).show();
                    e.printStackTrace();
                } catch (UnknownHostException e){
                    Toast.makeText(chatActivity.this, "IP address error", Toast.LENGTH_SHORT).show();
                    e.printStackTrace();
                } catch (SocketTimeoutException e) {
                    Toast.makeText(chatActivity.this, "Socket timeout", Toast.LENGTH_SHORT).show();
                } catch (SocketException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    Toast.makeText(chatActivity.this, "I/O error", Toast.LENGTH_SHORT).show();
                    e.printStackTrace();
                }
            }
        });
    }


    //Make JSON user object
    public JSONObject deregisterUser(String userName) throws JSONException {
        String uuid = UUID.nameUUIDFromBytes(userName.getBytes()).toString();
        JSONObject obj = new JSONObject();
        JSONObject header = new JSONObject();
        header.put("username", userName);
        header.put("uuid", uuid);
        header.put("timestamp", "{}");
        header.put("type", "deregister");
        obj.put("header", header);
        obj.put("body", new JSONObject());
        return obj;
    }

    //Make JSON user object
    public JSONObject retrieveChat(String userName) throws JSONException {
        String uuid = UUID.nameUUIDFromBytes(userName.getBytes()).toString();
        JSONObject obj = new JSONObject();
        JSONObject header = new JSONObject();
        header.put("username", userName);
        header.put("uuid", uuid);
        header.put("timestamp", "{}");
        header.put("type", "retrieve_chat_log");
        obj.put("header", header);
        obj.put("body", new JSONObject());
        return obj;
    }
}
