package a3.message;

import org.json.JSONException;
import org.json.JSONObject;

import a3.clock.VectorClock;

public class Message {
    private VectorClock timeStamp;
    private String content;

    public Message(JSONObject packet) throws JSONException {
        JSONObject header = null;
        try {
            header = packet.getJSONObject("header");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        JSONObject body = packet.getJSONObject("body");
        this.timeStamp = new VectorClock();
        this.timeStamp.setClockFromString(header.getString("timestamp"));
        if (body.has("content")) {
            this.content = body.getString("content");
        }
    }

    public VectorClock getTimeStamp() {
        return this.timeStamp;
    }

    public void setTimeStamp(VectorClock timeStamp) {
        this.timeStamp = timeStamp;
    }

    public String getContent() {
        return this.content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public String toString() {
        return "VectorClock: "+ this.timeStamp.toString() + " - Content: " + this.content + "\n";
    }
}
