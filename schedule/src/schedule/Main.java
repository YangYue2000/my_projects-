package schedule;

import java.io.IOException;
import java.security.cert.CertPathChecker;
import java.sql.DriverManager;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Vector;
import java.util.zip.Adler32;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class Main {
	public static Vector<Vector<session>> solution = new Vector<Vector<session>>();
	public static void main(String[] args) throws IOException {
		Scanner scanner = new Scanner(System.in);
		Vector<Class> classes = new Vector<Class>();
		Vector<session> sessions = new Vector<session>();
		String webPage = "https://classes.usc.edu/term-20203/";
		org.jsoup.nodes.Document doc = Jsoup.connect(webPage).get();
		System.out.println("type in a class name");
		String class_name = scanner.nextLine().toUpperCase();
		while(true) {
			System.out.println("class name is: "+class_name);
			Class bufferClass = new Class();
	    	bufferClass.name = class_name;
	    	String prefix = class_name.substring(0,class_name.indexOf("-")).toLowerCase();
			doc = Jsoup.connect("https://classes.usc.edu/term-20203/classes/"+prefix+"/").get();
			Elements tables;
			if(prefix.equals("writ")) {
				tables = doc.select("div#"+class_name+" tr[data-section-id]");
			}
			else {
				tables = doc.select("div#"+class_name+" tr[data-section-id]");
			}
//			System.out.println(tables.toString());
			for(Element table : tables) {
		    	Elements details = table.select("td");
		    	if(details.size()>0) {
		    		int start;
		    		int finish;
		    		boolean special_case = false;
		    		
		    		String time = details.get(3).text();
		    		int time_division;
		    		int boundary;
		    		String s = time.substring(0, time.indexOf("-"));
		    		String f = time.substring((time.indexOf("-")+1));
		    		time_division = s.indexOf(":");
		    		boundary = s.indexOf("m");
		    		int s_hour = Integer.parseInt(s.substring(0, s.indexOf(":")));
		    		int s_min;
		    		if(s.charAt(time_division+1)=='0') {
		    			s_min = s.charAt(time_division+2)-'0';
		    		}
		    		else {
		    			s_min = Integer.parseInt(s.substring(time_division+1, time_division+3));
		    		}
		    		start = s_hour*60+s_min;
		    		if(boundary>0) {
		    			special_case = true;
		    		}
		    		
		    		
		    		time_division = f.indexOf(":");
		    		boundary = f.indexOf("m");
		    		int f_hour = Integer.parseInt(f.substring(0, f.indexOf(":")));
		    		int f_min;
		    		if(f.charAt(time_division+1)=='0') {
		    			f_min = f.charAt(time_division+2)-'0';
		    		}
		    		else {
		    			f_min = Integer.parseInt(f.substring(time_division+1, time_division+3));
		    		}
		    		finish = f_hour*60+f_min;
		    		
		    		if(f.charAt(boundary-1)=='p') {
		    			if(special_case) {
		    				if(f_hour!=12) {
		    					finish += 720;
		    				}
		    			}
		    			else {
		    				if(s_hour!=12) {
		    					start+=720;
		    				}
		    				if(f_hour!=12) {
		    					finish += 720;
		    				}
		    			}
		    		}
//		    		
		    		System.out.println("start time: "+start+" finish time: "+finish);
//		    		
		    		session bufferSession = new session();
		    		bufferSession.start = start;
		    		bufferSession.finish = finish;
		    		bufferSession.name = class_name;
		    		
		    		String days = details.get(4).text();
		    		if(days.indexOf(",")<0) {
		    			if(day_to_num(days)==0) {
		    				if(days.equals("TBA")) {
		    					
		    				}
		    				else if(days.equals("MWF")){
		    					bufferSession.day.add(1);
		    					bufferSession.day.add(2);
		    					bufferSession.day.add(3);
		    				}
		    			}
		    			else {
		    				bufferSession.day.add(day_to_num(days));
		    			}
		    		}
		    		else {
		    			bufferSession.day.add(day_to_num(days.substring(0, days.indexOf(","))));
		    			bufferSession.day.add(day_to_num(days.substring(days.indexOf(",")+2)));
		    		}
//		    		
		    		for(int i=0;i<bufferSession.day.size();i++) {
		    			System.out.println(bufferSession.day.get(i));
		    		}
		    		bufferClass.sessions.add(bufferSession);
		    	}
		    }
		   classes.add(bufferClass);
			System.out.println("type in a class name");
			 class_name = scanner.nextLine().toUpperCase();
			 if(class_name.equals("F")) {
				 break;
			 }
		}
		

		
		
		
		
//      below are test cases;
//		Class A = new Class();
//		Class B = new Class();
//		Class C = new Class();
//		A.name = "a";
//		B.name = "b";
//		C.name = "c";
//		session A1 = new session();
//		session A2 = new session();
//		session B1 = new session();
//		session B2 = new session();
//		session C1 = new session();
//		A1.name = "A1";
//		A1.start = 8;
//		A1.finish = 9;
//		A1.day.add(1);
//		A1.day.add(3);
//		A2.name = "A2";
//		A2.start = 11;
//		A2.finish = 13;
//		A2.day.add(1);
//		A2.day.add(3);
//		B1.name = "B1";
//		B1.start = 10;
//		B1.finish = 12;
//		B1.day.add(1);
//		B2.name = "B2";
//		B2.start = 11;
//		B2.finish =13;
//		B2.day.add(4);
//		C1.name = "C1";
//		C1.start = 9;
//		C1.finish = 11;
//		C1.day.add(3);
//		C1.parent = C;
//		A.sessions.add(A1);
//		A.sessions.add(A2);
//		B.sessions.add(B1);
//		B.sessions.add(B2);
//		C.sessions.add(C1);
//
//		Vector<Class> input = new Vector<Class>();
//		input.add(A);
//		input.add(B);
//		input.add(C);
		Vector<session> result = new Vector<session>();
		solve(classes, result, 0);
		for(int i=0; i<solution.size();i++) {
			Vector<session> verify = solution.get(i);
			for(int j=0; j<verify.size(); j++) {
				print(verify.get(j).name);
				System.out.println(verify.get(j).start);
				System.out.println(verify.get(j).finish);
				for(int k=0; k<verify.get(j).day.size();k++) {
					System.out.println(verify.get(j).day.get(k));
				}
			} 
			print(" ");
		}
	}
	
	public static void print(String input) {
		System.out.println(input);
	}
	
	public static void solve(Vector<Class> input, Vector<session> result, int index) {
		if(index==0) {
			Vector<session> temp = input.get(index).sessions;
			for(int i=0;i<temp.size();i++) {
				Vector<session> buffer = (Vector<session>)result.clone();
				session target = temp.get(i);
				buffer.add(target);
				solve(input, buffer, index+1);
			}
		}
		else if(result.size()==input.size()) {
			solution.add(result);
//			this is the terminating condition, when the amount of sessions
//			matches the amount of classes, it is a complete schedule, and 
//			none of the session in this schedule is conflicting. 
		}
		else {
			Vector<session> temp = input.get(index).sessions;
			for(int i=0;i<temp.size();i++) {
				session target = temp.get(i);
				//not in first layer, check if this session is 
				//conflicting with any previous session
				if(check(result, target)) {
					Vector<session> buffer = (Vector<session>)result.clone();
					buffer.add(target);
					solve(input, buffer, index+1);
					//if not conflicting, add it and move on to the next 
					//layer by incrementing the index
					//if conflicting, nothing will happen, so the recursion
					//stops at this layer(or depth in DFS).
				}
			}
		}
	}
	
	public static boolean check(Vector<session> input, session target) {
		for(int i=0; i<input.size();i++) {
			if(!compare(input.get(i), target)) {
				return false;
			}
		}
		return true;
//		for(int i=0;i<input.size()-1;i++) {
//			for(int j=i+1; j<input.size();j++) {
//				if(!compare(input.get(i), input.get(j))) {
////					if any two sessions are conflicting with each other
//					return false;
//				}
//			}
//		}
//		return true;
	}
	public static boolean compare(session a, session b) {
		int day_a;
		int day_b;
		for(int i=0; i<a.day.size();i++) {
			day_a = a.day.get(i);
			for(int j=0; j<b.day.size();j++) {
				day_b = b.day.get(j);
				if(day_a==day_b) {
					if(a.start < b.start) {
//						the case when a starts earlier than b starts
						if(a.finish>b.start) {
//						if a finishes later than b starts, then they are overlapping
							return false;
						}
					}
					else if(a.start > b.start) {
//						the case when a starts later than b starts
						if(a.start < b.finish) {
//							if b finishes later than a starts, overlapping
							return false;
						}
					}
					else {
						return false;
//						this is the case when a and b start at the same time
//						already overlapping
					}
				}
			}
		}
		return true;
	}
	public static Vector<session> rating(Vector<Vector<session>> input){
		Vector<session> result = new Vector<session>();
		double max = 0;
		for(int i=0; i<input.size();i++) {
			Vector<session> buffer = input.get(i);
			double count = buffer.size();
			double total = 0;
			double ave = 0;
			for(int j=0; j<buffer.size();j++) {
				if(buffer.get(j).rating >=0) {
//					all courses' ratings are initialized to negative 1
//					if a course has a rating, it must be non-negative
					total += buffer.get(i).rating;
				}
				else {
					count--;
//					decrement the denominator when a course doesn't have a rating
//					so that the average is accurate
				}
			}
			if(count>0) {
				ave = total/count;
				if(ave>max) {
					ave = max;
					result = buffer;
				}
			}
		}
		return result;
//		note that the result could be an empty set
//		because it's possible that every courses don't have professor ratings
	}
	
	public static Vector<Integer> free_day(Vector<session> input) {
//		given a schedule, this function returns the day(s) that are free of class
//		this function might be improved by using recursion
		Vector<Integer> output = new Vector<Integer>();
		boolean mon, tue, wed, thur, fri, sat, sun;
		mon=tue=wed=thur=fri=sat=sun=true;
		for(int i=0; i<input.size();i++) {
			session target = input.get(i);
			Vector<Integer> weekday = target.day;
			for(int j=0; j<weekday.size();j++) {
				int day = weekday.get(j);
				if(day==1) {
					mon = false;
				}
				else if(day==2) {
					tue = false;
				}
				else if(day==3) {
					wed = false;
				}
				else if(day==4) {
					thur = false;
				}
				else if(day==5) {
					fri = false;
				}
				else if(day==6) {
					sat = false;
				}
				else if(day==7) {
					sun = false;
				}
			}
		}
		if(mon) {
			output.add(1);
		}
		if(tue) {
			output.add(2);
		}
		if(wed) {
			output.add(3);
		}
		if(thur) {
			output.add(4);
		}
		if(fri) {
			output.add(5);
		}
		return output;
	}
	
	public static int day_to_num(String day) {
		if(day.equals("Monday")||day.equals("Mon")) {
			return 1;
		}
		else if(day.equals("Tuesday")||day.equals("Tue")) {
			return 2;
		}
		else if(day.equals("Wednesday")||day.equals("Wed")) {
			return 3;
		}
		else if(day.equals("Thursday")||day.equals("Thu")) {
			return 4;
		}
		else if(day.equals("Friday")||day.equals("Fri")) {
			return 5;
		}
		else if(day.equals("Saturday")||day.equals("Sat")) {
			return 6;
		}
		else if(day.equals("Sunday")||day.equals("Sun")){
			return 7;
		}
		return 0;
	}
}


