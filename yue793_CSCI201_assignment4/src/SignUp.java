

import java.io.IOException;
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

import com.sun.jndi.url.corbaname.corbanameURLContextFactory;


@WebServlet("/SignUp")
public class SignUp extends HttpServlet {
	private static final long serialVersionUID = 1L;

    public SignUp() {
        super();
    }


	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		String name = request.getParameter("name");
		String password = request.getParameter("password");
		String email = request.getParameter("email");
		Connection conn = null;
		java.sql.Statement st = null;
		try {
//			Class.forName("com.mysql.jdbc.Driver");
			DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());
			conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/hw4?serverTimezone=UTC&user=root&password=Dan15110278550.");
			st = conn.createStatement();
			st.executeUpdate("INSERT INTO saluser (uname,email,upassword) VALUES('"+name+"','"+email+"','"+password+"')");
			if(email!=null) {
				HttpSession session = request.getSession(true);
				session.setAttribute("email", email);
				response.sendRedirect("home.jsp");
			}
		} catch ( SQLException e) {
			e.printStackTrace();
		}finally {
			try {
				if (st != null) {
					st.close(); 
				}
				if (conn != null){
					conn.close(); 
				}
			}
			catch (SQLException sqle){ 
				System.out.println(sqle.getMessage());
			} 
		}
	}


	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
