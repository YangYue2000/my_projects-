

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


@WebServlet("/AddFavorite")
public class AddFavorite extends HttpServlet {
	private static final long serialVersionUID = 1L;
    public AddFavorite() {
        super();
    }
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String rating = request.getParameter("r");
		String id = request.getParameter("id");
		String image = request.getParameter("image");
		String address= request.getParameter("address");
		String name = request.getParameter("name");
		String url = request.getParameter("url");
		Connection conn = null;
		java.sql.Statement st = null;
		try {
//			Class.forName("com.mysql.jdbc.Driver");
			DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());
			conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/hw4?serverTimezone=UTC&user=root&password=Dan15110278550.");
			st = conn.createStatement();
			st.executeUpdate("INSERT INTO favorites (userID,address,rname,url,rating,image) VALUES('"+id+"','"+address+"','"+name+"','"+url+"','"+rating+"','"+image+"')");
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
