package a3.clock;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

public class VectorClock  implements Clock {
    private HashMap<Integer, Integer> clockMap;
    public VectorClock(){
        clockMap = new HashMap<Integer, Integer>();
    }

    public HashMap <Integer, Integer> getClockMap (){
        return clockMap;
    }

    @Override
    /*
    * Compare length, update using larger
    * based on ID
    * */
    public void update(Clock other) {}

    public void update(VectorClock other) {
        // pick larger map
        // some pid in one not exits in another

        for (int pID : other.getClockMap().keySet()){
            if (!clockMap.containsKey(pID)){
                clockMap.put(pID, other.getTime(pID));
            } else {
                if (clockMap.get(pID) < other.getTime(pID)){
                    clockMap.put(pID, other.getTime(pID));
                }
            }
        }
    }

    @Override
    public void setClock(Clock other) {}

    public void setClock(VectorClock other) {
        for (int pID : clockMap.keySet()){
            if (!clockMap.containsKey(pID)){
                clockMap.put(pID, other.getTime(pID));
            } else{
                clockMap.put(pID, other.getTime(pID));
            }
        }
    }

    @Override
    public void tick(Integer pid) {
        clockMap.put(pid, clockMap.get(pid) + 1);
    }

    @Override
    public boolean happenedBefore(Clock other) { return false; }

    public boolean happenedBefore(VectorClock other) {
        if (clockMap.size() <= other.getClockMap().size()){
            for (int pID : clockMap.keySet()){
                if (clockMap.get(pID) > other.getClockMap().get(pID)){
                    return false;
                }
            }
        }

        if (clockMap.size() > other.getClockMap().size()){
            for (int pID : other.getClockMap().keySet()){
                if (clockMap.get(pID) > other.getClockMap().get(pID)){
                    return false;
                }
            }
        }
        return true;
    }

    public String toString(){
        if(clockMap == null || clockMap.isEmpty()){
            return "{}";
        }

        String toReturn = "{";
        for (int pID : clockMap.keySet()){
            toReturn = toReturn + "\"" + pID + "\"" + ":" + clockMap.get(pID) + ",";
        }
        toReturn = toReturn.substring(0, toReturn.length()-1);
        return toReturn += "}";
    }

    // {'0':1,'1':2,'2':3}

    @Override
    public void setClockFromString(String clock) {
        // invalid string
        if (clock.equals("{}") || clock == null){
            clockMap = new HashMap<Integer, Integer>();
            return;
        }

        // valid string
        clock = clock.substring(1, clock.length()-1);
        ArrayList<Integer> key = new ArrayList<Integer>();
        ArrayList<Integer> value = new ArrayList<Integer>();
        for (String pair : clock.split(",")) {
            String[] kv = pair.split(":");
            try {
                key.add(Integer.parseInt(kv[0].substring(1,2)));
                value.add(Integer.parseInt(kv[1]));
            } catch (NumberFormatException nfe) {
                return;
            }
        }

        for (int i=0; i<key.size(); i++) {
            clockMap.put(key.get(i), value.get(i));
        }
    }

    @Override
    public int getTime(){ return 0; }

    public int getTime(int pID) {
        return clockMap.get(pID);
    }

    public void setTime(int testTime) { }

    public void addProcess(int pID, int p_testTime) {
        //if (!clockMap.containsKey(pID)){
        clockMap.put(pID, p_testTime);
        //}
    }
}
