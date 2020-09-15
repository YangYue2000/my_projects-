package schedule;

import java.util.Vector;

public class session {
	public int rating = -1;
//	initialize the rating to an negative number
//	because a professor may have a score of 0
	public Class parent;
	public String name;
	public int start;
	public int finish;
	public Vector<Integer> day = new Vector<Integer>();
}
