package a3.clock;

public class LamportClock implements Clock {
    private int time;

    @Override
    public void update(Clock other) {
        if (time < other.getTime()){
            time = other.getTime();
        }
    }

    @Override
    public void setClock(Clock other) {
        time  = other.getTime();
    }

    @Override
    public void tick(Integer pid) {
        time++;
    }

    @Override
    public boolean happenedBefore(Clock other) {
        if (time < other.getTime()){return true;}
        return false;
    }

    @Override
    public void setClockFromString(String clock) {
        try
        {
            time = Integer.parseInt(clock);
        }
        catch (NumberFormatException nfe)
        {
            time = 0;
        }
    }

    public String toString(){
        return Integer.toString(time);
    }

    public int getTime() {
        return time;
    }

    @Override
    public void setTime(int testTime) {
        time = testTime;
    }
}
