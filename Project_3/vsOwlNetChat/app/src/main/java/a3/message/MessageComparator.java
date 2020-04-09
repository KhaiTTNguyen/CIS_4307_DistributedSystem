package a3.message;

import java.util.Comparator;

/**
 * Message comparator class. Use with PriorityQueue.
 */
public class MessageComparator implements Comparator<Message> {

    /* return -1 if lhs < rhs
    * return 1 if lhs > rhs
    * return 0 if lhs = rhs
    * */
    @Override
    public int compare(Message lhs, Message rhs) {
        if (lhs.getTimeStamp().happenedBefore(rhs.getTimeStamp())){
            return -1;
        } else {
            return 1;
        }
    }

}
