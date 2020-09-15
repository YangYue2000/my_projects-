

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


@WebServlet("/nameValidate")
public class nameValidate extends HttpServlet {
	private static final long serialVersionUID = 1L;
       

    public nameValidate() {
        super();
    }


	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String name = (String)request.getParameter("name");
		String buffer = "SELECT s.uname from saluser s where s.uname="+"'"+name+"'";
		Connection conn = null;
		java.sql.Statement st = null;
		ResultSet rs = null;
		PrintWriter out = response.getWriter();
		try {
			DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());
			conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/hw4?serverTimezone=UTC&user=root&password=Dan15110278550.");
			st = conn.createStatement();
			rs=st.executeQuery(buffer);
			while(rs.next()) {
				if(name.contentEquals(rs.getString("uname"))) {
					out.println("This name has been USED!");
					break;
				}
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
	}

}
