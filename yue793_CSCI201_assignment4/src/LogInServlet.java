

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.websocket.Session;

@WebServlet("/LogInServlet")
public class LogInServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
    
    public LogInServlet() {
        super();
    }
    
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String email = request.getParameter("email");
		String password = request.getParameter("password");
		if(email!=null) {
			System.out.println("in Login page: email is: "+email);
//			The SQL part of code creates a corresponding account in the Database for a first-signed-in gmail or 
//			prints out a message indicating there is already an account made in the Database
//			if i keep this code, there is a bug: when I sign in using gmail, most of the times the session
//			is not directed to the home page after loggin in. But if i log in with a normal account with a password 
//			and try to log in with gmail again, the session is directed.....
//			i guess its a problem about connecting to 
			if(password==null) {
				String buffer = "SELECT s.email from saluser s where s.email="+"'"+email+"'";
				Connection conn = null;
				java.sql.Statement st = null;
				ResultSet rs = null;
				boolean existed_account = false;
//				try {
//					DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());
//					conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/hw4?serverTimezone=UTC&user=root&password=Dan15110278550.");
//					st = conn.createStatement();
//					rs=st.executeQuery(buffer);
//					while(rs.next()) {
//						if(email.contentEquals(rs.getString("email"))) {
//							existed_account = true;
//							System.out.println("google duplicates existing account!");
//							break;
//						}
//					}
//					if(!existed_account) {
//						st.executeUpdate("INSERT INTO saluser (uname,email,upassword) VALUES('google_user','"+email+"','')");
//					}
//				} catch ( SQLException e) {
//					e.printStackTrace();
//				}finally {
//					try {
//						if (st != null) {
//							st.close(); 
//						}
//						if (conn != null){
//							conn.close(); 
//						}
//					}
//					catch (SQLException sqle){ 
//						System.out.println(sqle.getMessage());
//					} 
//				}
			}
			HttpSession session = request.getSession(true);
			session.setAttribute("email", email);
			response.sendRedirect("home.jsp");
		}
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
