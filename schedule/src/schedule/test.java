package schedule;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Scanner;

import javax.swing.text.StyledEditorKit.ForegroundAction;
import javax.xml.ws.WebEndpoint;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class test {
	public static void main(String[] args) throws IOException {
		String homePage = "https://classes.usc.edu";
		
		
		String webPage = "https://classes.usc.edu/term-20201/classes/writ/";
		org.jsoup.nodes.Document doc = Jsoup.connect(webPage).get();

//		###code below scrape all the class names of a certain semester
//		File file = new File("spring.txt");
//		FileOutputStream fos = new FileOutputStream(file);
//	    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));
//		Elements schools = doc.select("div#content-main ul#sortable-classes li");
//		for(Element school : schools) {
//			if(school.attr("data-type").equals("department")) {
//				String school_link = school.child(0).attr("href");
//				doc = Jsoup.connect(school_link).get();
//				Elements divs = doc.select("div.course-details");
//				for(Element div : divs) {
//					String id = div.id();
//			    	int x = id.lastIndexOf("-");
//			    	id = id.substring(0, x);
//			    	bw.write(id);
//			    	bw.newLine();
//				}
//			}
//		}
//		bw.close();
		
	

//		Element whole = doc.select("[data-code='CSCI']").first();
//		String link =whole.child(0).attr("href");

		

	    String html = doc.html();
	    doc = Jsoup.parse(html);
	    System.out.println(doc.toString());
	    
	    
//	   ###code below find a class from the text file###
//	    Scanner scanner = new Scanner(file);
//	    String input = "CSCI-794Z";
//	    while(scanner.hasNextLine()) {
//	    	if(scanner.nextLine().equals(input)) {
//	    		System.out.println("found "+input);
//	    	}
//	    }
		
//	   ####codes below find the information of a specific class####
//		doc = Jsoup.connect("https://classes.usc.edu/term-20203/classes/csci/").get();
//	    Elements tables = doc.select("div#CSCI-103 tr");
//	    for(Element table : tables) {
//	    	Elements details = table.select("td");
//	    	if(details.size()>0) {
//	    		for(int i=0; i<8; i++) {
//		    		Element detail = details.get(i);
//		    		System.out.println(detail.text());
//		    	}
//	    	}
//	    	System.out.println("");
//	    }
	}
}
