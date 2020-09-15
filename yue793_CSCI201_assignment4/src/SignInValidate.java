

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


@WebServlet("/SignInValidate")
public class SignInValidate extends HttpServlet {
	private static final long serialVersionUID = 1L;
       

    public SignInValidate() {
        super();
        // TODO Auto-generated constructor stub
    }


	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String email = request.getParameter("email");
		String password = request.getParameter("password");
		String buffer = "SELECT s.email, s.upassword FROM saluser s where s.email="+"'"+email+"' AND s.upassword='"+password+"'";
		Connection conn = null;
		java.sql.Statement st = null;
		ResultSet rs = null;
		PrintWriter out = response.getWriter();
		try {
			DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());
			conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/hw4?serverTimezone=UTC&user=root&password=Dan15110278550.");
			st = conn.createStatement();
			rs=st.executeQuery(buffer);
			boolean match = false;
			while(rs.next()) {
				if(email.contentEquals(rs.getString("email"))&&password.contentEquals(rs.getString("upassword"))) {
					match = true;
				}
			}
			if(!match) {
				out.println("incorrect email or password!");
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
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
